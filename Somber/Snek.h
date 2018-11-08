#pragma once

#include <SFML/Graphics.hpp>

#include "EngineX/Utility.h"
#include "EngineX/eClock.h"
#include "Grid.h"

#include <vector>
#include <deque>




class Snek
{
public:
	Snek();
	~Snek();

	eClock time;
	
	void Init(int length, GridPoint start, Grid* grid, sf::Color color = sf::Color::Green, double delay = 0.2, double scale = 1);
	void Init(int length, sf::Vector2f start, Grid* grid, sf::Color color = sf::Color::Green, double delay = 0.2, double scale = 1);

	void setTexture(const sf::Texture& head, const sf::Texture& tail, const sf::Texture& mid, const sf::Texture& joint);
	
	// optional precalculation of bfs to target to prevent lag
	void preCalculateBFS(sf::Vector2f targetPos);

	// returns whether the snake has devoured the character
	bool update(float dt, sf::Vector2f targetPos);

	// linear interpolated movement
	void move(GridPoint des);
	void movePartial(double progress);
	void moveStatic();
	void direcUpdate();
	
	// cuts the length of the snake by n from behind
	void cut(int n);
	// set speed of snake
	inline void setDelay(double delay) { this->delay = delay; }
	inline double getDelay() { return this->delay; }
	inline float getLength() { return body.size(); }

	// draws corners interpolated fashion (to be drawn over snake)
	void drawCorners(sf::RenderWindow* app);
	void drawTo(sf::RenderWindow* app);

	GridPoint tailCor;
	GridPoint headCor;

private:
	Grid* grid;

	std::vector <sf::RectangleShape> body; // body of the snake
	std::vector <GridPoint> bodyGrid; // body positions in grid co-ordinates
	std::vector <GridPoint> bodyGridPrev; // prev body positions in grid co-ordinates
	std::vector <Direction> bodyDir; // body directions
	std::vector <Direction> bodyDirPrev; // prev body directions

	// joint/corner piece of snek
	sf::RectangleShape joint;
	const sf::Texture* tailTex;

	double delay = 0.2; //in seconds
	double scalingFactor = 1; // what multiple of BIT will the size of each body sell
	PathPair path = { Path(), false }; // active path the snake is following

	bool uncoiled = false;
	int _uncoilCount;
};

