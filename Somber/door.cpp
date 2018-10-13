#include "pch.h"
#include "Door.h"

using namespace sf;

Door::Door()
{
}


Door::~Door()
{
}

void Door::Init(sf::Texture& tex)
{
	obj.setTexture(tex);
}

void Door::open()
{
	DoorState = OPEN;
}

void Door::close()
{
	DoorState = CLOSED;
}

void Door::drawTo(sf::RenderWindow * app)
{
	if (DoorState == CLOSED)
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
