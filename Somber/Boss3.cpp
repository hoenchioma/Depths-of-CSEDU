#include "Boss3.h"

using namespace std;
using namespace sf;


void Boss3::LoadRes()
{
	loadFromFile(characterSpriteSheet, "res/running_1.png");
}

void Boss3::Init(Engine * game)
{
	grid.Init(CanvasWidth, CanvasHeight, 40);
	cout << grid.sizeX << " " << grid.sizeY << endl;

	snek.Init(50, Vector2f(game->width / 2.0, game->height / 2.0), &grid, Color::Green, 0.2, 1.5);
	
	mainChar.Init(characterSpriteSheet, 0.1f, 300.f);
	mainChar.setScale(1.4f, 1.4f);
	mainChar.setPosition(10, 10);

	// so that it doesn't go out of the boundary
	mainChar.setBoundary(CanvasWidth, CanvasHeight);
	// so that it can't go over the blocked parts in grid
	mainChar.dontMoveIf([&]() {return grid.at(grid.realToGrid(mainChar.getPosition())); });
}

void Boss3::Cleanup()
{
}

void Boss3::Pause()
{
	pause = true;
	snek.time.pause();
}

void Boss3::Resume()
{
	pause = false;
	snek.time.resume();
}

void Boss3::togglePause()
{
	if (pause) Resume();
	else Pause();
}

void Boss3::HandleEvents(Engine * game, sf::Event * event)
{
}

void Boss3::Update(Engine * game, double dt)
{
	if (!pause)
	{
		mainChar.keyHandle();
		mainChar.update(dt);

		centreView(game->gameView, mainChar.getPosition(), Vector2f(CanvasWidth, CanvasHeight));

		auto nowPos = mainChar.getPosition();
		bool eaten = snek.update(dt, mainChar.getPosition(), nowPos != prevPos);
		prevPos = nowPos;

		if (eaten) popScene(game);
	}
}

void Boss3::Draw(sf::RenderWindow * app)
{
	mainChar.drawTo(app);
	snek.drawTo(app);

	/************************ TESTING ZONE **************************/
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
