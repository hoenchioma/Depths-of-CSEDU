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

	float health = 150;
	std::vector<Bullet> bullets;				//uses bullets as vector
};
