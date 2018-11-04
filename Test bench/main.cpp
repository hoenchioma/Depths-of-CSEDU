#include "EngineX/Engine.h"

#include "Boss4.h"

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

	game.pushScene(Boss4::getInstance());

	app.setFramerateLimit(120);

	while (app.isOpen())
	{
		game.handleChange();

		while (app.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
				game.close();
			if (event.type == Event::EventType::KeyPressed && event.key.code == Keyboard::Escape)
				game.close();
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
