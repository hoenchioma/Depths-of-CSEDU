#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class bullet
{
public:
	sf::Sprite object;
	double bulletMulX;
	double bulletMulY;
	double dis;
	bullet(sf::Texture *texture, sf::Vector2f position, sf::Vector2i click)
	{
		object.setTexture(*texture);
		object.setScale(.06, .06);
		object.setPosition(position);
		bulletMulX = click.x - position.x;
		bulletMulY = click.y - position.y;
		dis = sqrt(pow(bulletMulX, 2) + pow(bulletMulY, 2));
		bulletMulX /= dis;
		bulletMulY /= dis;
	}
	~bullet() {}
};
