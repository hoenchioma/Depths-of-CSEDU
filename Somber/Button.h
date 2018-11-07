#pragma once

class Button
{
public:
	sf::Sprite objectAc;
	sf::Sprite object;
	Button() {}
	void Init(sf::Texture *textureAc, sf::Texture *texture, int valX, int valY)
	{
		objectAc.setTexture(*textureAc);
		object.setPosition(valX, valY);
		object.setTexture(*texture);
		objectAc.setPosition(-500, valY);
	}
	~Button() {}
};