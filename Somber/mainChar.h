#pragma once

#include "EngineX/AniSprite.h"
#include "EngineX/Utility.h"

class MainChar
{
public:
	MainChar() {};
	MainChar(sf::Texture& tex, float delay, float vel) { Init(tex, delay, vel); }
	~MainChar() {};

	void Init(sf::Texture& tex, float delay, float vel);

	bool running = false;
	Direction getState() { return state; }
	void setScale(float x, float y);
	void setScale(sf::Vector2f);

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::IntRect getTextureRect() const;
	sf::FloatRect getGlobalBounds() const;
	void setPosition(sf::Vector2f vec);
	void setPosition(float x, float y);
	void setOrigin(sf::Vector2f vec);
	void setOrigin(float x, float y);
	void setColor(const sf::Color& color);

	void moveOn(Direction direc);
	void moveOff();
	void setDirec(Direction direc) { state = direc; }

	void update(float dt);

	void drawTo(sf::RenderWindow* app);

private:
	const int dirAr[4][2] =
	{
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1}
	};

	AniSprite ani[4];
	float vel = 500;
	Direction state = DOWN;
};

