#include "boss1.h"

#include "EngineX/Utility.h"

using namespace sf;
using namespace std;

void boss1::Init(Engine* game)
{
	// Initialize variables here
}

void boss1::Cleanup()
{
}

void boss1::Pause()
{
	pause = true;

	// handle what happens when the game is paused
	// this function is going to be called when the game is paused
}

void boss1::Resume()
{
	pause = false;

	// handle what happens when the game is resumed
	// this function is going to be called when the game is resumed
}

void boss1::togglePause()
{
	if (this->pause) Resume();
	else Pause();
}

void boss1::HandleEvents(Engine * game, Event * event)
{
	// handle events here (keyboard/ mouse)
	// see main.cpp for clarification of location of call
	
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

void boss1::Update(Engine * game, double dt)
{
	// handle collision and other logic
	// update the sprites
	// use dt (interval between two frames) for framerate independent movement
}

void boss1::Draw(RenderWindow * app)
{
	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
