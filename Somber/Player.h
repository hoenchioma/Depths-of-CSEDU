#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"

class Player
{
public:
	Player() {}
	~Player() {}

	int health;
	sf::Sprite object;
	std::vector<Bullet> bullets;
	void Init(sf::Texture *texture)
	{
		health = 150;
		object.setTexture(*texture);
	}
};
