#include "Grid.h"

#include <algorithm>

using namespace std;
using namespace sf;


Grid::Grid()
{
}

Grid::~Grid()
{
}

void Grid::Init(float canvasX, float canvasY, int BIT)
{
	this->canvasX = canvasX;
	this->canvasY = canvasY;
	sizeX = canvasX / BIT;
	sizeY = canvasY / BIT;

	//grid.Init(sizeY, sizeX, false);
}

void Grid::insert(sf::FloatRect rect)
{
}

void Grid::block(int x, int y)
{
	//grid[y][x] = true;
}

Point Grid::toPoint(int x, int y)
{
	return Point();
}
