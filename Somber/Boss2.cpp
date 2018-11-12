#include "Boss2.h"

#include "EngineX/Utility.h"

#include <iostream>

using namespace sf;
using namespace std;

void Boss2::LoadRes()									//game resource files are loaded here
{
	loadFromFile(zombieAttackTexL[0], "res/Zombies 1/zombie1AttackLeft.png");
	loadFromFile(zombieAttackTexL[1], "res/Zombies 2/zombie2AttackLeft.png");
	loadFromFile(zombieAttackTexL[2], "res/Zombies 3/zombie3AttackLeft.png");
	loadFromFile(zombieAttackTexR[0], "res/Zombies 1/zombie1AttackRight.png");
	loadFromFile(zombieAttackTexR[1], "res/Zombies 2/zombie2AttackRight.png");
	loadFromFile(zombieAttackTexR[2], "res/Zombies 3/zombie3AttackRight.png");

	loadFromFile(bulletTexture, "res/bullet.png");
	loadFromFile(crosshair, "res/crosshair.png");
	loadFromFile(playerSpriteSheet, "res/running_1.png");
	loadFromFile(heartFull, "res/heart_full.png");
	loadFromFile(heartHalf, "res/heart_half.png");
	loadFromFile(heartEmpty, "res/heart_empty.png");
	loadFromFile(doorTex, "res/door.png");
	loadFromFile(PCTex, "res/PC.png");
	loadFromFile(PCInTex, "res/PCInv.png");
	loadFromFile(highestScoreTex, "res/HighScoreTag.png");
	scoreCardTex.loadFromFile("res/scoreCard.png");
	loadFromFile(floorTex, "res/floorBoss2.png");

	loadFromFile(zombieRunTexL[0], "res/Zombies 1/zombie1RunLeft.png");
	loadFromFile(zombieRunTexL[1], "res/Zombies 2/zombie2RunLeft.png");
	loadFromFile(zombieRunTexL[2], "res/Zombies 3/zombie3RunLeft.png");
	loadFromFile(zombieRunTexR[0], "res/Zombies 1/zombie1RunRight.png");
	loadFromFile(zombieRunTexR[1], "res/Zombies 2/zombie2RunRight.png");
	loadFromFile(zombieRunTexR[2], "res/Zombies 3/zombie3RunRight.png");

	loadFromFile(perkBuffer,"res/Sounds/powerUp.wav");
	loadFromFile(playerHurtBuffer,"res/Sounds/playerHurt.wav");
	loadFromFile(bulletSoundBuf, "res/Sounds/40_smith_wesson_8x_gunshot-mike-koenig_2.wav");
	loadFromFile(tempBuf, "res/Sounds/Zombie Gets Attacked-SoundBible.com-20348330.wav");
	zombieSoundBuf.insert({ "zombie_attacked", tempBuf });

	loadFromFile(displayFont, "res/Font/unispace bd.ttf");
	loadFromFile(textBoxFont, "res/Font/PressStart2P.ttf");

	invShow.loadRes();
}

