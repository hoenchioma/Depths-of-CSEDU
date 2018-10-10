#include "mainChar.h"

using namespace sf;
using namespace std;

void mainChar::Init(sf::Texture& tex, float delay, float vel)
{
	this->vel = vel;
	
	int bitx = tex.getSize().x / 3;
	int bity = tex.getSize().y / 4;

	for (auto& i : ani)
	{
		i.setSpriteSheet(tex);
		i.setDelay(delay);
		i.pause();
	}
	ani[0].addSheet(AniSprite::dir::horizontal, bitx, bity, 0, bity);
	ani[0].setDefault(IntRect(bitx, bity, bitx, bity));

	ani[1].addSheet(AniSprite::dir::horizontal, bitx, bity, 0, bity * 2);
	ani[1].setDefault(IntRect(bitx, bity * 2, bitx, bity));

	ani[2].addSheet(AniSprite::dir::horizontal, bitx, bity, 0, bity * 3);
	ani[2].setDefault(IntRect(bitx, bity * 3, bitx, bity));

	ani[3].addSheet(AniSprite::dir::horizontal, bitx, bity, 0, 0);
	ani[3].setDefault(IntRect(bitx, 0, bitx, bity));
}

void mainChar::setScale(float x, float y)
{
	for (auto& i : ani)
	{
		i.setScale(x, y);
	}
}

void mainChar::setScale(sf::Vector2f vec)
{
	for (auto& i : ani)
	{
		i.setScale(vec);
	}
}

sf::Vector2f mainChar::getPosition() const
{
	return ani[0].getPosition();
}

sf::Vector2f mainChar::getSize() const
{
	return ani[0].getSize();
}

sf::IntRect mainChar::getTextureRect() const
{
	return ani[0].getTextureRect();
}

sf::FloatRect mainChar::getGlobalBounds() const
{
	return ani[0].getGlobalBounds();;
}

void mainChar::setPosition(sf::Vector2f vec)
{
	for (auto& i : ani) i.setPosition(vec);
}

void mainChar::setPosition(float x, float y)
{
	for (auto& i : ani) i.setPosition(x, y);
}

void mainChar::setOrigin(sf::Vector2f vec)
{
	for (auto& i : ani) i.setOrigin(vec);
}

void mainChar::setOrigin(float x, float y)
{
	for (auto& i : ani) i.setOrigin(x, y);
}

void mainChar::setColor(const sf::Color& color)
{
	for (auto& i : ani) i.setColor(color);
}

void mainChar::moveOn(Direction direc)
{
	running = true;
	state = direc;
	ani[state].resume();
}

void mainChar::moveOff()
{
	running = false;
	ani[state].pause();
}

void mainChar::update(float dt)
{
	if (running)
	{
		for (auto& i: ani)
			i.move(dt * vel * dirAr[state][0], dt * vel * dirAr[state][1]);
	}
}

void mainChar::drawTo(sf::RenderWindow* app)
{
	ani[state].drawTo(app);
}
