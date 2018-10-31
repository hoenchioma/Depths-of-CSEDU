#pragma once

#include "Point.h"

#include <vector>

class Polygon
{
public:
	Polygon(): vertex(), side() {};
	Polygon(const std::vector <Point>& points, const Point& cen);
	Polygon(const std::vector <Point>& points);
	~Polygon() {};

	void setPoints(const std::vector <Point>& points, const Point& cen);
	void setPoints(const std::vector <Point>& points);
	void setCentre(const Point& cen);
	void setCentre();
	void sideSet();

	Point centre;
	std::vector <Point> vertex;
	std::vector <Point> side;

	// for convex polygon only
	// SAT collision detection
	// optimized for rectangle (this) and polygon (a) collision [for now]
	bool intersects(const Polygon& a);

	void draw(sf::RenderWindow* app); //for debugging purposes

	// for implicit conversion from sf::FloatRect
	Polygon(const sf::FloatRect &a);
	Polygon& operator=(const sf::FloatRect &a);
};

