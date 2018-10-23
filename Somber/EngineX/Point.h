#pragma once

#include <iostream>
#include <cmath>

struct Point
{
	Point() {}
	Point(float a, float b): x(a), y(b) {}
	~Point() {}

	float x, y;

	// for implicit conversion from sf::Vector2f
	Point(const sf::Vector2f &a) : x(a.x), y(a.y) {}
	Point& operator=(const sf::Vector2f &a) { x = a.x, y = a.y; return *this; }
	operator sf::Vector2f() { return sf::Vector2f(x, y); }

	// overload of common arithmetic operators
	inline Point operator+(Point a) const { return Point(this->x + a.x, this->y + a.y); }
	inline Point operator-(Point a) const { return Point(this->x - a.x, this->y - a.y); }
	inline Point operator*(float a) const { return Point(this->x * a, this->y * a); }
	inline float operator*(Point a) const { return (this->x * a.x + this->y * a.y); } //dot product
	inline float mag() const { return sqrt(x * x + y * y); }
	inline Point unit() const { return Point(x / mag(), y / mag()); }
	inline Point perpL() const { return Point(-y, x); }
	inline Point perpR() const { return Point(y, -x); }

	inline sf::Vector2f vec() const { return sf::Vector2f(x, y); } // get a sf::Vector2f instance of the Point

	// for IO operations
	friend std::ostream& operator << (std::ostream& out, const Point& point)
	{
		out << point.x << "i + " << point.y << "j";
		return out;
	}
	friend std::istream& operator >> (std::istream& in, Point& point)
	{
		in >> point.x >> point.y;
		return in;
	}
};

