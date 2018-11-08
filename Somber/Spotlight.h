#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#define RADIUS_SPOTLIGHT 150
#define DIAMETER_SPOTLIGHT 300

class Spotlight
{
public:
	float x, y, dirX = 1, dirY = 1;
	sf::CircleShape circleSpot;
	sf::Texture texture;
	Spotlight()
	{
		texture.loadFromFile("res/spotlight.png");
		dirX = 1; dirY = 1;
		circleSpot.setRadius(RADIUS_SPOTLIGHT);
		circleSpot.setPointCount(100);
		circleSpot.setTexture(&texture);
	}
	~Spotlight() {}
};