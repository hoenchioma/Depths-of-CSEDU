#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "bullet.h"

class player
{
public:
	int health;
	sf::Sprite object;
	std::vector<bullet> bullets;
	player(sf::Texture *texture)
	{
		health = 150;
		object.setTexture(*texture);
	}
	~player() {}
};