void Boss2::Init(Engine* game)
{																//initialize game variables here
	this->game = game;


	for (i = 0; i < 40; i++)									//setting position,texture and scale for each computer table or PC
	{
		pc[i].object.setTexture(PCTex);
		pc[i].object.setScale(.25, .25);
	}
	for (i = 0; i < 10; i++)
	{
		pc[i].object.setPosition(i * 103 + 50, 35);
	}
	for (i = 10, j = 0; i < 20; i++, j++)
	{
		pc[i].object.setPosition(j * 103 + 75, 90);
	}
	for (i = 20, j = 0; i < 30; i++, j++)
	{
		pc[i].object.setPosition(j * 105 + 50, 600);
	}
	for (i = 30, j = 0; i < 40; i++, j++)
	{
		pc[i].object.setPosition(j * 105 + 75, 650);
		pc[i].object.setScale(.3, .3);
	}
	pcIn.setTexture(PCInTex);
	pcIn.setScale(.35, .35);
	pcIn.setPosition(j * 105 + 75, 630);

	////////////////// textbox and inv //////////////////////
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
	///////////////////////////////////////////////////////////

	game->app->setMouseCursorVisible(false);						//set mouse cursor invisible
	
	ifstream Boss2ScoreFileIn;										//load highest score form save file Boss2ScoreFile.txt
	Boss2ScoreFileIn.open("save/Boss2ScoreFile.txt");
	Boss2ScoreFileIn >> topScore;
	Boss2ScoreFileIn.close();
	ostringstream TopScoreString;
	TopScoreString << "TOP SCORE : " << topScore;					//setting topScore display string
	topScoreText.setString(TopScoreString.str());

	target.setTexture(crosshair);									//setting textures,scales and position for exit door, mouse cursor
	target.setScale(0.2, 0.2);
	floor.setTexture(floorTex);
	door.setTexture(doorTex);
	door.setTextureRect(IntRect(0, 0, doorTex.getSize().x / 2, doorTex.getSize().y));
	door.setScale(0.85, 0.75);
	door.setPosition(windowWidth - 100, -10);

	highestScoreTag.setTexture(highestScoreTex);				//setting textures, scales and positions of scorecard screen
	scoreCard.setTexture(scoreCardTex);
	scoreCard.setPosition(3000, 3000);
	highestScoreTag.setPosition(3000, 3000);

	player.Init(playerSpriteSheet, 0.1f, 300.f);
	player.setScale(1.4, 1.4);
	player.setPosition(windowWidth / 2.0, windowHeight / 2.0 + 50);

	Score = 0;													//setting variable initial values
	scoreNeg = 0;
	heartDim = 16;


	speedPerk = 0;												//setting initial flag values
	invinciblePerk = 0;
	timeFreezePerk = 0;
	perkSoundAc = 0;
	fileClose = 0;

	ScoreText.setFont(displayFont);								//setting font, size and position of on screen display information
	topScoreText.setFont(displayFont);
	ScoreText.setCharacterSize(20);
	topScoreText.setCharacterSize(30);
	ScoreText.setPosition(windowWidth - 150, 0);
	topScoreText.setPosition(3000, 3000);
																		//setting sound volume and buffer
	perkSound.setBuffer(perkBuffer);
	perkSound.setVolume(15);
	bulletSound.setBuffer(bulletSoundBuf);
	bulletSound.setVolume(20);
	playerHurt.setBuffer(playerHurtBuffer);
	playerHurt.setVolume(15);

	zombieAttacked.push_back(Sound(zombieSoundBuf["zombie_attacked"]));
	zombieAttacked.back().setVolume(50);
	zombieAttacked.push_back(Sound());


	player.setBoundary(70, 50, windowWidth - 70, windowHeight - 70);			//setting player boundary and object collsion positions
	player.dontIntersect(sf::FloatRect(0, 0, windowWidth - 200, 150));
	player.dontIntersect(sf::FloatRect(0, windowHeight - 100, windowWidth, 130));


	textBox.addTextTyped(														//textbox
		"Survive the zombie horde as long as you can.\
		\n\nFortunately, you can shoot the zombies.\
		\n\nGood luck!"
	);

	if (game->mute)																//volume settings if game is muted
	{
		for (auto& i : zombieSound) i.setVolume(0);
		for (auto& i : zombieAttacked) i.setVolume(0);
		bulletSound.setVolume(0);
		playerHurt.setVolume(0);
		perkSound.setVolume(0);
	}

	exitTimer.restart();														//restarts clock for level duration
}

void Boss2::Cleanup()
{
	player.health = 150;
	zombies.clear();
	resetView(game->gameView);
	_fullScreen = false;
	textBox.turnOn();
	textBox.setText("");
	Resume();
}

void Boss2::Pause()
{
	pause = true;
	zombieEatStep.pause();
	exitTimer.pause();

	for (auto& i : zombies) i.pause();

	textBox.time.pause();
																				// this function is going to be called when the game is paused
}

void Boss2::Resume()
{
	pause = false;
	zombieEatStep.resume();
	exitTimer.resume();

	for (auto& i : zombies) i.resume();

	textBox.time.resume();
																				// this function is going to be called when the game is resumed
}

