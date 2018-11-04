#include "Boss4.h"

using namespace sf;
using namespace std;


void Boss4::LoadRes()
{
	// load resources
}

void Boss4::Init(Engine* game)
{
	// initialize variables
}

void Boss4::Cleanup()
{
}

void Boss4::Pause()
{
	Sprite.running = false;
	pause = true;

	// this function is going to be called when the game is paused
}

void Boss4::Resume()
{
	pause = false;

	// this function is going to be called when the game is resumed
}

void Boss4::togglePause()
{
	if (this->pause) Resume();
	else Pause();
}

void Boss4::HandleEvents(Engine * game, Event * event)
{
	// handle events here (keyboard/ mouse)
}

void Boss4::Update(Engine * game, double dt)
{
	if (!pause)
	{
		// Key press & release handle
		// handle collision and other logic
		// update the sprites
		// use dt (interval between two frames) for framerate independent movement
	}
}

void Boss4::Draw(RenderWindow * app)
{
	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
