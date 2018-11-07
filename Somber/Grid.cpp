#include "Grid.h"

#include <algorithm>
#include <queue>

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
	this->sizeX = canvasX / BIT;
	this->sizeY = canvasY / BIT;
	this->BIT = BIT;

	//cout << sizeX << " " << sizeY << endl;

	blocked.Init(sizeY, sizeX, false);
	visited.Init(sizeY, sizeX);
	parent.Init(sizeY, sizeX);
	level.Init(sizeY, sizeX);

	/*cout << grid.sizeX() << endl;
	cout << grid.sizeY() << endl;*/
}

void Grid::fill(Maze & maze)
{
	for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeY; j++)
			blocked.at(i, j) = maze[i][j];
}

void Grid::insert(sf::FloatRect rect)
{
	int top		= realToGrid(rect.top);
	int bottom	= realToGrid(rect.top + rect.height);
	int left	= realToGrid(rect.left);
	int right	= realToGrid(rect.left + rect.width);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			block(i, j);
}

GridPoint Grid::randomPoint()
{
	int x, y;
	do
	{
		x = rand() % sizeX;
		y = rand() % sizeY;
	} 
	while (at({ x, y }));
	return GridPoint(x, y);
}

PathPair Grid::bfs(GridPoint src, GridPoint des)
{
	//sf::Clock timer;

	if (src == des) return { Path(), true };
	
	queue <GridPoint> q;
	visited.fill(false);

	bool found = false;

	q.push(src);
	visited.at(src) = true;

	while (!q.empty())
	{
		auto curr = q.front();

		if (curr == des)
		{
			found = true;
			break;
		}

		for (auto i : dirArr)
		{
			auto temp = curr + i;
			if (isInside(temp) and !this->at(temp) and !visited.at(temp))
			{
				parent.at(temp) = curr;
				level.at(temp) = level.at(curr) + 1;
				visited.at(temp) = true;

				q.push(temp);
			}
		}

		random_shuffle(dirArr, dirArr + 4); // shuffles the direction array for less rigid movement

		q.pop();
	}

	Path ans;
	if (found)
	{
		// make a Path (deque) of the path from src to des (in reverse order)
		for (auto i = des; i != src; i = parent.at(i)) ans.push_front(i); // fills the deque in reverse order
	}

	//cout << timer.getElapsedTime().asMilliseconds() << endl;
	return { ans, found };
}
