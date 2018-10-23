#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "EngineX/AniSprite.h"
#include "EngineX/Polygon.h"

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

