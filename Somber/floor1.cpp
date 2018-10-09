#include "floor1.h"
#include "EngineX/Utility.h"

using namespace sf;
using namespace std;

void floor1::Init(Engine* game)
{
	cout << "scene created" << endl;
	if (!tex.loadFromFile("res/running_1.png"))
	{
		cout << "can't load texture" << endl;
	}
	MainChar.Init(tex, 0.1, 300);
	MainChar.setScale(1.25, 1.25);
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
	
		MainChar.update(dt);
	}
}

void floor1::Draw(RenderWindow * app)
{
	MainChar.drawTo(app);
}
