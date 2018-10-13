#pragma once

#include "EngineX/AniSprite.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class MainChar;

class Coin: public AniSprite
{
public:
	Coin();
	~Coin();

	bool collected(MainChar& mc);
	void setSound(sf::SoundBuffer& buf);
	sf::Sound& getSound() { return sound; }

private:
	sf::Sound sound;
	bool soundSet = false;
};

