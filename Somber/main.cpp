#include "EngineX/Engine.h"
#include "Floor1.h"
#include "Boss1.h"
#include <ctime>

using namespace sf;

int main()
{
	srand(time(0));
	
	RenderWindow app(VideoMode(1280, 720), "Depths of CSEDU");
	Event event;
	Clock clock;
	double dt;

	Engine game(&app);

	game.pushScene(Floor1::getInstance());
	//game.pushScene(Boss1::getInstance());

	//app.setFramerateLimit(10);

	while (app.isOpen())
	{
		game.handleChange();

		while (app.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
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
