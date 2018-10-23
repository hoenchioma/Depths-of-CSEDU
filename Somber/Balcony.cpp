#include "pch.h"
#include "Balcony.h"

using namespace sf;

Balcony::Balcony()
{
}


Balcony::~Balcony()
{
}

void Balcony::Init(const std::vector <Point> & points, const sf::Texture & tops, const sf::Texture & bottoms, const sf::Texture& unders, const sf::Vector2f pos)
{
	top.setTexture(tops);
	top.setOrigin(tops.getSize().x / 2.f, tops.getSize().y / 2.f);
	top.setPosition(pos);
	bottom.setTexture(bottoms);
	bottom.setOrigin(bottoms.getSize().x / 2.f, bottoms.getSize().y / 2.f);
	bottom.setPosition(pos);
	under.setTexture(unders);
	under.setOrigin(unders.getSize().x / 2.f, unders.getSize().y / 2.f);
	under.setPosition(pos);

	FloatRect boundary = top.getGlobalBounds();
	for (const auto& i : points)
	{
		poly.vertex.push_back(i + Point(boundary.left, boundary.top));
	}
	poly.setCentre();
	poly.sideSet();
}

void Balcony::setBrightness(sf::Uint8 light = 255)
{
	top.setColor(Color(light, light, light));
	bottom.setColor(Color(light, light, light));
	under.setColor(Color(light, light, light));
}

void Balcony::setPosition(sf::Vector2f vec)
{
	top.setPosition(vec); 
	bottom.setPosition(vec);
	under.setPosition(vec);
}

void Balcony::setScale(sf::Vector2f scale)
{
	top.setScale(scale); 
	bottom.setScale(scale);
	under.setScale(scale);

	// centre focused scaling of the points
	for (int i = 0; i < poly.vertex.size(); i++)
	{
		poly.vertex[i].x = ((poly.vertex[i].x - poly.centre.x) * scale.x) + poly.centre.x;
		poly.vertex[i].y = ((poly.vertex[i].y - poly.centre.y) * scale.y) + poly.centre.y;
	}
	poly.sideSet();
}

void Balcony::setScale(float scale)
{
	top.setScale(scale, scale); 
	bottom.setScale(scale, scale);
	under.setScale(scale, scale);

	// centre focused scaling of the points
	for (int i = 0; i < poly.vertex.size(); i++)
	{
		poly.vertex[i] = ((poly.vertex[i] - poly.centre) * scale) + poly.centre;
	}
	poly.sideSet();
}

void Balcony::drawTop(sf::RenderWindow * app)
{
	app->draw(top);
	//poly.draw(app);
}

void Balcony::drawBottom(sf::RenderWindow * app)
{
	app->draw(under); 
	app->draw(bottom);
}
