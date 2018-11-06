#pragma once

/*
	Class to generate walls for the Grid (maze)
*/

#include <SFML/Graphics.hpp>

#include <vector>

#include "Grid.h"

#define PURPLE sf::Color(148, 0, 211)

class Walls
{
public:
	Walls() {}
	Walls(Grid* grid, sf::Color color = PURPLE) { Init(grid, color); }
	Walls(Grid* grid, sf::Texture& tex) { Init(grid, tex); }
	~Walls() {}

	// loading coloured rectangles
	void Init(Grid* grid, sf::Color color = PURPLE);
	// loading textures
	void Init(Grid* grid, sf::Texture& tex);

	// draws in two parts so that player can go over and under it dpending on position (pseudo 3d effect)
	void drawTo1(sf::RenderWindow* app, sf::Vector2f pos);
	void drawTo2(sf::RenderWindow* app);

private:
	// vector of rects representing the walls
	std::vector <sf::RectangleShape> rects;
	std::vector <sf::Sprite> sprites;
	Grid* grid;

	// keeps track of how much is drawn on first draw
	int secondDrawStart = 0;
};

