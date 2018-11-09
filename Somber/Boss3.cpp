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
	textBox.addTextTyped("Hello world, you guys are the best. I'll always be in debt to you :')");

	menu.Init(game, this, textBoxFont);
	//menu.turnOn();

	//snek.time.pause();
}

void Boss3::Cleanup()
{
	resetView(game->gameView);
	this->game->miniMapOn = false;
	Resume();
}

void Boss3::Pause()
{
	pause = true;
	snek.time.pause();
	mainChar.pause();
	textBox.time.pause();
	
}

void Boss3::Resume()
{
	pause = false;
	snek.time.resume();
	mainChar.resume();
	textBox.time.resume();
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
		/*case Keyboard::C:
			snek.cut(10);
			break;*/
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

		if (mainChar.intersects(apple.getGlobalBounds()))
		{
			if (snek.getLength() - 10 <= 0) popScene(game);
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
	}
}

void Boss3::Draw(sf::RenderWindow * app)
{
	app->draw(floor);
	
	walls.drawTo1(app, mainChar.getPosition());

	mainChar.drawTo(app);
	snek.drawTo(app);
	app->draw(apple);

	walls.drawTo2(app);

	textBox.draw();
	menu.draw(app);

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
