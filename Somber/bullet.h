#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cmath>

const double PIE = acos(-1.0);

class Bullet
{
public:
	sf::Sprite object;
	double bulletMulX;
	double bulletMulY;
	double dis;
	Bullet(sf::Texture *texture, sf::Vector2f position, sf::Vector2i click)
	{
		object.setTexture(*texture);
		object.setScale(.06, .06);
		object.setPosition(position);
		bulletMulX = click.x - position.x;
		bulletMulY = click.y - position.y;
		dis = sqrt(pow(bulletMulX, 2) + pow(bulletMulY, 2));
		bulletMulX /= dis;
		bulletMulY /= dis;

		float angle = atan((click.y - position.y) / (click.x - position.x)) * 180 / PIE;
		object.setRotation(angle);
	}
	~Bullet() {}
};
