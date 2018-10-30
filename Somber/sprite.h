#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "bullet.h"

class sprite
{
public:
	int health;
	sf::Sprite object;
	std::vector<bullet> bullets;
	sprite(sf::Texture *texture)
	{
		health = 150;
		object.setTexture(*texture);
	}
	~sprite() {}
};
