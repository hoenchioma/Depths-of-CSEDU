#pragma once

/*
	A pair of two ints
	serves as co-ordinates in Grid class
*/

class GridPoint
{
public:
	GridPoint() {}
	GridPoint(int x_cordinate, int y_cordinate) : x(x_cordinate), y(y_cordinate) {}
	~GridPoint() {}

	int x, y;

	inline GridPoint operator+(const GridPoint& a) const { return GridPoint(this->x + a.x, this->y + a.y); }
	inline GridPoint operator-(const GridPoint& a) const { return GridPoint(this->x - a.x, this->y - a.y); }
	inline bool operator==(const GridPoint& a) const { return (this->x == a.x && this->y == a.y); }
	inline bool operator!=(const GridPoint& a) const { return !(this->x == a.x && this->y == a.y); }

	inline GridPoint up() const { return GridPoint(x, y - 1); }
	inline GridPoint down() const { return GridPoint(x, y + 1); }
	inline GridPoint right() const { return GridPoint(x + 1, y); }
	inline GridPoint left() const { return GridPoint(x - 1, y); }

	// for IO operations
	friend std::ostream& operator << (std::ostream& out, const GridPoint& point)
	{
		out << point.x << "i + " << point.y << "j";
		return out;
	}
	friend std::istream& operator >> (std::istream& in, GridPoint& point)
	{
		in >> point.x >> point.y;
		return in;
	}
};

