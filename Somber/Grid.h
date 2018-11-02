#pragma once

/*
	Grid to apply BFS on
	-based on Array2d class
	
	Clarifications:
	Real co-ordinates: co-ordinates on the game screen (expressed as Vector2f or two floats)
	Grid co-ordinates: co-ordinates on the grid (two integer co-ordinates)
*/

#include <SFML/Graphics.hpp>

#include "EngineX/Point.h"
#include "Array2d.h"

#include <utility>

class Grid
{
public:
	Grid();
	~Grid();

	void Init(float canvasX, float canvasY, int BIT);

	size_t sizeX;
	size_t sizeY;

	float canvasX;
	float canvasY;

	int BIT;

	void insert(sf::FloatRect rect);

	// convert point from real co-ordinates to grid co-ordinates
	std::pair <int, int> realToGrid(sf::Vector2f vec);

	// block a point in the grid (make it a barrier in bfs)
	void block(int x, int y);
	void block(std::pair <int, int> cor);
	
	// free a point in the grid (remove it as a barrier in bfs)
	void free(int x, int y);
	void free(std::pair <int, int> cor);

	// convert point from grid co-ordinates to real co-ordinates
	Point toPoint(int x, int y);

private:
	Array2d <bool> grid;
};

