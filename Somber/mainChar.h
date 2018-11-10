#pragma once

#include "EngineX/AniSprite.h"
#include "EngineX/Utility.h"
#include "EngineX/Polygon.h"

#include <vector>
#include <functional>

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
	inline void setVel(float vel) { this->vel = vel; };

	void pause();
	void resume();

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::IntRect getTextureRect() const;
	sf::FloatRect getGlobalBounds() const;
	void setPosition(sf::Vector2f vec);
	void setPosition(float x, float y);
	void setOrigin(sf::Vector2f vec);
	void setOrigin(float x, float y);
	void setColor(const sf::Color& color);
	Polygon& getPoly() { return poly; }

	void moveOn(Direction direc);
	void moveOff();
	void setDirec(Direction direc) { state = direc; }
	void keyHandle();

	// set the boundary of player movement (in Init)
	void setBoundary(float left, float top, float width, float height);
	// set the boundary of player movement (in Init)
	void setBoundary(sf::Vector2f topLeft, sf::Vector2f size);
	// set the boundary of player movement (in Init)
	void setBoundary(sf::FloatRect bound);

	bool intersects(const Polygon& a);

	// add a polygon pointer to the off-limits list (saves a reference/pointer to the polygon)
	void dontIntersect(Polygon* a);
	// add a polygon to the off-limits list (saves the polygon itself)
	void dontIntersect(Polygon a);
	// add a bool function to the dontDo list (things the char is not allowed to do)
	void dontMoveIf(std::function <bool ()> comp);

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
	Polygon poly;
	float vel = 500;
	Direction state = DOWN;
	bool diagOn = false;
	std::pair <Direction, Direction> state_diag;

	void setPolyInit();
	void setPoly();

	std::vector <Polygon*> offLimits; // polygons the character is not supposed to intersect
	std::vector <Polygon> offLimits_hard; // polygons the character is not supposed to intersect
	std::vector <std::function <bool(void)> > dontDo; // the bool functions character is not allowed to do
};