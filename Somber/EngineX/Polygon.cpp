#include "Polygon.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <numeric>

using namespace std;

Polygon::Polygon(const std::vector<Point>& points, const Point& cen)
	:vertex(points), centre(cen)
{
	sideSet();
}

Polygon::Polygon(const std::vector<Point>& points)
	:vertex(points)
{
	sideSet();
	setCentre();
}

void Polygon::setPoints(const std::vector<Point>& points, const Point & cen)
{
	vertex = points;
	sideSet();
	setCentre(cen);
}

void Polygon::setPoints(const std::vector<Point>& points)
{
	vertex = points;
	sideSet();
	setCentre();
}

void Polygon::setCentre(const Point& cen)
{
	centre = cen;
}

void Polygon::setCentre()
{
	// sets the average of the points as the centre
	centre = Point(
		accumulate(vertex.begin(), vertex.end(), 0.f, [](float init, Point first) {return init + first.x; }) / vertex.size(),
		accumulate(vertex.begin(), vertex.end(), 0.f, [](float init, Point first) {return init + first.y; }) / vertex.size()
	);
}

void Polygon::sideSet()
{
	if (side.empty())
	{
		for (size_t i = 0; i < vertex.size() - 1; i++)
			side.push_back(vertex[i + 1] - vertex[i]);
		side.push_back(vertex[0] - vertex[vertex.size() - 1]);
	}
	else
	{
		for (size_t i = 0; i < vertex.size() - 1; i++)
			side[i] = (vertex[i + 1] - vertex[i]);
		side[vertex.size() - 1] = (vertex[0] - vertex[vertex.size() - 1]);
	}
}

bool Polygon::intersects(const Polygon & a)
{
	float magnitude;
	bool collision;
	Point perpUnit;

	for (size_t i = 0; i < a.side.size(); i++)
	{
		perpUnit = a.side[i].perpR().unit();
		magnitude = a.vertex[i] * perpUnit;
		collision = false;

		// check on which side of the centre the side is
		if (a.centre * perpUnit > magnitude)
		{
			for (const auto& j : this->vertex)
			{
				if (j * perpUnit >= magnitude)
				{
					collision = true;
					break;
				}
			}
		}
		else
		{
			for (const auto& j : this->vertex)
			{
				if (j * perpUnit <= magnitude)
				{
					collision = true;
					break;
				}
			}
		}

		if (!collision) return false;
		// if even collision with one side is false the intersection is false
		// the intersection is only true if collision is true for all sides
	}

	return true;
}

void Polygon::draw(sf::RenderWindow * app)
{
	sf::CircleShape point(5.f);
	point.setFillColor(sf::Color::Green);
	point.setOrigin(point.getRadius(), point.getRadius());
	for (const auto& i: vertex)
	{
		point.setPosition(i.vec());
		app->draw(point);
	}
	point.setPosition(centre.vec());
	app->draw(point);
}

Polygon::Polygon(const sf::FloatRect & a)
{
	// based on the assignment operator function
	*this = a;
}

Polygon & Polygon::operator=(const sf::FloatRect & a)
{
	float left = a.left;
	float right = a.left + a.width;
	float top = a.top;
	float bottom = a.top + a.height;

	setPoints({
		{left, top},
		{left, bottom},
		{right, bottom},
		{right, top},
	});

	return *this;
}


