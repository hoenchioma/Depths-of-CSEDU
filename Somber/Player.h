#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Bullet.h"
#include "MainChar.h"

#include <vector>

class Player: public MainChar
{
public:
	Player() {}
	~Player() {}

	int health = 150;
	//sf::Sprite object;
	std::vector<Bullet> bullets;
	/*void Init(sf::Texture *texture)
	{
		health = 150;
		object.setTexture(*texture);
	}*/
};
