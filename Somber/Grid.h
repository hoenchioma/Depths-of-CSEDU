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

#include <utility>

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

	// block a portion in the grid corresponding to the rect
	void insert(sf::FloatRect rect);

	// convert point from grid co-ordinates to real co-ordinates
	Point toPoint(int x, int y);
	Point toPoint(GridPoint cor);

	// convert point from real co-ordinates to grid co-ordinates
	GridPoint realToGrid(sf::Vector2f vec);
	int realToGrid(float x);

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

