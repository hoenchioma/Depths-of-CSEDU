#include "pch.h"
#include "Snek.h"

#include "EngineX/Point.h"

using namespace std;
using namespace sf;


/////////////// Global functions and variables ///////////////////////

// returns the weighted average between two points
inline Vector2f avg(sf::Vector2f a, Vector2f b, double ratio)
{
	float x = a.x * ratio + b.x * (1 - ratio);
	float y = a.y * ratio + b.y * (1 - ratio);
	return Vector2f(x, y);
}

// converting GridPoint difference to direction
inline Direction snekDirMap(GridPoint a)
{
	if (a == GridPoint(1, 0))	return RIGHT;
	if (a == GridPoint(-1, 0))	return LEFT;
	if (a == GridPoint(0, 1))	return DOWN;
	if (a == GridPoint(0, -1))	return UP;
	//if (a == GridPoint(0, 0))	return UP;
}

// converting Direction to rotation angle (for corner/joint piece)
const std::map <std::pair <Direction, Direction > , float> cornerAngle =
{
	{{UP, RIGHT},	270},	
	{{UP, LEFT},	0},
	{{DOWN, RIGHT}, 180},
	{{DOWN, LEFT},	90},
	{{LEFT,	UP},	180},
	{{LEFT, DOWN},	270},
	{{RIGHT, UP},	90},
	{{RIGHT, DOWN}, 0},
};

// converting direction to rotation angle
const std::map <Direction, float> dirToAngle =
{
	{RIGHT, 90},
	{LEFT, 270},
	{UP, 0},
	{DOWN, 180}
};

////////////////////////////////////////////////////////////////



Snek::Snek()
{
}


Snek::~Snek()
{
}

//void Snek::Init(int length, GridPoint start, Grid* grid, sf::Color color, double delay, double scale)
//{
//	this->grid = grid;
//	this->delay = delay;
//	this->scalingFactor = scale;
//	body.resize(length);
//	bodyGridPrev.resize(length);
//	// bodyGrid is not included because it is pushed, not directly assigned
//
//	GridPoint i = start;
//
//	// the head
//	RectangleShape tempRec(Vector2f(grid->BIT * scalingFactor, grid->BIT * scalingFactor));
//	tempRec.setFillColor(Color::Green);
//	tempRec.setOrigin(tempRec.getSize().x / 2.0, tempRec.getSize().y / 2.0);
//	tempRec.setPosition(grid->toPoint(i));
//	
//	body[0] = tempRec;
//	bodyGrid.push_back(i);
//
//	grid->block(i);
//
//	for (int j = 1; j < length; j++)
//	{
//		for (int k = 0; k < 4; k++)
//		{
//			GridPoint temp = i + dirArr[k];
//			if (grid->isInside(temp) && !grid->at(temp))
//			{
//				RectangleShape tempRec(Vector2f(grid->BIT * scalingFactor, grid->BIT * scalingFactor));
//				tempRec.setFillColor(color);
//				tempRec.setOrigin(tempRec.getSize().x / 2.0, tempRec.getSize().y / 2.0);
//				tempRec.setPosition(grid->toPoint(temp));
//
//				body[j] = tempRec;
//				bodyGrid.push_back(temp);
//				
//				grid->block(temp); // block the body part of snek in grid
//
//				i = temp; // increments i for next step
//
//				goto loopEnd;
//			}
//		}
//		throw std::logic_error("There is not enough space to generate snake body");
//	loopEnd:
//		continue;
//	}
//
//	headCor = bodyGrid.front();
//	tailCor = bodyGrid.back();
//
//	time.restart(); // reset the clock to 0
//}

void Snek::Init(int length, GridPoint start, Grid* grid, sf::Color color, double delay, double scale)
{
	this->grid = grid;
	this->delay = delay;
	this->scalingFactor = scale;
	uncoiled = false;
	_uncoilCount = length;
	path = { Path(), false };

	body.resize(length);
	bodyGrid.resize(length);
	bodyGridPrev.resize(length);
	bodyDir.resize(length);
	bodyDirPrev.resize(length);

	// if the start point is a blocked point move it randomly until it's not a blocked point
	while (grid->at(start))	start = start + dirArr[rand() % 4];

	joint.setSize(Vector2f(grid->BIT * scalingFactor, grid->BIT * scalingFactor));
	joint.setOrigin(joint.getSize().x / 2.0, joint.getSize().y / 2.0);
	//joint.setFillColor(Color::Green);

	RectangleShape tempRec(Vector2f(grid->BIT * scalingFactor, grid->BIT * scalingFactor));
	//tempRec.setFillColor(Color::Green);
	tempRec.setOrigin(tempRec.getSize().x / 2.0, tempRec.getSize().y / 2.0);
	tempRec.setPosition(grid->toPoint(start));
	grid->at(start) = true;

	// set all the body blocks at the same point so the snake starts coiled
	for (int i = 0; i < length; i++)
	{
		body[i] = tempRec;
		bodyGrid[i] = start;
		bodyDir[i] = UP;
		bodyDirPrev[i] = UP;
	}

	headCor = bodyGrid.front();
	tailCor = bodyGrid.back();

	eating = false;
	
	time.restart(); // reset the clock to 0
}

void Snek::Init(int length, sf::Vector2f start, Grid * grid, sf::Color color, double delay, double scale)
{
	Init(length, grid->realToGrid(start), grid, color, delay, scale);
}

void Snek::setTexture(const sf::Texture & head, const sf::Texture & tail, const sf::Texture & mid, const sf::Texture & joint)
{
	this->joint.setTexture(&joint);
	for (auto& i : body) i.setTexture(&mid);
	body.front().setTexture(&head);
	body.back().setTexture(&tail);
	tailTex = &tail;
}

