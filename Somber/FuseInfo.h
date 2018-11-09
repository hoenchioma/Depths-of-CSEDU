#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class FuseInfo
{
public:
	float health = 100;
	float X;
	float Y;
	bool fuseState;
	sf::Texture fuseOpenTex;
	sf::Texture fuseCloseTex;
	sf::Sprite fuseBox;
	sf::RectangleShape fuseHealthBar;
	FuseInfo()
	{
		health = 100;
		fuseCloseTex.loadFromFile("res/fuseClosed.png");
		fuseOpenTex.loadFromFile("res/fuseOpened.png");
		fuseBox.setTexture(fuseCloseTex);
		fuseBox.setScale(.1, .1);
		fuseState ;
	}
	~FuseInfo() {}

};