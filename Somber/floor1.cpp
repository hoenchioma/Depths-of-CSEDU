#include "floor1.h"
#include "EngineX/Utility.h"
#include "boss1.h"

using namespace sf;
using namespace std;

const float offSetX = 118 - 25;
const float offSetY = 175 - 60;

void floor1::Init(Engine* game)
{
	cout << "scene created" << endl;

	cout << game->width << " " << game->height << endl;

	// views
	view.setCenter(game->width / 2, game->height / 2);
	view.setSize(game->width, game->height);
	
	// main character
	if (!spriteSheet.loadFromFile("res/running_1.png"))
	{
		cerr << "can't load texture 1" << endl;
	}
	MainChar.Init(spriteSheet, 0.1f, 300.f);
	MainChar.setScale(1.4f, 1.4f);

	cout << MainChar.getTextureRect().width << " " << MainChar.getTextureRect().height << endl;
	cout << MainChar.getSize().x << " " << MainChar.getSize().y << endl;
	cout << MainChar.getPosition().x << " " << MainChar.getPosition().y << endl;

	MainChar.setOrigin(MainChar.getTextureRect().width / 2.0, MainChar.getTextureRect().height / 2.0);
	MainChar.setPosition(game->width / 2.0, game->height / 2.0);
	//MainChar.setPosition(0, 0);

	// background
	if (!backgroundImage.loadFromFile("res/floor1_back_2.png"))
	{
		cerr << "can't load texture 2" << endl;
	}
	background.setTexture(backgroundImage);
	background.setScale(1.35, 1.35);
	background.setOrigin(0, 0);
	background.setPosition(0, 0);

	if (!doorImage.loadFromFile("res/door.png"))
	{
		cerr << "can't load texture 3" << endl;
	}
	Door.Init(doorImage);
	Door.setScale(0.85, 0.85);
	Door.setPosition(offSetX + 23, 5);

	// dark effect
	Uint8 light = 150;
	Door.setColor(Color(light, light, light));
	MainChar.setColor(Color(light, light, light));
	background.setColor(Color(light, light, light));
}

void floor1::Cleanup()
{
}

void floor1::Pause()
{
	MainChar.running = false;
	pause = true;
}

void floor1::Resume()
{
	pause = false;
}

void floor1::togglePause()
{
	if (this->pause) this->Resume();
	else this->Pause();
}

void floor1::HandleEvents(Engine * game, Event * event)
{
	// Key release handle
	if (event->type == Event::EventType::KeyReleased)
	{
		for (auto& i : KeyArr)
		{
			if (event->key.code == i)
			{
				MainChar.moveOff();
			}
		}
	}

	if (event->type == Event::EventType::KeyPressed)
	{
		switch (event->key.code)
		{
		case Keyboard::Escape:
			togglePause();
			break;
		case Keyboard::E:
			if (MainChar.getGlobalBounds().intersects(Door.getGlobalBounds()))
			{
				cout << "Door Opened" << endl;
				Door.open();
			}
			break;
		default:
			break;
		}
	}
}

void floor1::Update(Engine * game, double dt)
{
	if (!pause)
	{
		// Key press handle
		for (auto& i : KeyArr)
		{
			if (Keyboard::isKeyPressed(i))
			{
				MainChar.moveOn(KeyMap.at(i));
			}
		}

		bool intersection = MainChar.getGlobalBounds().intersects(Door.getGlobalBounds());

		/*cerr << MainChar.getPosition().x << " " << MainChar.getPosition().y << " "
			<< Door.getPosition().x << " " << Door.getPosition().y << endl;
		*/
		// so that the character sprite cannot go out of bounds
		if (MainChar.getPosition().x < 25 + offSetX) MainChar.setPosition(25 + offSetX, MainChar.getPosition().y);
		// character can only enter door region if door open
		// character cannot enter wall region
		if (Door.doorState == door::state::CLOSED)
		{
			if (MainChar.getPosition().y < 60 + offSetY)
				MainChar.setPosition(MainChar.getPosition().x, 60 + offSetY);
		}
		else
		{
			if (!intersection)
			{
				if (MainChar.getPosition().y < 60 + offSetY)
					MainChar.setPosition(MainChar.getPosition().x, 60 + offSetY);
			}
		}
		if (MainChar.getPosition().x > background.getGlobalBounds().width + offSetX - 20) 
			MainChar.setPosition(background.getGlobalBounds().width + offSetX - 20, MainChar.getPosition().y);
		if (MainChar.getPosition().y > background.getGlobalBounds().height + offSetY - 20) 
			MainChar.setPosition(MainChar.getPosition().x, background.getGlobalBounds().height + offSetY - 20);

		if (intersection)
		{
			if (MainChar.getPosition().y < offSetX + 50)
			{
				///////// scene change /////////////
				MainChar.moveOn(Direction::DOWN);
				MainChar.moveOff();
				pushScene(game, boss1::getInstance());
			}
		}
	
		MainChar.update(dt);
	}

	// so that camera doesn't go out of bounds
	if (MainChar.getPosition().x >= game->width / 2 
	and MainChar.getPosition().x + game->width /2 <= background.getGlobalBounds().width)
	{
		view.setCenter(MainChar.getPosition().x, view.getCenter().y);
	}
	if (MainChar.getPosition().y >= game->height / 2
	and MainChar.getPosition().y + game->height / 2 <= background.getGlobalBounds().height)
	{
		view.setCenter(view.getCenter().x, MainChar.getPosition().y);
	}
	game->app->setView(view);
}

void floor1::Draw(RenderWindow * app)
{
	app->draw(background);

	Door.drawTo(app);
	MainChar.drawTo(app);
}
