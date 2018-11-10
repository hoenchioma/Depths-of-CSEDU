#include "Boss3.h"

using namespace std;
using namespace sf;


#define SNEK_LENGTH 50

// snek speed at easy difficulty
#define EASY_SNEK 0.3
// snek speed at medium difficulty
#define MID_SNEK 0.2
// snek speed at hard difficulty
#define HARD_SNEK 0.15


void Boss3::LoadRes()
{
	loadFromFile(characterSpriteSheet, "res/running_1.png");
	loadFromFile(wallTexture, "res/walltex_wshadow.png");
	loadFromFile(floorTex, "res/stone_floor_50x50.png");
	loadFromFile(appleTex, "res/apple.png");

	loadFromFile(headTex, "res/snek_head2.png");
	loadFromFile(tailTex, "res/snek_tail.png");
	loadFromFile(bodyTex, "res/snek_body.png");
	loadFromFile(jointTex, "res/snek_joint2.png");

	loadFromFile(textBoxFont, "res/Font/PressStart2P.ttf");
	highScoreFont.loadFromFile("res/Font/unispace bd.ttf");

	highestScoreTex.loadFromFile("res/HighScoreTag.png");
	scoreCardTex.loadFromFile("res/scoreCard.png");

	timeText.resLoad();
}

void Boss3::Init(Engine * game)
{
	this->game = game;

	resetView(game->gameView);
	game->miniMapOn = true;
	game->miniMap.reset(sf::FloatRect(0, 0, CanvasWidth, CanvasHeight));
	
	grid.Init(CanvasWidth, CanvasHeight, 50);

#ifdef _DEBUG
	cout << grid.sizeX << " " << grid.sizeY << endl;
#endif

	Maze maze("extra/maze/maze1.txt");
	grid.fill(maze);

	// done before snek.Init to prevent snek body blocks being walled
	walls.Init(&grid, wallTexture);

	snek.Init(SNEK_LENGTH, Vector2f(game->width / 2.0, game->height / 2.0), &grid, Color::Green, EASY_SNEK, 1);
	snek.setTexture(headTex, tailTex, bodyTex, jointTex);
	
	mainChar.Init(characterSpriteSheet, 0.1f, 300.f);
	mainChar.setScale(1.4f, 1.4f);
	mainChar.setPosition(grid.toPoint(GridPoint(0, 0)));

	snek.preCalculateBFS(mainChar.getPosition());

	// so that it doesn't go out of the boundary
	mainChar.setBoundary(0, 0, CanvasWidth, CanvasHeight);
	// so that it can't go over the blocked parts in grid
	mainChar.dontMoveIf([&]() {return grid.at(grid.realToGrid(mainChar.getPosition())); });

	apple.setTexture(appleTex);
	apple.setOrigin(apple.getTexture()->getSize().x / 2.0, apple.getTexture()->getSize().x / 2.0);
	apple.setScale(0.1f, 0.1f);
	apple.setPosition(grid.toPoint(grid.randomPoint()));


	floorTex.setRepeated(true);
	floor.setTexture(floorTex);
	floor.setTextureRect(IntRect(0, 0, CanvasWidth, CanvasHeight));
	floor.setPosition(0, 0);

	textBox.Init(game, textBoxFont);
	textBox.addTextTyped("Hello world!!");

	menu.Init(game, this, textBoxFont);
	//menu.turnOn();

	timeText.Init(game);

	////////// score and high score /////////////
	scoreToText.setFont(highScoreFont);
	topScoreText.setFont(highScoreFont);
	scoreToText.setCharacterSize(20);
	topScoreText.setCharacterSize(30);
	scoreToText.setPosition(1e6, 1e6);
	topScoreText.setPosition(1e6, 1e6);
	
	highestScoreTag.setPosition(1e6, 1e6);
	scoreCard.setPosition(1e6, 1e6);

	highestScoreTag.setTexture(highestScoreTex);
	scoreCard.setTexture(scoreCardTex);

	GameOver = false;
	instantWin = false;

	//snek.time.pause();
}

void Boss3::Cleanup()
{
	resetView(game->gameView);
	this->game->miniMapOn = false;
	_fullScreen = false;
	menu.turnOff();
	textBox.turnOn();
	textBox.setText("");
	Resume();
}

void Boss3::Pause()
{
	pause = true;

	snek.time.pause();
	mainChar.pause();
	textBox.time.pause();
	timeText.time.pause();
}

void Boss3::Resume()
{
	pause = false;

	snek.time.resume();
	mainChar.resume();
	textBox.time.resume();
	timeText.time.resume();
}

