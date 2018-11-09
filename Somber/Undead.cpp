#include "Undead.h"

Undead::Undead(sf::Texture * texture1, sf::Texture * texture2, sf::Texture * texture3)
{
	maxHealth = rand() % 3 + 1;
	position = rand() % 7 + 1;
	health = maxHealth;
	if (maxHealth == 1)
		object.setTexture(*texture1);
	else if (maxHealth == 2)
		object.setTexture(*texture2);
	else if (maxHealth == 3)
		object.setTexture(*texture3);
	object.setScale(.1, .1);
	if (position == 1)
		object.setPosition(930, 90);//
	else if (position == 2)
		object.setPosition(755, 580);//
	else if (position == 3)
		object.setPosition(1000, 345);//
	else if (position == 4)
		object.setPosition(570, 90);//
	else if (position == 5)
		object.setPosition(80, 580);//
	else if (position == 6)
		object.setPosition(400, 580);//
	else if (position == 7)
		object.setPosition(210, 90);//
}
