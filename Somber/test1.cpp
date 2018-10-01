#include "pch.h"
#include "test1.h"

using namespace sf;
using namespace std;

void test1::Init(Engine* game)
{
	cerr << "box created!!" << endl;
	box.setFillColor(Color::Red);
	box.setSize(Vector2f(50, 50));
	box.setPosition(game->width/2, game->height/2);
}

void test1::Cleanup()
{
}

void test1::Pause()
{
}

void test1::Resume()
{
}

void test1::HandleEvents(Engine * game, Event * event)
{
	if (event->type == Event::EventType::KeyPressed)
	{
		if (event->key.code == Keyboard::P)
		{
		}
	}
}

void test1::Update(Engine * game, double dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		box.move(dt * vel, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		box.move(-dt * vel, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		box.move(0, -dt * vel);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		box.move(0, dt * vel);
	}
}

void test1::Draw(RenderWindow * app)
{
	app->draw(box);
}
