#pragma once

/*
	Grid to apply BFS on
	(keeps track of blocked points)
	-based on Array2d class
*/
/*
	Clarifications:
	Real co-ordinates: co-ordinates on the game screen (expressed as Vector2f or two floats)
	Grid co-ordinates: co-ordinates on the grid (two integer co-ordinates)
*/

#include <SFML/Graphics.hpp>

#include "EngineX/Point.h"
#include "Array2d.h"
#include "GridPoint.h"
#include "Maze.h"

#include <utility>
#include <deque>

// precision for real world to grid convertion (mod operation)
#define PRECISION 1000

typedef std::deque<GridPoint> Path;
typedef std::pair<Path, bool> PathPair;

static GridPoint dirArr[4] =
{
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
};



class Grid
{
public:
	Grid();
	~Grid();

	size_t sizeX;
	size_t sizeY;

	float canvasX;
	float canvasY;

	int BIT = 0;
	
	void Init(float canvasX, float canvasY, int BIT);
	
	// fill the grid using maze
	void fill(Maze& maze);

	// block a portion in the grid corresponding to the rect
	void insert(sf::FloatRect rect);

	GridPoint randomPoint();

	// convert point from grid co-ordinates to real co-ordinates
	inline Point toPoint(int x, int y);
	inline Point toPoint(GridPoint cor);

	// convert point from real co-ordinates to grid co-ordinates
	inline GridPoint realToGrid(sf::Vector2f vec);
	inline int realToGrid(float x);

	// block a point in the grid (make it a barrier in bfs)
	inline void block(int x, int y) { blocked.at(y, x) = true; }
	inline void block(GridPoint cor) { blocked.at(cor) = true; }
	
	// free a point in the grid (remove it as a barrier in bfs)
	inline void free(int x, int y) { blocked.at(y, x) = false; }
	inline void free(GridPoint cor) { blocked.at(cor) = false; }

	inline bool isInside(int x, int y);
	inline bool isInside(GridPoint cor);

	// access the grid using gridPoint
	inline bool& at(GridPoint cor) { return blocked.at(cor); }

	// Path finding algorithm from src to des using BFS
	PathPair bfs(GridPoint src, GridPoint des);

private:
	// holds the blocked points in the grid
	Array2d <bool> blocked;

	// BFS variables
	Array2d <bool> visited;
	Array2d <GridPoint> parent;
	Array2d <int> level;
};




// inline function definitions

inline Point Grid::toPoint(int x, int y)
{
	return Point(BIT * x + BIT / 2.0, BIT * y + BIT / 2.0);
}

inline Point Grid::toPoint(GridPoint cor)
{
	return toPoint(cor.x, cor.y);
}

inline GridPoint Grid::realToGrid(sf::Vector2f vec)
{
	int tempY = realToGrid(vec.y);
	int tempX = realToGrid(vec.x);

	// correction
	if (tempY < 0) tempY = 0;
	if (tempY >= sizeY) tempY = sizeY - 1;
	if (tempX < 0) tempX = 0;
	if (tempX >= sizeX) tempX = sizeX - 1;

	//cout << tempY << " " << tempX << endl;

	return GridPoint(tempX, tempY);
}

inline int Grid::realToGrid(float x)
{
	int ans = round((double)((x - BIT / 2.0) * PRECISION) / (BIT * PRECISION));
	return ans;
}

inline bool Grid::isInside(int x, int y)
{
	return (x >= 0 && x < sizeX && y >= 0 && y < sizeY);
}

inline bool Grid::isInside(GridPoint cor)
{
	return isInside(cor.x, cor.y);
}

