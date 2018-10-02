#include "EngineX/Engine.h"
#include "test1.h"

using namespace sf;

int main()
{
	RenderWindow app(VideoMode(1000, 700), "Depths of CSEDU");
	Event event;
	Clock clock;
	double dt;

	Engine game(&app);

	game.pushScene(test1::getInstance());

	//app.setFramerateLimit(120);

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
