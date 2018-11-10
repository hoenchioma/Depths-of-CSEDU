#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Chairs
{
public:
	Texture texture;
	Sprite object;
	Chairs()
	{
		texture.loadFromFile("res/roomChair.png");
		object.setTexture(texture);
		object.setScale(.1, .1);
	}
	~Chairs() {}
};
