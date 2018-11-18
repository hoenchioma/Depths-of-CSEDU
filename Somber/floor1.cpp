#include "Floor1.h"

#include "EngineX/Utility.h"
#include "Boss1.h"
#include "Boss2.h"

#include "DefaultInv.h"
#include "Floor2.h"
#include "Boss3.h"
#include "PauseMenu.h"

#include <iostream>


using namespace sf;
using namespace std;

#define WALL_OFFSET_X 30 // thickness of wall on the left side (X)
#define WALL_OFFSET_Y 66 // thickness of wall on the left side (Y)
#define REV_OFFSET_X 11 // thickness of wall on the right side (X)
#define REV_OFFSET_Y 10 // thickness of wall on the right side (Y)
#define WALL_OPENING_Y 700 // co-oridinate (Y) where there is an opening in the wall

void Floor1::LoadRes()
{
	if (!spriteSheet.loadFromFile("res/running_1.png"))
	{
		cerr << "can't load main character sprite texture" << endl;
	}
	if (!backgroundImage.loadFromFile("res/floor1_back_2.png"))
	{
		cerr << "can't load background texture" << endl;
	}
	if (!coinSpriteSheet.loadFromFile("res/coin_gold.png"))
	{
		cerr << "can't load coin texture" << endl;
	}
	if (!coinSoundBuff.loadFromFile("res/Sounds/coins.wav"))
	{
		cerr << "can't load coin sound" << endl;
	}
	if (!DoorImage.loadFromFile("res/door.png"))
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
	if (!balconyUnder.loadFromFile("res/Balcony_new_under_black.png"))
	{
		cerr << "can't load balcony under texture" << endl;
	}


	loadFromFile(textBoxFont, "res/Font/PressStart2P.ttf");
	invShow.loadRes();
}

void Floor1::Init(Engine* game)
{
	///////////////// views //////////////////////////
	/*view.setCenter(game->width / 2, game->height / 2);
	view.setSize(game->width, game->height);*/

	this->game = game;

	////////////////// textbox and inventory //////////////////////
	game->miniMapOn = true;
	game->miniMap.reset(sf::FloatRect(0, 0, game->width, game->height));
	// inventory
	game->inventoryOn = true;
	game->inventory.reset(sf::FloatRect(
		InvShow::getDefaultLoc().x,
		InvShow::getDefaultLoc().y,
		game->fullWidth * 0.2,
		game->fullHeight * 0.8
	));
	invShow.Init(game);

	textBox.Init(game, textBoxFont);
	
	////////////// main character ////////////////////
	mainChar.Init(spriteSheet, 0.1f, 300.f);
	mainChar.setScale(1.4f, 1.4f);
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

	door2.Init(DoorImage);
	door2.setScale(0.85, 0.85);
	door2.setPosition(500, 5);

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
			game->width / 2.f + WALL_OFFSET_X + 20.f, 
			game->height / 2.f + WALL_OFFSET_Y + 85.f
		)
	);
	balcony.setScale(1.25f);

	/////////////////// coins //////////////////////
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
				WALL_OFFSET_X + rand() % (int)(background.getGlobalBounds().width - WALL_OFFSET_X - REV_OFFSET_X - coin.getSize().x),
				WALL_OFFSET_Y + rand() % (int)(background.getGlobalBounds().height - WALL_OFFSET_Y - REV_OFFSET_Y - coin.getSize().y)
			);
		} while (Polygon(coin.getGlobalBounds()).intersects(balcony.getPoly()));
		// randomly generate coins until it spawns outside the balcony region

		coin.setSound(coinSoundBuff);
		coin.getSound().setVolume(30);
		if (game->mute) coin.getSound().setVolume(0);
	}

	/////////////// dark effect /////////////////////////
	Uint8 light = 150; // the lower this value the more darker
	door.setColor(Color(light, light, light));
	door2.setColor(Color(light, light, light));
	mainChar.setColor(Color(light, light, light));
	background.setColor(Color(light, light, light));
	balcony.setBrightness(light);
	///for (auto& coin : coins) coin.setColor(Color(light, light, light));

	/////////////////////// loading from saved game /////////////////////
	if (INVI("save") == 1) mainChar.setPosition(INVD("locationX"), INVD("locationY"));
	game->gameView.setCenter(mainChar.getPosition());

	if (INVI("boss1Complete") == 1) door.open();
	if (INVI("boss2Complete") == 1) door2.open();

	cout << "floor1 scene initialized" << endl;
}

