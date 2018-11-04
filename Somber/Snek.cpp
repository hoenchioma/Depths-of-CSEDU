#include "pch.h"
#include "Snek.h"

#include "EngineX/Point.h"

#include <cassert>

using namespace std;
using namespace sf;

inline Vector2f avg(sf::Vector2f a, Vector2f b, double ratio)
{
	float x = a.x * ratio + b.x * (1 - ratio);
	float y = a.y * ratio + b.y * (1 - ratio);
	return Vector2f(x, y);
}


Snek::Snek()
{
}


Snek::~Snek()
{
}

void Snek::Init(int length, GridPoint start, Grid* grid, sf::Color color, double delay, double scale)
{
	this->grid = grid;
	this->delay = delay;
	this->scalingFactor = scale;
	body.resize(length);
	bodyPrev.resize(length);
	bodyGridPrev.resize(length);
	// bodyGrid is not included because it is pushed, not directly assigned

	GridPoint i = start;

	RectangleShape tempRec(Vector2f(grid->BIT * scalingFactor, grid->BIT * scalingFactor));
	tempRec.setFillColor(color);
	tempRec.setOrigin(tempRec.getSize().x / 2.0, tempRec.getSize().y / 2.0);
	tempRec.setPosition(grid->toPoint(i));
	
	body[0] = tempRec;
	bodyGrid.push_back(i);

	grid->block(i);

	for (int j = 1; j < length; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			GridPoint temp = i + dirArr[k];
			if (grid->isInside(temp) && !grid->at(temp))
			{
				RectangleShape tempRec(Vector2f(grid->BIT * scalingFactor, grid->BIT * scalingFactor));
				tempRec.setFillColor(color);
				tempRec.setOrigin(tempRec.getSize().x / 2.0, tempRec.getSize().y / 2.0);
				tempRec.setPosition(grid->toPoint(temp));

				body[j] = tempRec;
				bodyGrid.push_back(temp);
				
				grid->block(temp); // block the body part of snek in grid

				i = temp; // increments i for next step

				goto loopEnd;
			}
		}
		throw std::logic_error("There is not enough space to generate snake body");
	loopEnd:
		continue;
	}

	headCor = bodyGrid.front();
	tailCor = bodyGrid.back();

	time.restart(); // reset the clock to 0
}

void Snek::Init(int length, sf::Vector2f start, Grid * grid, sf::Color color, double delay, double scale)
{
	Init(length, grid->realToGrid(start), grid, color, delay, scale);
}

bool Snek::update(float dt, sf::Vector2f targetPos, bool targetMoved)
{
	double timePassed = time.getElapsedTime().asSeconds();
	if (timePassed > delay)
	{
		moveStatic();

		if (targetMoved)
			path = grid->bfs(headCor, grid->realToGrid(targetPos));

		if (path.second) // only move if there is a valid path
		{
			if (path.first.empty()) return true;

			move(path.first.front());
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
	for (int i = 0; i < body.size(); i++)
		bodyGridPrev[i] = bodyGrid[i];

	bodyGrid[0] = des;

	grid->block(des);
	grid->free(tailCor);

	for (int i = 1; i < body.size(); i++)
		bodyGrid[i] = bodyGridPrev[i - 1];

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

void Snek::drawTo(sf::RenderWindow * app)
{
	for (auto& i : body) app->draw(i);
}
