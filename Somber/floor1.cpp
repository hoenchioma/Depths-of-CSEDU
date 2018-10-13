#include "Floor1.h"

#include "EngineX/Utility.h"
#include "Boss1.h"

#include <iostream>

using namespace sf;
using namespace std;

const float wallOffSetX = 30;
const float wallOffSetY = 66;
const float revOffSetX = 11;
const float revOffSetY = 10;

void Floor1::Init(Engine* game)
{
	cout << "scene created" << endl;

	///////////////// views //////////////////////////
	view.setCenter(game->width / 2, game->height / 2);
	view.setSize(game->width, game->height);
	
	////////////// main character ////////////////////
	if (!spriteSheet.loadFromFile("res/running_1.png"))
	{
		cerr << "can't load main character sprite texture" << endl;
	}
	mainChar.Init(spriteSheet, 0.1f, 300.f);
	mainChar.setScale(1.4f, 1.4f);
	mainChar.setOrigin(mainChar.getTextureRect().width / 2.0, mainChar.getTextureRect().height / 2.0);
	mainChar.setPosition(game->width / 2.0, game->height / 2.0);
	///mainChar.setPosition(0, 0);

	////////////////// background ///////////////////////
	if (!backgroundImage.loadFromFile("res/Floor1_back_2.png"))
	{
		cerr << "can't load background texture" << endl;
	}
	background.setTexture(backgroundImage);
	background.setScale(1.35, 1.35);
	background.setOrigin(0, 0);
	background.setPosition(0, 0);

	if (!DoorImage.loadFromFile("res/Door.png"))
	{
		cerr << "can't load door texture" << endl;
	}
	door.Init(DoorImage);
	door.setScale(0.85, 0.85);
	door.setPosition(110, 5);

	/////////////////// coins //////////////////////
	if (!coinSpriteSheet.loadFromFile("res/coin_gold.png"))
	{
		cerr << "can't load coin texture" << endl;
	}
	if (!sound.loadFromFile("res/Sounds/coins.wav"))
	{
		cerr << "can't load coin sound" << endl;
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
		coin.setSound(sound);
		coin.getSound().setVolume(30);
	}

	/////////////// dark effect /////////////////////////
	Uint8 light = 150; // the lower this value the more darker
	door.setColor(Color(light, light, light));
	mainChar.setColor(Color(light, light, light));
	background.setColor(Color(light, light, light));
	///for (auto& coin : coins) coin.setColor(Color(light, light, light));
}

void Floor1::Cleanup()
{
}

void Floor1::Pause()
{
	mainChar.running = false;
	pause = true;
}

void Floor1::Resume()
{
	pause = false;
}

void Floor1::togglePause()
{
	if (this->pause) this->Resume();
	else this->Pause();
}

void Floor1::HandleEvents(Engine * game, Event * event)
{
	// Key release handle
	if (event->type == Event::EventType::KeyReleased)
	{
		for (auto& i : KeyArr)
		{
			if (event->key.code == i)
			{
				mainChar.moveOff();
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
			if (mainChar.getGlobalBounds().intersects(door.getGlobalBounds()))
			{
				cout << "door Opened" << endl;
				door.open();
			}
			break;
		default:
			break;
		}
	}
}

void Floor1::Update(Engine * game, double dt)
{
	// setting it to false after any scene change occurs
	enteringdoor = false;

	if (!pause)
	{
		// Key press handle, character movement
		for (auto& i : KeyArr)
		{
			if (Keyboard::isKeyPressed(i))
			{
				mainChar.moveOn(KeyMap.at(i));
			}
		}

		bool intersection = mainChar.getGlobalBounds().intersects(door.getGlobalBounds());

		// so that the character sprite cannot go out of bounds
		// when the player tries to go out of bounds setPosition s to the boundary point
		if (mainChar.getPosition().x - mainChar.getSize().x / 2 < wallOffSetX - 10)
			mainChar.setPosition(wallOffSetX - 10 + mainChar.getSize().x / 2, mainChar.getPosition().y);
		if (mainChar.getPosition().x > background.getGlobalBounds().width - revOffSetX)
			mainChar.setPosition(background.getGlobalBounds().width - revOffSetX, mainChar.getPosition().y);
		if (mainChar.getPosition().y > background.getGlobalBounds().height - revOffSetY)
			mainChar.setPosition(mainChar.getPosition().x, background.getGlobalBounds().height - revOffSetY);

		////////////////// door Logic /////////////////////
		// special case logic for Door
		// character can only enter Door region if Door is open
		// character cannot enter wall region
		if (door.DoorState == Door::state::CLOSED)
		{
			if (mainChar.getPosition().y + mainChar.getSize().y / 2 < wallOffSetY + 40)
				mainChar.setPosition(mainChar.getPosition().x, wallOffSetY + 40 - mainChar.getSize().y / 2);
			// 40 so that the character can partially enter the wall for a pseudo 3d effect
		}
		else
		{
			if (!intersection)
			{
				if (mainChar.getPosition().y + mainChar.getSize().y / 2 < wallOffSetY + 40)
					mainChar.setPosition(mainChar.getPosition().x, wallOffSetY + 40 - mainChar.getSize().y / 2);
				// 40 so that the character can partially enter the wall for a pseudo 3d effect
			}
		}

		if (intersection)
		{
			if (mainChar.getPosition().y < 50)
			{
				///////// scene change /////////////
				pushScene(game, Boss1::getInstance());
				enteringdoor = true;
				//sets position outside Door to prevent instant re-entry
				mainChar.setPosition(mainChar.getPosition().x, wallOffSetY);
				//changes the direction downward for when the player returns to scene
				mainChar.setDirec(Direction::DOWN);
			}
		}

		mainChar.update(dt);

		///////////////// View Logic /////////////////////
		// so that camera/view doesn't go out of bounds
		if (mainChar.getPosition().x >= game->width / 2
			and mainChar.getPosition().x + game->width / 2 <= background.getGlobalBounds().width)
		{
			view.setCenter(mainChar.getPosition().x, view.getCenter().y);
		}
		if (mainChar.getPosition().y >= game->height / 2
			and mainChar.getPosition().y + game->height / 2 <= background.getGlobalBounds().height)
		{
			view.setCenter(view.getCenter().x, mainChar.getPosition().y);
		}
		game->app->setView(view);

		////////////// Coin Logic //////////////////////
		for (auto& coin : coins)
		{
			if (coin.collected(mainChar))
			{
				coinCollected++;
				// sets the coins way outside the screen
			}
		}
	}
}

void Floor1::Draw(RenderWindow * app)
{
	app->draw(background);

	door.drawTo(app);
	if (!enteringdoor) mainChar.drawTo(app);
	for (auto& coin : coins) coin.drawTo(app);
}