void Boss3::togglePause()
{
	if (pause) Resume();
	else Pause();
}

void Boss3::HandleEvents(Engine * game, sf::Event * event)
{
	if (event->type == Event::EventType::KeyPressed)
	{
		switch (event->key.code)
		{
		case Keyboard::Space:
			togglePause();
			break;
		case Keyboard::C:
			instantWin = true;
			break;
		default:
			break;
		}
	}
	textBox.handleEvent(event);
	menu.handleEvent(event);
}

void Boss3::Update(Engine * game, double dt)
{
	if (!pause)
	{
		mainChar.keyHandle();
		mainChar.update(dt);

		centreView(game->gameView, mainChar.getPosition(), Vector2f(CanvasWidth, CanvasHeight));

		if (mainChar.intersects(apple.getGlobalBounds()) or instantWin)
		{
			if (snek.getLength() - 10 <= 0 or instantWin)
			{
				//////// return to previous scene /////////
				////////// score and high score ///////////
				_fullScreen = true;
				game->fullScreen.reset(FloatRect(0, 0, game->width, game->height));
				textBox.turnOff();
				Pause();

				scoreToText.setCharacterSize(50);
				scoreToText.setPosition(500, 200);
				scoreToText.setString(timeText.getStr());
				scoreCard.setPosition(0, 0);

				int savedScoreTime = -1;
				bool newHighScore = false;

				// check and read high score from file
				ifstream file("save/Boss3ScoreFile.txt");
				if (file.good())
				{
					file >> savedScoreTime;
					if (timeText.getTime() < savedScoreTime)
						newHighScore = true;
				}
				else newHighScore = true;
				file.close();

				// save new score to file
				if (newHighScore)
				{
					ofstream fileOut("save/Boss3ScoreFile.txt");
					fileOut << timeText.getTime() << "\n";
					fileOut.close();
				}
				
				if (!newHighScore)
				{
					char strrr[50];
					sprintf_s(strrr, "TOP TIME: %02d:%02d", savedScoreTime / 60, savedScoreTime % 60);
					topScoreText.setString(strrr);
				}

				if (!newHighScore)
				{
					topScoreText.setPosition(530, 300);
				}
				else
				{
					highestScoreTag.setPosition(350, 300);
				}

				GameOver = true;
				instantWin = false;
			}
			else
			{
				apple.setPosition(grid.toPoint(grid.randomPoint()));
				snek.cut(10);
				snek.setDelay(snek.getDelay() - 0.03);
			}
		}


		bool eaten = snek.update(dt, mainChar.getPosition());

		if (eaten)
		{
			eaten = false;
			Pause();
			menu.turnOn();
		}
		//if (grid.realToGrid(mainChar.getPosition()) == GridPoint(grid.sizeX - 1, grid.sizeY - 1))
			//popScene(game);
		textBox.update();

		timeText.update();
	}
	if (GameOver && Keyboard::isKeyPressed(Keyboard::Enter)) popScene(game);
}

void Boss3::Draw(sf::RenderWindow * app)
{
	app->draw(floor);
	
	walls.drawTo1(app, mainChar.getPosition());

	snek.drawTo1(app);
	app->draw(apple);
	mainChar.drawTo(app);
	snek.drawTo2(app);

	walls.drawTo2(app);

	timeText.drawTo(app);

	textBox.draw();
	menu.draw(app);

	/////// score and high score ////////
	app->draw(scoreCard);
	app->draw(highestScoreTag);
	app->draw(scoreToText);
	app->draw(topScoreText);

	/************************ TESTING ZONE **************************
	CircleShape test(5);
	test.setOrigin(test.getRadius(), test.getRadius());
	for (int i = 0; i < grid.sizeX; i++)
	{
		for (int j = 0; j < grid.sizeY; j++)
		{
			if (grid.at({ i, j })) test.setFillColor(Color::Red);
			else test.setFillColor(Color(255, 255, 255, 50));
			test.setPosition(grid.toPoint(GridPoint(i, j)));
			app->draw(test);
		}
	}

	test.setFillColor(Color::Cyan);
	test.setPosition(grid.toPoint(snek.headCor));
	app->draw(test);

	test.setFillColor(Color::Yellow);
	test.setPosition(grid.toPoint(snek.tailCor));
	app->draw(test);

	test.setFillColor(Color::Blue);
	test.setPosition(grid.toPoint(grid.realToGrid(mainChar.getPosition())));
	app->draw(test);

	test.setFillColor(Color::Red);
	test.setPosition(mainChar.getPosition());
	app->draw(test);
	/**********************************************************************/
}
