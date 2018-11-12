#include "Boss3.h"

#include "DefaultInv.h"

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

	invShow.loadRes();

	hissBuff.loadFromFile("res/Sounds/snakehiss2.wav");
	snakehiss.setBuffer(hissBuff);

	hitBuff.loadFromFile("res/Sounds/snakehit.wav");
	snakehit.setBuffer(hitBuff);
}

void Boss3::Init(Engine * game)
{
	game->app->setMouseCursorVisible(true);
	this->game = game;

	resetView(game->gameView);

	//makeDefault(game->inv);

	// mini map
	game->miniMapOn = true;
	game->miniMap.reset(sf::FloatRect(0, 0, CanvasWidth, CanvasHeight));

	// inventory
	game->inventoryOn = true;
	game->inventory.reset(sf::FloatRect(
		InvShow::getDefaultLoc().x,
		InvShow::getDefaultLoc().y,
		game->fullWidth * 0.2,
		game->fullHeight * 0.8
	));
	invShow.Init(game);
	
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
	if (!InitOnce) mainChar.setBoundary(0, 0, CanvasWidth, CanvasHeight);
	// so that it can't go over the blocked parts in grid
	if (!InitOnce) mainChar.dontMoveIf([&]() {return grid.at(grid.realToGrid(mainChar.getPosition())); });

	apple.setTexture(appleTex);
	apple.setOrigin(apple.getTexture()->getSize().x / 2.0, apple.getTexture()->getSize().x / 2.0);
	apple.setScale(0.1f, 0.1f);
	apple.setPosition(grid.toPoint(grid.randomPoint()));


	floorTex.setRepeated(true);
	floor.setTexture(floorTex);
	floor.setTextureRect(IntRect(0, 0, CanvasWidth, CanvasHeight));
	floor.setPosition(0, 0);

	textBox.Init(game, textBoxFont);
	textBox.addTextTyped("Escape the snake.\n\nIf you can....\n\nCollect poison apples to hurt the snake");

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

	// perk variable initialization
	speedB = false;
	reLifeB = false;
	timeFreezeB = false;
	phaseB = false;
	phaseBOnce = false;

	InitOnce = true;

	//snek.time.pause();

	// set all sound volume to zero when mute is on
	if (game->mute)
	{
		snakehiss.setVolume(0);
		snakehit.setVolume(0);
	}

	snakehiss.setVolume(0); // muted for annoyance
}

void Boss3::Cleanup()
{
	resetView(game->gameView);
	//this->game->miniMapOn = false;
	//this->game->inventoryOn = false;
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

	speedT.pause();
	reLifeT.pause();
	timeFreezeT.pause();
	phaseT.pause();

	hissTime.pause();
}

void Boss3::Resume()
{
	pause = false;

	snek.time.resume();
	mainChar.resume();
	textBox.time.resume();
	timeText.time.resume();

	speedT.resume();
	reLifeT.resume();
	timeFreezeT.resume();
	phaseT.resume();

	hissTime.resume();
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
		case Keyboard::Num1:
			if (INVI("speed"))
			{
				speedB = true;
				speedT.restart();
				invShow.activate("speed");
			}
			break;
		case Keyboard::Num6:
			if (INVI("timeFreeze"))
			{
				timeFreezeB = true;
				timeFreezeT.restart();
				invShow.activate("timeFreeze");
			}
			break;
		case Keyboard::Num7:
			if (INVI("phase"))
			{
				phaseB = true;
				phaseT.restart();
				invShow.activate("phase");
			}
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
				if (INVI("boss3Complete") == 0) INVI("boss3Complete") = 1;

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
			snakehit.play();
			eaten = false;
			Pause();
			menu.turnOn();
		}
		//if (grid.realToGrid(mainChar.getPosition()) == GridPoint(grid.sizeX - 1, grid.sizeY - 1))
			//popScene(game);
		textBox.update();

		timeText.update();

		/////////// perks ///////////////
		if (speedB)
		{
			if (speedT.getElapsedTime().asSeconds() < 10)
			{
				mainChar.setVel(700);
				invShow.setProgress("speed", 1.0 - speedT.getElapsedTime().asSeconds() / 10.0);
			}
			else
			{
				speedB = false;
				mainChar.setVel(300);
				invShow.deActivate("speed");
				INVI("speed")--;
			}
		}

		if (timeFreezeB)
		{
			if (timeFreezeT.getElapsedTime().asSeconds() < 10)
			{
				snek.time.pause();
				invShow.setProgress("timeFreeze", 1.0 - timeFreezeT.getElapsedTime().asSeconds() / 10.0);
			}
			else
			{
				timeFreezeB = false;
				snek.time.resume();
				invShow.deActivate("timeFreeze");
				INVI("timeFreeze")--;
			}
		}

		if (phaseB)
		{
			if (phaseT.getElapsedTime().asSeconds() < 10)
			{
				if (!phaseBOnce)
				{
					mainChar.dontMovePop();
					phaseBOnce = true;
				}
				invShow.setProgress("phase", 1.0 - phaseT.getElapsedTime().asSeconds() / 10.0);
			}
			else
			{
				phaseB = false;
				phaseBOnce = false;
				mainChar.dontMoveIf([&]() {return grid.at(grid.realToGrid(mainChar.getPosition())); });
				invShow.deActivate("phase");
				INVI("phase")--;
			}
		}

		invShow.update();

		// sound effects
		if (hissTime.getElapsedTime().asSeconds() > 10 - rand()%3)
		{
			hissTime.restart();
			snakehiss.play();
		}
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

	if (game->app->getView().getViewport().width > 0.5)
		timeText.drawTo(app);

	textBox.draw();
	invShow.draw(app);
	menu.draw(app);

	/////// score and high score ////////
	app->draw(scoreCard);
	app->draw(highestScoreTag);
	app->draw(scoreToText);
	app->draw(topScoreText);

	// uncomment section to see grid
	// for debugging purposes
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