void Boss2::togglePause()
{
	if (this->pause) Resume();
	else Pause();
}

void Boss2::HandleEvents(Engine * game, Event * event)
{
																				// handle events here (keyboard/ mouse)

	if (event->type == Event::EventType::KeyPressed)
	{
		switch (event->key.code)
		{
		case Keyboard::Escape:
			togglePause();
			break;
		default:
			break;
		}
	}

	textBox.handleEvent(event);
}

void Boss2::Update(Engine * game, double dt)
{
	if (!pause)
	{
		if (Keyboard::isKeyPressed(Keyboard::C))															// ends the level immediately if "C" is pressed
		{
			zombies.clear();
			gameTime = 0;
			player.setPosition(windowWidth - 70, 70);
		}

		if (Keyboard::isKeyPressed(Keyboard::Num1) && !fileClose && INVI("speed") > 0 && !speedPerk)		//speedPerk is activated and player movement speed is increased
		{
			player.setVel(800);
			speedPerk = 1;
			INVI("speed")--;
			speedPerkTime.restart();
			invShow.activate("speed");
			perkSoundAc = 1;																				//activates perkSound flag

		}
		if (speedPerkTime.getElapsedTime().asSeconds() > perkTime && speedPerk)								//speedPerk is deactivated and player movement is reset
		{
			player.setVel(300);
			invShow.deActivate("speed");
			perkSoundAc = 0;																					//deactivates perkSound flag
		}
		invShow.setProgress("speed", 1.0 - speedPerkTime.getElapsedTime().asSeconds() / 10.0);
		if (Keyboard::isKeyPressed(Keyboard::Num2) && !fileClose && INVI("invincible") > 0 && !invinciblePerk)	//invincibleperk is activated
		{
			invinciblePerk = 1;
			invShow.activate("invincible");
			invinciblePerkTime.restart();
			INVI("invincible")--;
			perkSoundAc = 1;																					//activates spundPerk flag

		}
		if (invinciblePerkTime.getElapsedTime().asSeconds() > perkTime && invinciblePerk)						//invincible perk deactivated
		{
			invinciblePerk = 0;
			invShow.deActivate("invincible");
			perkSoundAc = 0;																					//activates spundPerk flag
		}

		if (Keyboard::isKeyPressed(Keyboard::Num6) && !fileClose && INVI("timeFreeze") > 0 && !timeFreezePerk)	//timefreeze perk activated
		{
			timeFreezePerk = 1;
			timeFreezeTime.restart();
			INVI("timeFreeze")--;
			invShow.activate("timeFreeze");
			exitTimer.pause();
			perkSoundAc = 1;																					//activates spundPerk flag
		}

		if (timeFreezeTime.getElapsedTime().asSeconds() > perkTime && timeFreezePerk)							//timefreeze perk deactivated
		{
			timeFreezePerk = 0;
			exitTimer.resume();
			invShow.deActivate("timeFreeze");
			perkSoundAc = 0;																					//deactivates spundPerk flag
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) && !fileClose &&INVI("healthBoost") > 0)
		{
			player.health += 60;
			INVI("healthBoost")--;
		}


		if (Score < 0) Score = 0;
		ostringstream numberToString;
		numberToString << "Score : " << Score;																	//updates player Score
		ScoreText.setString(numberToString.str());

		target.setPosition(mouse.getPosition(*game->app).x - crosshair.getSize().x / 20, mouse.getPosition(*game->app).y - crosshair.getSize().y / 20); //sets crosshair poisiton based on mouse movement

		diffInt = player.health / 30;																			//sets player health bar based on current health
		diffFloat = player.health / 30.0;
		if (diffInt < diffFloat) diffInt++;
		for (i = 0; i < diffInt; i++)
		{
			healthDiff = player.health - i * 30;
			if (healthDiff > 0)
			{
				if (healthDiff > 20)	heartSprite[i].setTexture(heartFull);
				else if (healthDiff <= 20 && healthDiff > 10) heartSprite[i].setTexture(heartHalf);
				else if (healthDiff <= 10 && healthDiff > 0) heartSprite[i].setTexture(heartEmpty);
				heartSprite[i].setPosition(i * 20 + 10, 0);
			}
			else heartSprite[i].setPosition(-300, -3000);
		}
		if (player.health <= 0 && INVI("reLife") <= 0)															//activates game over screen if player loses level
		{
			// restarts game////////////////////////////////////HERE RAHEEB
			reset(game);
		}
		else if (INVI("reLife") > 0 && player.health <= 0)														//activates relife perk if available and sets player health to 60 when player dies
		{
			player.health = 60;
			player.setPosition(windowWidth / 2.0, windowHeight / 2.0 + 50);
			player.setDirec(Direction::DOWN);
			INVI("reLife")--;
		}

		if (player.health > 0)
		{

			player.keyHandle();
			player.update(dt);

			if (bulletTime < 35)
				bulletTime += 1 * dt*dtMul;																			//multiply by dtMul*dt for framerate independency
			if (Mouse::isButtonPressed(Mouse::Left) && bulletTime >= 35)
			{
				bulletSound.play();																					// play sound when gun is fired
				player.bullets.push_back(Bullet(&bulletTexture, player.getPosition(), Mouse::getPosition(*game->app)));
				bulletTime = 0;
			}
			for (int i = 0; i < player.bullets.size(); i++)
			{
				player.bullets[i].object.move(15 * player.bullets[i].bulletMulX*dt*dtMul, 15 * player.bullets[i].bulletMulY*dt*dtMul);		//moves the bullet on screen and multiply by dtMul*dt for framerate independency
				if (player.bullets[i].object.getPosition().x > windowWidth || player.bullets[i].object.getPosition().x < 0 || player.bullets[i].object.getPosition().y > windowHeight || player.bullets[i].object.getPosition().y > windowHeight)
				{																									//erases bullet vector if bullet goes out of screen
					player.bullets.erase(player.bullets.begin() + i);
					break;
				}
				for (int j = 0; j < zombies.size(); j++)
				{
					if (player.bullets[i].object.getGlobalBounds().intersects(zombies[j].getGlobalBounds()))		//if bullet hits zombies 
					{
						Score += 10;																				//increases score
						zombieAttacked[rand() % zombieAttacked.size()].play();										//plays zombie hurt sound
						if (zombies[j].health <= 1)
						{
							zombies.erase(zombies.begin() + j);														//zombie vector is erased if its health becomes zero
						}
						else
						{
							zombies[j].health--;																	//decreasesif zombie health if the health is more than one
						}
						player.bullets.erase(player.bullets.begin() + i);											//erases the bullet vector which hits zombie
						break;
					}
				}
			}
			if (spawnTime < 80) spawnTime += 1 * dt*dtMul;
			if (spawnTime >= 80)
			{
				zombies.push_back(Undead(zombieRunTexL, zombieRunTexR, zombieAttackTexL, zombieAttackTexR));		//spawns new zombie if spawn time becomes greater then 80
				spawnTime = 0;
			}
			for (int i = 0; i < zombies.size(); i++)
			{
				if (!timeFreezePerk)																				//if timefreeze perk is not active, zombie movement is handled
				{
					if (zombies[i].getPosition().x > player.getPosition().x) zombies[i].move(-zombieSpeed * dt*dtMul, 0);	//decreases or increases zombie vector x axis value 
					if (zombies[i].getPosition().x < player.getPosition().x) zombies[i].move(zombieSpeed*dt*dtMul, 0);		//based on player x axis value
					if (zombies[i].getPosition().y > player.getPosition().y) zombies[i].move(0, -zombieSpeed * dt*dtMul);	//decreases or increases zombie vector y axis value
					if (zombies[i].getPosition().y < player.getPosition().y) zombies[i].move(0, zombieSpeed*dt*dtMul);		//based on player y axis value
					if (zombies[i].getPosition().y < 150 && zombies[i].getPosition().x < windowWidth - 225) zombies[i].move(0, zombieSpeed*dt*dtMul);	//zombie movement limitation based on boundary
					if (zombies[i].getPosition().y > windowHeight - 175)zombies[i].move(0, -zombieSpeed * dt*dtMul);

					if (zombies[i].getPosition().x > player.getPosition().x) zombies[i].mode = 0;					//sets animation texture for zombie based on player location
					else  zombies[i].mode = 1;
				}
			}

			if (zombieEatStep.getElapsedTime().asMilliseconds() > 10)
			{
				preUpdateHealth = player.health;
				for (int i = 0; i < zombies.size(); i++)
				{
					if (player.getPoly().intersects(zombies[i].getGlobalBounds()) && !invinciblePerk && !timeFreezePerk)		//if freeze time perk is inactive and player collides zombie
					{																											//player health decreases and score decreases
						player.health -= 1 * dt*dtMul;
						scoreNeg += dt * dtMul;
						if (scoreNeg > 1)
						{
							Score -= scoreNeg;
							scoreNeg = 0;
						}
						zombieEatStep.restart();
						if (playerHurt.getStatus() != Sound::Status::Playing) playerHurt.play();								//starts player hurt sound

						zombies[i].eating = true;
					}
					else zombies[i].eating = false;
				}
				if (preUpdateHealth == player.health) playerHurt.stop();														//stops player hurt sound if health remains same after update loop
			}
		}

		// Exit level
		if (exitTimer.getElapsedTime().asSeconds() > gameTime)																	//door opens if level time exceeds game time
		{
			door.setTextureRect(IntRect(doorTex.getSize().x / 2, 0, doorTex.getSize().x / 2, doorTex.getSize().y));
			if (player.intersects(door.getGlobalBounds()))																		//player intersects with door
			{																													//shows end level screen with score
				_fullScreen = true;
				game->fullScreen.reset(FloatRect(0, 0, game->width, game->height));
				textBox.turnOff();
				zombies.clear();																								//removes all zombies
				ScoreText.setCharacterSize(50);
				ScoreText.setPosition(350, 200);
				scoreCard.setPosition(0, 0);

				if (Score > topScore)
				{
					if (!fileClose)
					{
						ofstream Boss2ScoreFileOut;																				//saves new score on Boss2ScoreFile.txt if new high score is achieved
						Boss2ScoreFileOut.open("save/Boss2ScoreFile.txt");
						Boss2ScoreFileOut << Score;
						Boss2ScoreFileOut.close();
					}
					highestScoreTag.setPosition(350, 300);																		//shows "new high score" box on screen
				}
				else topScoreText.setPosition(400, 300);																		//if score is not high score then shows highest score on screen
				fileClose = 1;

				if (Keyboard::isKeyPressed(Keyboard::Enter))
					popScene(game);

				if (!oonce)
				{
					INVI("keys")++;
					oonce = true;
				}
			}
		}
		for (int i = 0; i < zombies.size(); i++)
		{
			if (zombies[i].eating)
			{
				if (zombies[i].mode == 0) zombies[i].mode = 2;													//sets zombie animation to eating if it player is hurt by zombies
				else zombies[i].mode = 3;
			}
		}

		textBox.update();
		invShow.update();
		if (perkSound.getStatus() != Sound::Status::Playing&& perkSoundAc) perkSound.play();					//plays perk sound when perk is active
	}
}

////////draw each object on screen(order is necessary for 3D effect)//////////
void Boss2::Draw(RenderWindow * app)
{
	app->draw(floor);
	for (i = 0; i < 20; i++) app->draw(pc[i].object);								//draws the computer tableson top  on the screen
	app->draw(door);
	player.drawTo(app);																//draws the player
	for (int i = 0; i < zombies.size(); i++)										//draws the zombies
		zombies[i].drawTo(app);
	for (i = 20; i < 40; i++) app->draw(pc[i].object);								//draws the computer tables on the bottom
	for (int i = 0; i < player.bullets.size(); i++)
		app->draw(player.bullets[i].object);
	app->draw(pcIn);

	for (i = 0; i < diffInt; i++) app->draw(heartSprite[i]);						//draws the player health bar
	app->draw(target);

	app->draw(scoreCard);															//score and texts on screens are drawn
	app->draw(ScoreText);
	app->draw(topScoreText);
	app->draw(highestScoreTag);

	textBox.draw();																	//draws the textbox and inventory
	invShow.draw(app);
};