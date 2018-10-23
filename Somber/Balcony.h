#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EngineX/Polygon.h"

#include <vector>

class Balcony
{
public:
	Balcony();
	~Balcony();

	// the point vector indicates the polygon points in local co-ordinates (origin top-left)
	void Init(const std::vector <Point> & points, const sf::Texture& tops, const sf::Texture& bottoms, const sf::Texture& unders, const sf::Vector2f pos);

	void setBrightness(sf::Uint8 light);
	void setPosition(sf::Vector2f vec);
	void setScale(sf::Vector2f scale);
	void setScale(float scale);
	Polygon& getPoly() { return poly; }

	void drawTop(sf::RenderWindow* app); // drawn over character (top half of balcony)
	void drawBottom(sf::RenderWindow* app); // drawn under character (bottom half of balcony)

private:
	sf::Sprite top; // top half of balcony
	sf::Sprite bottom; // bottom half of balcony
	sf::Sprite under; // picture visible through the balcony hole
	Polygon poly;
};

