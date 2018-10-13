#include "floor1.h"

#include "EngineX/Utility.h"
#include "boss1.h"

#include <iostream>

using namespace sf;
using namespace std;

const float wallOffSetX = 30;
const float wallOffSetY = 66;
const float revOffSetX = 11;
const float revOffSetY = 10;

void floor1::Init(Engine* game)
{
	cout << "scene created" << endl;

	///////////////// views //////////////////////////
	view.setCenter(game->width / 2, game->height / 2);
	view.setSize(game->width, game->height);
	
	////////////// main character ////////////////////
	if (!spriteSheet.loadFromFile("res/running_1.png"))
	{
		cerr << "can't load texture 1" << endl;
	}
	MainChar.Init(spriteSheet, 0.1f, 300.f);
	MainChar.setScale(1.4f, 1.4f);
	MainChar.setOrigin(MainChar.getTextureRect().width / 2.0, MainChar.getTextureRect().height / 2.0);
	MainChar.setPosition(game->width / 2.0, game->height / 2.0);
	///MainChar.setPosition(0, 0);

	////////////////// background ///////////////////////
	if (!backgroundImage.loadFromFile("res/floor1_back_2.png"))
	{
		cerr << "can't load texture 2" << endl;
	}
	background.setTexture(backgroundImage);
	background.setScale(1.35, 1.35);
	background.setOrigin(0, 0);
	background.setPosition(0, 0);

	if (!doorImage.loadFromFile("res/door.png"))
	{
		cerr << "can't load texture 3" << endl;
	}
	Door.Init(doorImage);
	Door.setScale(0.85, 0.85);
	Door.setPosition(110, 5);

	/////////////////// coins //////////////////////
	if (!coinSpriteSheet.loadFromFile("res/coin_gold.png"))
	{
		cerr << "can't load texture 3" << endl;
	}
	for (auto& coin : coins)
	{
		coin.setSpriteSheet(coinSpriteSheet);
		coin.addSheet(AniSprite::dir::horizontal, coinSpriteSheet.getSize().x / 8, coinSpriteSheet.getSize().y);
		coin.setDelay(0.1);
		coin.setScale(1.25, 1.25);
		///coin.setOrigin(coin.getSize().x / 2, coin.getSize().y / 2);
		coin.setPosition(
			wallOffSetX + rand() % (int) (background.getGlobalBounds().width - wallOffSetX - revOffSetX - coin.getSize().x),
			wallOffSetY + rand() % (int) (background.getGlobalBounds().height - wallOffSetY - revOffSetY - coin.getSize().y)
		);
	}

	/////////////// dark effect /////////////////////////
	Uint8 light = 150; // the lower this value the more darker
	Door.setColor(Color(light, light, light));
	MainChar.setColor(Color(light, light, light));
	background.setColor(Color(light, light, light));
	///for (auto& coin : coins) coin.setColor(Color(light, light, light));
}

void floor1::Cleanup()
{
}

void floor1::Pause()
{
	MainChar.running = false;
	pause = true;
}

void floor1::Resume()
{
	pause = false;
}

void floor1::togglePause()
{
	if (this->pause) this->Resume();
	else this->Pause();
}

void floor1::HandleEvents(Engine * game, Event * event)
{
	// Key release handle
	if (event->type == Event::EventType::KeyReleased)
	{
		for (auto& i : KeyArr)
		{
			if (event->key.code == i)
			{
				MainChar.moveOff();
			}
		}
	}

	if (event->type == Event::EventType::KeyPressed)
	{
		switch (event->key.code)
		{
		case Keyboard::Escape:
			togglePause();
			break;
		case Keyboard::E:
			if (MainChar.getGlobalBounds().intersects(Door.getGlobalBounds()))
			{
				cout << "Door Opened" << endl;
				Door.open();
			}
			break;
		default:
			break;
		}
	}
}

void floor1::Update(Engine * game, double dt)
{
	// setting it to false after any scene change occurs
	enteringDoor = false;

	if (!pause)
	{
		// Key press handle, character movement
		for (auto& i : KeyArr)
		{
			if (Keyboard::isKeyPressed(i))
			{
				MainChar.moveOn(KeyMap.at(i));
			}
		}

		bool intersection = MainChar.getGlobalBounds().intersects(Door.getGlobalBounds());

		// so that the character sprite cannot go out of bounds
		// when the player tries to go out of bounds setPosition s to the boundary point
		if (MainChar.getPosition().x - MainChar.getSize().x / 2 < wallOffSetX - 10)
			MainChar.setPosition(wallOffSetX - 10 + MainChar.getSize().x / 2, MainChar.getPosition().y);
		if (MainChar.getPosition().x > background.getGlobalBounds().width - revOffSetX)
			MainChar.setPosition(background.getGlobalBounds().width - revOffSetX, MainChar.getPosition().y);
		if (MainChar.getPosition().y > background.getGlobalBounds().height - revOffSetY)
			MainChar.setPosition(MainChar.getPosition().x, background.getGlobalBounds().height - revOffSetY);

		////////////////// Door Logic /////////////////////
		// special case logic for door
		// character can only enter door region if door is open
		// character cannot enter wall region
		if (Door.doorState == door::state::CLOSED)
		{
			if (MainChar.getPosition().y + MainChar.getSize().y / 2 < wallOffSetY + 40)
				MainChar.setPosition(MainChar.getPosition().x, wallOffSetY + 40 - MainChar.getSize().y / 2);
			// 40 so that the character can partially enter the wall for a pseudo 3d effect
		}
		else
		{
			if (!intersection)
			{
				if (MainChar.getPosition().y + MainChar.getSize().y / 2 < wallOffSetY + 40)
					MainChar.setPosition(MainChar.getPosition().x, wallOffSetY + 40 - MainChar.getSize().y / 2);
				// 40 so that the character can partially enter the wall for a pseudo 3d effect
			}
		}

		if (intersection)
		{
			if (MainChar.getPosition().y < 50)
			{
				///////// scene change /////////////
				pushScene(game, boss1::getInstance());
				enteringDoor = true;
				//sets position outside door to prevent instant re-entry
				MainChar.setPosition(MainChar.getPosition().x, wallOffSetY);
				//changes the direction downward for when the player returns to scene
				MainChar.moveOn(Direction::DOWN); 
				MainChar.moveOff();
			}
		}

		MainChar.update(dt);

		///////////////// View Logic /////////////////////
		// so that camera/view doesn't go out of bounds
		if (MainChar.getPosition().x >= game->width / 2
			and MainChar.getPosition().x + game->width / 2 <= background.getGlobalBounds().width)
		{
			view.setCenter(MainChar.getPosition().x, view.getCenter().y);
		}
		if (MainChar.getPosition().y >= game->height / 2
			and MainChar.getPosition().y + game->height / 2 <= background.getGlobalBounds().height)
		{
			view.setCenter(view.getCenter().x, MainChar.getPosition().y);
		}
		game->app->setView(view);

		////////////// Coin Logic //////////////////////
		for (auto& coin : coins)
		{
			if (coin.getGlobalBounds().intersects(MainChar.getGlobalBounds()))
			{
				coinCollected++;
				coin.setPosition((int) 1e7, (int) 1e7);
				// sets the coins way outside the screen
			}
		}
	}
}

void floor1::Draw(RenderWindow * app)
{
	app->draw(background);

	Door.drawTo(app);
	if (!enteringDoor) MainChar.drawTo(app);
	for (auto& coin : coins) coin.drawTo(app);
}