void Floor1::Cleanup()
{
	resetView(game->gameView);
	this->game->miniMapOn = false;
	this->game->inventoryOn = false;
	_fullScreen = false;
	textBox.turnOn();
	textBox.setText("");
	Resume();
}

void Floor1::Pause()
{
	mainChar.running = false;
	pause = true;

	textBox.time.pause();
}

void Floor1::Resume()
{
	pause = false;

	textBox.time.resume();
}

void Floor1::togglePause()
{
	if (this->pause) this->Resume();
	else this->Pause();
}

void Floor1::HandleEvents(Engine * game, Event * event)
{
	if (event->type == Event::EventType::KeyPressed)
	{
		switch (event->key.code)
		{
		case Keyboard::E:

			if (mainChar.getGlobalBounds().intersects(door.getGlobalBounds()))
			{
				door.open();
			}
			if (mainChar.getGlobalBounds().intersects(door2.getGlobalBounds()))
			{
				if (INVI("keys") == 0) textBox.setText("The door is locked.");
				else
				{
					door2.open();
					INVI("keys")--;
				}
			}
			
		break;

		case Keyboard::Space:

			// save everything before going to pause menu screen
			INVD("locationX") = mainChar.getPosition().x;
			INVD("locationY") = mainChar.getPosition().y;
			if (door.DoorState == Door::state::OPEN) INVI("boss1Complete") = 1;
			if (door2.DoorState == Door::state::OPEN) INVI("boss2Complete") = 1;
			pushScene(game, PauseMenu::getInstance());

		break;

		default:
			break;
		}
	}

	textBox.handleEvent(event);
}

