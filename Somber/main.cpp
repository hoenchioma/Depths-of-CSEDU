#include "EngineX/Engine.h"

#include "Floor1.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "MainMenu.h"

#include <ctime>

using namespace sf;
using namespace std;

const int gameWidth = 1280;
const int gameHeight = 720;

int main()
{
	srand(time(0));
	
	RenderWindow app(VideoMode::getDesktopMode(), "Depths of CSEDU", Style::Fullscreen);
	Event event;
	Clock clock;
	double dt;

	Engine game(&app, gameWidth, gameHeight);

	game.pushScene(MainMenu::getInstance());
	//game.pushScene(Floor1::getInstance());
	//game.pushScene(Boss1::getInstance());
	//game.pushScene(Boss2::getInstance());
	//game.pushScene(Boss3::getInstance());

	//app.setFramerateLimit(120);

	while (app.isOpen())
	{
		game.handleChange();

		while (app.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
				game.close();
			if (event.type == Event::EventType::KeyPressed && event.key.code == Keyboard::Escape)
				game.close();
			if (event.type == Event::EventType::KeyPressed && event.key.code == Keyboard::Q)
				game.popScene();
			game.HandleEvents(&event);
		}

		dt = clock.restart().asSeconds();

		game.Update(dt);

		app.clear();
		game.Draw();
		app.display();
	}
	game.Cleanup();

	return 0;
}
