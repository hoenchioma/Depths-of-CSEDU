#include "EngineX/Engine.h"

#include "Floor1.h"
#include "Boss1.h"

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

	Engine game(&app);
	game.width = gameWidth;
	game.height = gameHeight;

	View gameView(FloatRect(0, 0, gameWidth, gameHeight));
	//gameView.setCenter(gameWidth / 2.f, gameHeight / 2.f);
	gameView.setViewport(FloatRect(0.f, 0.f, 0.8f, 0.8f));
	game.gameView = &gameView;

	game.pushScene(Floor1::getInstance());
	//game.pushScene(Boss1::getInstance());

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
		
		app.setView(gameView);
		game.Draw();
		
		app.display();
	}
	game.Cleanup();

	return 0;
}