void Floor1::Update(Engine * game, double dt)
{
	// setting it to false after any scene change occurs
	enteringdoor = false;

	if (!pause)
	{
		// Key press & release handle, character movement
		mainChar.keyHandle();

		//cout << mainChar.getPosition().x << " " << mainChar.getPosition().y << endl;

		// goto Boss3
		if (mainChar.intersects(FloatRect(0, 700, 10, 200)))
		{
			if (INVI("keys") or INVI("snek"))
			{
				if (!INVI("snek")) INVI("keys")--;
				INVI("snek") = 1;
				pushScene(game, Boss3::getInstance());
				mainChar.setDirec(RIGHT);
				mainChar.setPosition(70, 750);
				enteringdoor = true;
				//game->gameView.setCenter(mainChar.getPosition());
			}
			else
			{
				textBox.setText("You need a key!!\n");
			}
		}
		else textBox.setText("");

		// so that the character sprite cannot go out of bounds
		// when the player tries to go out of bounds setPosition s to the boundary point
		if (mainChar.getPosition().x - mainChar.getSize().x / 2 < WALL_OFFSET_X - 10)
		{
			if (mainChar.getPosition().y > WALL_OPENING_Y)
			{
				if (INVI("keys") == 0)
				{
					textBox.setText("You need a key");
					mainChar.setPosition(WALL_OFFSET_X - 10 + mainChar.getSize().x / 2, mainChar.getPosition().y);
				}
				else {} // entering boss3 is handled above
			}
			else mainChar.setPosition(WALL_OFFSET_X - 10 + mainChar.getSize().x / 2, mainChar.getPosition().y);
		}
		if (mainChar.getPosition().x > background.getGlobalBounds().width - REV_OFFSET_X)
			mainChar.setPosition(background.getGlobalBounds().width - REV_OFFSET_X, mainChar.getPosition().y);
		if (mainChar.getPosition().y > background.getGlobalBounds().height - REV_OFFSET_Y)
			mainChar.setPosition(mainChar.getPosition().x, background.getGlobalBounds().height - REV_OFFSET_Y);

		////////////////// door Logic /////////////////////
		// special case logic for Door
		// character can only enter Door region if Door is open
		// character cannot enter wall region

		bool intersection = mainChar.getGlobalBounds().intersects(door.getGlobalBounds());
		bool intersection2 = mainChar.getGlobalBounds().intersects(door2.getGlobalBounds());

		if (intersection)
		{
			//textBox.setText("The door is locked.");
			if (door.DoorState == Door::state::CLOSED)
			{
				if (mainChar.getPosition().y + mainChar.getSize().y / 2 < WALL_OFFSET_Y + 40)
					mainChar.setPosition(mainChar.getPosition().x, WALL_OFFSET_Y + 40 - mainChar.getSize().y / 2);
				// 40 so that the character can partially enter the wall for a pseudo 3d effect

				textBox.setText("Press 'E' to open the door.");
			}
			if (mainChar.getPosition().y < 50)
			{
				///////// scene change /////////////
				pushScene(game, Boss1::getInstance());
				enteringdoor = true;
				//sets position outside Door to prevent instant re-entry
				mainChar.setPosition(mainChar.getPosition().x, WALL_OFFSET_Y);
				//changes the direction downward for when the player returns to scene
				mainChar.setDirec(Direction::DOWN);
			}
		}
		else if (intersection2)
		{
			if (door2.DoorState == Door::state::CLOSED)
			{
				if (mainChar.getPosition().y + mainChar.getSize().y / 2 < WALL_OFFSET_Y + 40)
					mainChar.setPosition(mainChar.getPosition().x, WALL_OFFSET_Y + 40 - mainChar.getSize().y / 2);
				// 40 so that the character can partially enter the wall for a pseudo 3d effect

				// show door is locked if they don't have key
				if (!INVI("boss2Complete")) textBox.setText("The door is locked.");
				else textBox.setText("Press 'E' to open the door.");

				if (INVI("keys") == 1) textBox.addText("\n\nPress 'E' to unlock the door");
			}
			if (mainChar.getPosition().y < 50)
			{
				/////////// scene change /////////////
				pushScene(game, Boss2::getInstance());
				enteringdoor = true;
				//sets position outside Door to prevent instant re-entry
				mainChar.setPosition(mainChar.getPosition().x, WALL_OFFSET_Y);
				//changes the direction downward for when the player returns to scene
				mainChar.setDirec(Direction::DOWN);
			}
		}
		else
		{
			//textBox.setText("");
			if (mainChar.getPosition().y + mainChar.getSize().y / 2 < WALL_OFFSET_Y + 40)
				mainChar.setPosition(mainChar.getPosition().x, WALL_OFFSET_Y + 40 - mainChar.getSize().y / 2);
			// 40 so that the character can partially enter the wall for a pseudo 3d effect
		}
		
		// Update the main character (movement & animation)
		mainChar.update(dt);

		///////////////// View Logic /////////////////////
		// so that camera/view doesn't go out of bounds

		/*centreView(game->gameView, mainChar.getPosition(), background.getGlobalBounds());*/

		smartCentre(
			game->gameView, 
			mainChar.getPosition(), 
			Vector2f(game->width, game->height), 
			Vector2f(
				background.getGlobalBounds().width,
				background.getGlobalBounds().height
			)
		);

		////////////// Coin Logic //////////////////////
		for (auto& coin : coins)
		{
			if (coin.collected(mainChar))
			{
				coinCollected++;
				if (coinCollected % 5 == 0)
				{
					// unlocks random perk
					INVI(perkName[rand() % perkName.size()])++;
				}
				// sets the coins way outside the screen
			}
		}

		/////////////// has successfully completed the game////////////////
		if (INVI("boss3Complete") == 1 && !endGame)
		{
			//cout << "EndGame" << endl;
			textBox.turnOn();
			textBox.addTextTyped(
				"You have successfully completed this journey. \n\n \
				You are free to go.\n\n \
				Or you may stay and enjoy my contraptions a little more ;)"
			);
			endGame = true;
		}

		textBox.update();
		invShow.update();
	}
}

void Floor1::Draw(RenderWindow * app)
{
	app->draw(background);

	door.drawTo(app);
	door2.drawTo(app);

	// draw bottom below and top above character for a pseudo 3d effect
	balcony.drawBottom(app);
	if (!enteringdoor) mainChar.drawTo(app);
	for (auto& coin : coins) coin.drawTo(app);
	balcony.drawTop(app);

	textBox.draw();
	invShow.draw(app);
}
