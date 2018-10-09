#pragma once

#include "EngineX/AniSprite.h"
#include "EngineX/Utility.h"

class mainChar
{
public:
	mainChar() {};
	mainChar(sf::Texture& tex, float delay, float vel) { Init(tex, delay, vel); }
	~mainChar() {};

	void Init(sf::Texture& tex, float delay, float vel);

	bool running = false;
	Direction getState() { return state; }
	void setScale(float x, float y);
	void setScale(sf::Vector2f);

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f vec);
	void setPosition(float x, float y);

	void moveOn(Direction direc);
	void moveOff();

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

