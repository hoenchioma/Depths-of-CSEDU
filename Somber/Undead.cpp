#include "Undead.h"

//Undead::Undead(sf::Texture * texture1, sf::Texture * texture2, sf::Texture * texture3)
//{
//	maxHealth = rand() % 3 + 1;
//	position = rand() % 7 + 1;
//	health = maxHealth;
//	if (maxHealth == 1)
//		object.setTexture(*texture1);
//	else if (maxHealth == 2)
//		object.setTexture(*texture2);
//	else if (maxHealth == 3)
//		object.setTexture(*texture3);
//	object.setScale(.1, .1);
//	if (position == 1)
//		object.setPosition(930, 90);//
//	else if (position == 2)
//		object.setPosition(755, 580);//
//	else if (position == 3)
//		object.setPosition(1000, 345);//
//	else if (position == 4)
//		object.setPosition(570, 90);//
//	else if (position == 5)
//		object.setPosition(80, 580);//
//	else if (position == 6)
//		object.setPosition(400, 580);//
//	else if (position == 7)
//		object.setPosition(210, 90);//
//}

Undead::Undead(sf::Texture runL[], sf::Texture runR[], sf::Texture attL[], sf::Texture attR[])
{
	maxHealth = rand() % 3 + 1;
	position = rand() % 7 + 1;

	int choice = maxHealth - 1;
	health = maxHealth;
	
	// running animation
	ani[0].setSpriteSheet(runL[choice]);
	ani[1].setSpriteSheet(runR[choice]);
	ani[2].setSpriteSheet(attL[choice]);
	ani[3].setSpriteSheet(attR[choice]);

	for (int i = 0; i < 4; i++)
	{
		ani[i].addSheet(
			AniSprite::horizontal,
			runL[0].getSize().x / 6.0,
			runL[0].getSize().y
		);
	}

	// setting the position
	if (position == 1)
		setPosition(sf::Vector2f(150, 150));
	else if (position == 2)
		setPosition(sf::Vector2f(450, 150));
	else if (position == 3)
		setPosition(sf::Vector2f(950, 150));
	else if (position == 4)
		setPosition(sf::Vector2f(150, 550));
	else if (position == 5)
		setPosition(sf::Vector2f(450, 550));
	else if (position == 6)
		setPosition(sf::Vector2f(950, 550));
	else if (position == 7)
		setPosition(sf::Vector2f(1150, 550));

	setScale(sf::Vector2f(0.5f, 0.5f));
	// the third type is bigger
	if (choice == 2) setScale(sf::Vector2f(0.8f, 0.8f));
}

void Undead::pause()
{
	for (int i = 0; i < 4; i++) ani[i].freeze();
}

void Undead::resume()
{
	for (int i = 0; i < 4; i++) ani[i].unfreeze();
}

void Undead::drawTo(sf::RenderWindow * app)
{
	for (int i = 0; i < 4; i++) ani[mode].drawTo(app);
}
