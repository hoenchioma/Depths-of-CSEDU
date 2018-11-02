#include "Grid.h"

#include <algorithm>

using namespace std;
using namespace sf;

const int PRESITION = 1000;


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

	grid.Init(sizeY, sizeX, false);
}

void Grid::insert(sf::FloatRect rect)
{
}

void Grid::block(int x, int y)
{
	grid[y][x] = true;
}

void Grid::block(std::pair<int, int> cor)
{
	block(cor.first, cor.second);
}

void Grid::free(int x, int y)
{
	grid[y][x] = false;
}

void Grid::free(std::pair<int, int> cor)
{
	free(cor.first, cor.second);
}

Point Grid::toPoint(int x, int y)
{
	return Point(BIT*x - BIT / 2.0, BIT*y / BIT / 2.0);
}

std::pair<int, int> Grid::realToGrid(sf::Vector2f vec)
{
	int tempX = vec.x * PRESITION;
	int tempY = vec.y * PRESITION;
	return std::pair<int, int>();
}
