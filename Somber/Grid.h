#pragma once

#include "EngineX/Point.h"
#include "Array2d.h"

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
	void block(int x, int y);

	Point toPoint(int x, int y);

private:
	//Array2d <bool> grid;
};

