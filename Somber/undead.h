#pragma once

#include <SFML/Graphics.hpp>

class Undead
{
public:
	Undead(sf::Texture *texture1, sf::Texture *texture2, sf::Texture *texture3);

	sf::Sprite object;
	AniSprite a[4];
	int health;
	int maxHealth;
	int position;
};
