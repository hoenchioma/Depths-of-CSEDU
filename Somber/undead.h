#pragma once

#include <SFML/Graphics.hpp>

class Undead
{
public:
	Undead(sf::Texture runL[], sf::Texture runR[], sf::Texture attL[], sf::Texture attR[]);

	inline sf::Vector2f getPosition() const { return ani[0].getPosition(); }
	inline void setPosition(sf::Vector2f pos) { prevPosX = getPosition().x;  for (auto& i : ani) i.setPosition(pos); }
	inline void move(sf::Vector2f pos) { prevPosX = getPosition().x; for (auto& i : ani) i.move(pos); }
	inline void move(float x, float y) { prevPosX = getPosition().x; for (auto& i : ani) i.move(x, y); }
	inline void setOrigin(sf::Vector2f pos) { for (auto& i : ani) i.setOrigin(pos); }
	inline sf::FloatRect getGlobalBounds() { return ani[0].getGlobalBounds(); }
	inline void setScale(sf::Vector2f vec) { for (auto& i : ani) i.setScale(vec); }

	void pause();
	void resume();

	void drawTo(sf::RenderWindow* app);

	sf::Sprite object;
	// index 0 and 1 are left and right for running
	// index 2 and 3 are left and right for attack
	AniSprite ani[4];

	double prevPosX;

	bool eating = false;

	// the mode to be drawn
	int mode = 0;
	
	int health;
	int maxHealth;
	int position;
};
