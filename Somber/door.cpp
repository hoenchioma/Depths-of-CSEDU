#include "pch.h"
#include "door.h"

using namespace sf;

door::door()
{
}


door::~door()
{
}

void door::Init(sf::Texture& tex)
{
	obj.setTexture(tex);
}

void door::open()
{
	doorState = OPEN;
}

void door::close()
{
	doorState = CLOSED;
}

void door::drawTo(sf::RenderWindow * app)
{
	if (doorState == CLOSED)
	{
		obj.setTextureRect(
			IntRect(0, 0, obj.getTexture()->getSize().x / 2, obj.getTexture()->getSize().y)
		);
	}
	else
	{
		obj.setTextureRect(
			IntRect(obj.getTexture()->getSize().x / 2, 0, obj.getTexture()->getSize().x / 2, obj.getTexture()->getSize().y)
		);
	}

	app->draw(obj);
}
