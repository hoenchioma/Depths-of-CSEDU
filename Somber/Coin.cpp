#include "pch.h"
#include "Coin.h"

#include "MainChar.h"


Coin::Coin()
{
}


Coin::~Coin()
{
}

bool Coin::collected(MainChar& mc)
{
	if (this->getGlobalBounds().intersects(mc.getGlobalBounds()))
	{
		this->setPosition((int) 1e7, (int) 1e7);
		if (soundSet) sound.play();
		return true;
	}
	return false;
}

void Coin::setSound(sf::SoundBuffer & buf)
{
	sound.setBuffer(buf);
	if (sound.getBuffer() != NULL) soundSet = true;
}
