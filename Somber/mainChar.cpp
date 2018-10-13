#include "MainChar.h"

using namespace sf;
using namespace std;

void MainChar::Init(sf::Texture& tex, float delay, float vel)
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

void MainChar::setScale(float x, float y)
{
	for (auto& i : ani)
	{
		i.setScale(x, y);
	}
}

void MainChar::setScale(sf::Vector2f vec)
{
	for (auto& i : ani)
	{
		i.setScale(vec);
	}
}

sf::Vector2f MainChar::getPosition() const
{
	return ani[0].getPosition();
}

sf::Vector2f MainChar::getSize() const
{
	return ani[0].getSize();
}

sf::IntRect MainChar::getTextureRect() const
{
	return ani[0].getTextureRect();
}

sf::FloatRect MainChar::getGlobalBounds() const
{
	return ani[0].getGlobalBounds();
}

void MainChar::setPosition(sf::Vector2f vec)
{
	for (auto& i : ani) i.setPosition(vec);
}

void MainChar::setPosition(float x, float y)
{
	for (auto& i : ani) i.setPosition(x, y);
}

void MainChar::setOrigin(sf::Vector2f vec)
{
	for (auto& i : ani) i.setOrigin(vec);
}

void MainChar::setOrigin(float x, float y)
{
	for (auto& i : ani) i.setOrigin(x, y);
}

void MainChar::setColor(const sf::Color& color)
{
	for (auto& i : ani) i.setColor(color);
}

void MainChar::moveOn(Direction direc)
{
	running = true;
	state = direc;
	ani[state].resume();
}

void MainChar::moveOff()
{
	running = false;
	ani[state].pause();
}

void MainChar::update(float dt)
{
	if (running)
	{
		for (auto& i: ani)
			i.move(dt * vel * dirAr[state][0], dt * vel * dirAr[state][1]);
	}
}

void MainChar::drawTo(sf::RenderWindow* app)
{
	ani[state].drawTo(app);
}
