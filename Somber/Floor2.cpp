#include "Floor2.h"

#include "EngineX/Utility.h"
#include "Boss1.h"
//#include "Boss2.h"

#include <iostream>

using namespace sf;
using namespace std;

const float wallOffSetX = 30;
const float wallOffSetY = 66;
const float revOffSetX = 11;
const float revOffSetY = 10;

void Floor2::LoadRes()
{
	if (!spriteSheet.loadFromFile("res/running_1.png"))
	{
		cerr << "can't load main character sprite texture" << endl;
	}
	if (!backgroundImage.loadFromFile("res/floor2.png"))
	{
		cerr << "can't load background texture" << endl;
	}
	if (!coinSpriteSheet.loadFromFile("res/coin_gold.png"))
	{
		cerr << "can't load coin texture" << endl;
	}
	if (!sound.loadFromFile("res/Sounds/coins.wav"))
	{
		cerr << "can't load coin sound" << endl;
	}
	if (!DoorImage.loadFromFile("res/Door.png"))
	{
		cerr << "can't load door texture" << endl;
	}
	if (!balconyTop.loadFromFile("res/Balcony_new_top.png"))
	{
		cerr << "can't load balcony top texture" << endl;
	}
	if (!balconyBottom.loadFromFile("res/Balcony_new_bottom.png"))
	{
		cerr << "can't load balcony bottom texture" << endl;
	}
	loadFromFile(balconyUnder, "res/Balcony_new_under_black.png");
	floor2CovTex.loadFromFile("res/floor2cover.png");
}

void Floor2::Init(Engine* game)
{
	///////////////// views //////////////////////////
	/*view.setCenter(game->width / 2, game->height / 2);
	view.setSize(game->width, game->height);*/

	////////////// main character ////////////////////
	mainChar.Init(spriteSheet, 0.1f, 300.f);
	mainChar.setScale(1.4f, 1.4f);
	mainChar.dontIntersect(sf::FloatRect(393,0,1000, 320));
	//mainChar.setPosition(game->width / 2.f, game->height / 2.f);
	mainChar.setPosition(0, 0);
	mainChar.dontIntersect(&balcony.getPoly());
	///mainChar.setPosition(0, 0);

	////////////////// background ///////////////////////
	background.setTexture(backgroundImage);
	background.setScale(1.35, 1.35);
	background.setOrigin(0, 0);
	background.setPosition(0, 0);

	door.Init(DoorImage);
	door.setScale(0.85, 0.85);
	door.setPosition(110, 5);
	floor2Cover.setTexture(floor2CovTex);
	floor2Cover.setScale(1.35, 1.35);
	floor2Cover.setPosition(374, 0);

	/////////////// balcony //////////////////////////
	balcony.Init(
		{
			{18, 437},
			{207, 585},
			{477, 585},
			{674, 437},
			{674, 208},
			{477, 70},
			{207, 70},
			{18, 208}
		},
		balconyTop,
		balconyBottom,
		balconyUnder,
		Vector2f(
			game->width / 2.f + wallOffSetX + 20.f,
			game->height / 2.f + wallOffSetY + 250.f
		)
	);
	balcony.setScale(1.f);

	/*/////////////////// coins //////////////////////
	for (auto& coin : coins)
	{
		coin.setSpriteSheet(coinSpriteSheet);
		coin.addSheet(AniSprite::dir::horizontal, coinSpriteSheet.getSize().x / 8, coinSpriteSheet.getSize().y);
		coin.setDelay(0.1);
		coin.setScale(1.25, 1.25);
		//coin.setOrigin(coin.getSize().x / 2, coin.getSize().y / 2);

		do
		{
			coin.setPosition(
				wallOffSetX + rand() % (int)(background.getGlobalBounds().width - wallOffSetX - revOffSetX - coin.getSize().x),
				wallOffSetY + rand() % (int)(background.getGlobalBounds().height - wallOffSetY - revOffSetY - coin.getSize().y)
			);
		} while (Polygon(coin.getGlobalBounds()).intersects(balcony.getPoly()));
		// randomly generate coins until it spawns outside the balcony region

		coin.setSound(sound);
		coin.getSound().setVolume(30);
	}
	*/
	/////////////// dark effect /////////////////////////
	Uint8 light = 150; // the lower this value the more darker
	door.setColor(Color(light, light, light));
	mainChar.setColor(Color(light, light, light));
	background.setColor(Color(light, light, light));
	balcony.setBrightness(light);
	floor2Cover.setColor(Color(light, light, light));
	///for (auto& coin : coins) coin.setColor(Color(light, light, light));

	cout << "Floor2 scene initialized" << endl;
}

void Floor2::Cleanup()
{
}

void Floor2::Pause()
{
	mainChar.running = false;
	pause = true;
}

void Floor2::Resume()
{
	pause = false;
}

void Floor2::togglePause()
{
	if (this->pause) this->Resume();
	else this->Pause();
}

void Floor2::HandleEvents(Engine * game, Event * event)
{
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

void Floor2::Update(Engine * game, double dt)
{
	if (Mouse::isButtonPressed(Mouse::Left)) printf("%lf %lf\n", mainChar.getPosition().x, mainChar.getPosition().y);
	// setting it to false after any scene change occurs
	enteringdoor = false;

	if (!pause)
	{
		// Key press & release handle, character movement
		mainChar.keyHandle();

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

		bool intersection = mainChar.getGlobalBounds().intersects(door.getGlobalBounds());

		if (intersection)
		{
			if (door.DoorState == Door::state::CLOSED)
			{
				if (mainChar.getPosition().y + mainChar.getSize().y / 2 < wallOffSetY + 40)
					mainChar.setPosition(mainChar.getPosition().x, wallOffSetY + 40 - mainChar.getSize().y / 2);
				// 40 so that the character can partially enter the wall for a pseudo 3d effect
			}
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

		else
		{
			if (mainChar.getPosition().y + mainChar.getSize().y / 2 < wallOffSetY + 40)
				mainChar.setPosition(mainChar.getPosition().x, wallOffSetY + 40 - mainChar.getSize().y / 2);
			// 40 so that the character can partially enter the wall for a pseudo 3d effect
		}

		// Update the main character (movement & animation)
		mainChar.update(dt);

		///////////////// View Logic /////////////////////
		// so that camera/view doesn't go out of bounds
		centreView(game->gameView, mainChar.getPosition(), background.getGlobalBounds());

		////////////// Coin Logic //////////////////////
		/*for (auto& coin : coins)
		{
			if (coin.collected(mainChar))
			{
				coinCollected++;
				// sets the coins way outside the screen
			}
		}*/
	}
}

void Floor2::Draw(RenderWindow * app)
{
	app->draw(background);

	door.drawTo(app);

	balcony.drawBottom(app);
	if (!enteringdoor) mainChar.drawTo(app);
	//for (auto& coin : coins) coin.drawTo(app);
	balcony.drawTop(app);
	app->draw(floor2Cover);
}