void Snek::preCalculateBFS(sf::Vector2f targetPos)
{
	this->path = grid->bfs(headCor, grid->realToGrid(targetPos));
}

bool Snek::update(float dt, sf::Vector2f targetPos)
{
	double timePassed = time.getElapsedTime().asSeconds();
	if (timePassed > delay)
	{
		moveStatic();

		if (path.first.empty() || grid->realToGrid(targetPos) != path.first.back())
			path = grid->bfs(headCor, grid->realToGrid(targetPos));

		if (path.second) // only move if there is a valid path
		{
			if (path.first.empty()) return true;

			// setting variables for proper eating animation
			if (path.first.size() <= 1) eating = true;
			else eating = false;

			move(path.first.front());
			direcUpdate();
			path.first.pop_front();
		}

		time.restart();
	}
	else
	{
		movePartial(timePassed / delay);
	}

	return false;
}

//void Snek::move(GridPoint des)
//{
//	for (int i = 0; i < body.size(); i++)
//	{
//		bodyPrev[i] = body[i].getPosition();
//		bodyGridPrev[i] = bodyGrid[i];
//	}
//
//	body[0].setPosition(grid->toPoint(des));
//	bodyGrid[0] = des;
//
//	grid->block(des);
//	grid->free(tailCor);
//
//	for (int i = 1; i < body.size(); i++)
//	{
//		body[i].setPosition(bodyPrev[i - 1]);
//		bodyGrid[i] = bodyGridPrev[i - 1];
//	}
//
//	tailCor = bodyGrid.back();
//	headCor = bodyGrid.front();
//}

void Snek::move(GridPoint des)
{
	// keep track of whether the snake is uncoiled
	if (!uncoiled) _uncoilCount--;
	// if fully uncoiled set flag to true
	if (_uncoilCount == 0) uncoiled = true;
	
	for (int i = 0; i < body.size(); i++)
	{
		bodyGridPrev[i] = bodyGrid[i];
		bodyDirPrev[i] = bodyDir[i];
	}

	// calculates the direction of the snek head
	bodyDir[0] = snekDirMap(des - bodyGrid[0]);

	bodyGrid[0] = des;

	grid->block(des);
	// only when fully uncoiled each snake body cell covers one grid block
	if (uncoiled) grid->free(tailCor);

	for (int i = 1; i < body.size(); i++)
	{
		bodyGrid[i] = bodyGridPrev[i - 1];
		bodyDir[i] = bodyDirPrev[i - 1];
	}

	tailCor = bodyGrid.back();
	headCor = bodyGrid.front();
}

void Snek::movePartial(double progress)
{
	for (int i = 0; i < body.size(); i++)
	{
		body[i].setPosition(
			avg(
				grid->toPoint(bodyGrid[i]), 
				grid->toPoint(bodyGridPrev[i]), 
				progress
			)
		);
	}
}

void Snek::moveStatic()
{
	for (int i = 0; i < body.size(); i++)
		body[i].setPosition(grid->toPoint(bodyGrid[i]));
}

void Snek::direcUpdate()
{
	for (int i = 0; i < body.size(); i++)
	{
		body[i].setRotation(dirToAngle.at(bodyDir[i]));
	}
}

void Snek::cut(int n)
{
	// do not cut snek when not uncoiled
	// (causes weird blocked parts left on grid)
	if (!uncoiled) return;

	for (int i = 1; i <= n; i++)
	{
		if (body.size() == 2) break;
		body.pop_back();

		grid->free(bodyGrid.back());

		bodyGrid.pop_back();
		bodyGridPrev.pop_back();
	}

	tailCor = bodyGrid.back();
	headCor = bodyGrid.front();

	body.back().setTexture(tailTex);
}

//void Snek::drawCorners(sf::RenderWindow* app)
//{
//	/*CircleShape corner(grid->BIT/2.0 * scalingFactor);
//	corner.setOrigin(corner.getRadius(), corner.getRadius());*/
//	RectangleShape corner(Vector2f(grid->BIT * scalingFactor, grid->BIT * scalingFactor));
//	corner.setOrigin(corner.getSize().x / 2.0, corner.getSize().y / 2.0);
//
//	corner.setFillColor(Color::Green);
//
//	Orientaion orient, prevOrient;
//	if (bodyGrid[0].x == bodyGrid[1].x) prevOrient = vertical;
//	else prevOrient = horizontal;
//
//	for (int i = 2; i < body.size(); i++)
//	{
//		if (bodyGrid[i - 1].x == bodyGrid[i].x) orient = vertical;
//		else orient = horizontal;
//
//		if (orient != prevOrient)
//		{
//			corner.setPosition(grid->toPoint(bodyGrid[i - 1]));
//			app->draw(corner);
//
//			prevOrient = orient;
//		}
//	}
//
//	// corner case handling for snakes' tail
//	corner.setPosition(grid->toPoint(bodyGrid.back()));
//	app->draw(corner);
//}

void Snek::drawCorners(sf::RenderWindow * app)
{
	for (int i = 0; i < body.size() - 1; i++)
	{
		if (bodyDir[i] != bodyDir[i + 1])
		{
			//joint.setRotation(dirToAngle.at(bodyDir[i]));
			joint.setRotation(cornerAngle.at({ bodyDir[i + 1], bodyDir[i]}));
			joint.setPosition(grid->toPoint(bodyGrid[i + 1]));
			app->draw(joint);
		}
	}
}

void Snek::drawTo1(sf::RenderWindow * app)
{
	if (!eating)
	{
		for (auto& i : body) app->draw(i);
		drawCorners(app); // draw the corners
	}
}

void Snek::drawTo2(sf::RenderWindow * app)
{
	if (eating)
	{
		for (auto& i : body) app->draw(i);
		drawCorners(app); // draw the corners
	}
}

