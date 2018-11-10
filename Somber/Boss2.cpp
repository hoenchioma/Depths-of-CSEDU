#include "Boss2.h"

#include "EngineX/Utility.h"

#include <iostream>

using namespace sf;
using namespace std;

void Boss2::LoadRes()
{
	loadFromFile(bulletTexture, "res/bullet.png");
	//loadFromFile(playerTexture, "res/player.png");
	loadFromFile(undeadTexture1, "res/undead1.png");
	loadFromFile(undeadTexture2, "res/undead2_mod.png");
	loadFromFile(undeadTexture3, "res/undead3_mod.png");
	loadFromFile(crosshair, "res/crosshair.png");
	loadFromFile(playerSpriteSheet, "res/running_1.png");
	loadFromFile(heartFull, "res/heart_full.png");
	loadFromFile(heartHalf, "res/heart_half.png");
	loadFromFile(heartEmpty, "res/heart_empty.png");
	loadFromFile(doorTex, "res/door.png");
	loadFromFile(bulletSoundBuf, "res/Sounds/40_smith_wesson_8x_gunshot-mike-koenig_2.wav");
	sf::SoundBuffer tempBuf;
	loadFromFile(tempBuf, "res/Sounds/Zombie Gets Attacked-SoundBible.com-20348330.wav");
	zombieSoundBuf.insert({ "zombie_attacked", tempBuf });
	font.loadFromFile("res/Font/unispace bd.ttf");
	highestScoreTex.loadFromFile("res/HighScoreTag.png");
	scoreCardTex.loadFromFile("res/scoreCard.png");
	floorTex.loadFromFile("res/floorBoss2.png");
	midPCTex.loadFromFile("res/boss2MiddlePC.png"); 
	centreTableTex.loadFromFile("res/centrePC.png");
	perkBuffer.loadFromFile("res/Sounds/powerUp.wav");
}

void Boss2::Init(Engine* game)
{
	game->app->setMouseCursorVisible(false);
	ifstream Boss2ScoreFileIn;
	Boss2ScoreFileIn.open("save/Boss2ScoreFile.txt");
	Boss2ScoreFileIn >> topScore;
	Boss2ScoreFileIn.close();
	perkSound.setBuffer(perkBuffer);
	perkSound.setVolume(10);

	fileClose = 0;
	midPCTex.setSmooth(true);
	highestScoreTag.setTexture(highestScoreTex);
	scoreCard.setTexture(scoreCardTex);
	scoreCard.setPosition(3000, 3000);
	highestScoreTag.setPosition(3000, 3000);
	floor.setTexture(floorTex);
	midPC.setTexture(midPCTex);
	bottomPC.setTexture(midPCTex);
	centreTable.setTexture(centreTableTex);
	//centreTable.setScale(.3, .25);
	centreTable.setPosition(880, 319);
	
	midPC.setPosition(25,300);
	bottomPC.setPosition(25,windowHeight-42);
	door.setTexture(doorTex);
	door.setTextureRect(IntRect(0, 0, doorTex.getSize().x/ 2, doorTex.getSize().y));
	door.setScale(0.85, 0.75);
	door.setPosition(50,-10);

	player.Init(playerSpriteSheet, 0.1f, 300.f);
	player.setScale(1.4, 1.4);
	player.setPosition(windowWidth / 2.0, windowHeight / 2.0+50);

	player.setBoundary(40, 55, windowWidth - 50, windowHeight - 90);

	target.setTexture(crosshair);
	target.setScale(0.1, 0.1);
	sf::Mouse mouse;
	Score = 0;
	scoreNeg = 0;


	speedPerk = 0;
	invinciblePerk = 0;
	timeFreezePerk = 0;

	// life variables
	heartDim = 16;

	ScoreText.setFont(font);
	topScoreText.setFont(font);
	ScoreText.setCharacterSize(20);
	topScoreText.setCharacterSize(30);
	// exit variables

	//ScoreText.setColor(sf::Color::White);
	ScoreText.setPosition(windowWidth - 150, 0);
	topScoreText.setPosition(3000, 3000);
	//exit.setScale(0.4f, 0.4f);

	ostringstream TopScoreString;
	TopScoreString << "TOP SCORE : " << topScore;//////////////////Score
	topScoreText.setString(TopScoreString.str());

	//exit.setPosition(0, windowHeight - 60);
	//exit.setPosition(1e7, 1e7);
	//exit.setTexture(exitLit);
	exitTimer.restart();

	// sound
	bulletSound.setBuffer(bulletSoundBuf);
	bulletSound.setVolume(20);

	zombieAttacked.push_back(Sound(zombieSoundBuf["zombie_attacked"]));
	zombieAttacked.back().setVolume(50);
	zombieAttacked.push_back(Sound());

	//Init

	player.dontIntersect(sf::FloatRect(0.f,322.f,870,49));
	player.dontIntersect(sf::FloatRect(160,42,843,28));
	player.dontIntersect(sf::FloatRect(880,347,108,22));
}

void Boss2::Cleanup()
{
	player.health = 150;
	zombies.clear();
}

void Boss2::Pause()
{
	//player.running = false;
	pause = true;
	zombieEatStep.pause();
	exitTimer.pause();

	// this function is going to be called when the game is paused
}

void Boss2::Resume()
{
	pause = false;
	zombieEatStep.resume();
	exitTimer.resume();
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
}

void Boss2::Update(Engine * game, double dt)
{
	if (!pause)
	{
		if ((speedPerk || invinciblePerk || timeFreezePerk )&&perkSound.getStatus()!=Sound::Status::Playing) perkSound.play();
		
		if (Keyboard::isKeyPressed(Keyboard::Num1) && !fileClose && INVI("speed") > 0 && !speedPerk)
		{
			player.setVel(800);
			speedPerk = 1;
			INVI("speed")--;
			speedPerkTime.restart();

		}
		if (speedPerkTime.getElapsedTime().asSeconds() > perkTime && speedPerk) player.setVel(300);

		if (Keyboard::isKeyPressed(Keyboard::Num2) && !fileClose && INVI("invincible") > 0 && !invinciblePerk)
		{
			invinciblePerk = 1;
			invinciblePerkTime.restart();
			INVI("invincible")--;
		}
		if (invinciblePerkTime.getElapsedTime().asSeconds() > perkTime && invinciblePerk) invinciblePerk = 0;

		if (Keyboard::isKeyPressed(Keyboard::Num3) && !fileClose && INVI("timeFreeze") > 0 && !timeFreezePerk)
		{
			timeFreezePerk = 1;
			timeFreezeTime.restart();
			INVI("timeFreeze")--;
			exitTimer.pause();
		}

		if (timeFreezeTime.getElapsedTime().asSeconds() > perkTime && timeFreezePerk)
		{
			timeFreezePerk = 0;
			exitTimer.resume();
		}

		if (Score < 0) Score = 0;
		ostringstream numberToString;
		numberToString << "Score : " << Score;//////////////////Score
		ScoreText.setString(numberToString.str());

		target.setPosition(mouse.getPosition(*game->app).x - crosshair.getSize().x / 20, mouse.getPosition(*game->app).y - crosshair.getSize().y / 20);

		diffInt = player.health / 30;
		diffFloat = player.health / 30.0;
		if (diffInt<diffFloat) diffInt++;
		for ( i = 0; i < diffInt; i++)
		{
			 healthDiff= player.health-i * 30;
			if (healthDiff > 0)
			{
				if (healthDiff > 20)	heartSprite[i].setTexture(heartFull);
				else if (healthDiff <= 20 && healthDiff > 10) heartSprite[i].setTexture(heartHalf);
				else if (healthDiff <= 10 && healthDiff>0) heartSprite[i].setTexture(heartEmpty);
				heartSprite[i].setPosition(i * 20+10, 0);
			}
			else heartSprite[i].setPosition(-300, -3000);
		}
		if (player.health <= 0 && INVI("reLife") <= 0)
		{
			// restarts game
			reset(game);
		}
		else if (INVI("reLife") > 0 && player.health <= 0)
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
				bulletTime += 1 * dt*dtMul;
			if (Mouse::isButtonPressed(Mouse::Left) && bulletTime >= 35)
			{
				bulletSound.play(); // play sound when gun is fired
				player.bullets.push_back(Bullet(&bulletTexture, player.getPosition(), Mouse::getPosition(*game->app)));
				bulletTime = 0;
			}
			for (int i = 0; i < player.bullets.size(); i++)
			{
				player.bullets[i].object.move(15 * player.bullets[i].bulletMulX*dt*dtMul, 15 * player.bullets[i].bulletMulY*dt*dtMul);
				if (player.bullets[i].object.getPosition().x > windowWidth || player.bullets[i].object.getPosition().x < 0 || player.bullets[i].object.getPosition().y > windowHeight || player.bullets[i].object.getPosition().y > windowHeight)
				{
					player.bullets.erase(player.bullets.begin() + i);
					break;
				}
				for (int j = 0; j < zombies.size(); j++)
				{
					if (player.bullets[i].object.getGlobalBounds().intersects(zombies[j].object.getGlobalBounds()))
					{
						Score += 10;
						zombieAttacked[rand() % zombieAttacked.size()].play();
						if (zombies[j].health <= 1)
						{
							zombies.erase(zombies.begin() + j);
						}
						else
						{
							zombies[j].health--;
						}
						player.bullets.erase(player.bullets.begin() + i);
						break;
					}
				}
			}
			if (spawnTime < 80) spawnTime += 1 * dt*dtMul;
			if (spawnTime >= 80)
			{
				zombies.push_back(Undead(&undeadTexture1, &undeadTexture2, &undeadTexture3));
				spawnTime = 0;
			}
			for (int i = 0; i < zombies.size(); i++)
			{
				if (!timeFreezePerk)
				{
					if (player.getPosition().y < 390 && zombies[i].object.getPosition().y>295 && zombies[i].object.getPosition().x < 985)
						zombies[i].object.move(zombieSpeed * dt*dtMul * 2, 0);
					else if (player.getPosition().y > 295 && zombies[i].object.getPosition().y < 390 && zombies[i].object.getPosition().x < 985)
						zombies[i].object.move(zombieSpeed * dt*dtMul * 2, 0);
					else
					{
						if (zombies[i].object.getPosition().x > player.getPosition().x) zombies[i].object.move(-zombieSpeed * dt*dtMul, 0);
						if (zombies[i].object.getPosition().x < player.getPosition().x) zombies[i].object.move(zombieSpeed*dt*dtMul, 0);
						if (zombies[i].object.getPosition().y > player.getPosition().y) zombies[i].object.move(0, -zombieSpeed * dt*dtMul);
						if (zombies[i].object.getPosition().y < player.getPosition().y) zombies[i].object.move(0, zombieSpeed*dt*dtMul);
						//if (zombies[i].object.getPosition().x < 0 || zombies[i].object.getPosition().y < 0 || zombies[i].object.getPosition().x >windowWidth || zombies[i].object.getPosition().y > windowHeight)
					}
					if (zombies[i].object.getPosition().x < 984 && zombies[i].object.getPosition().y>291 && zombies[i].object.getPosition().y < 389)
					{
						zombies[i].object.move(zombieSpeed * dt*dtMul, 0);
						if (zombies[i].object.getPosition().y > player.getPosition().y) zombies[i].object.move(0, -zombieSpeed * dt*dtMul);
						else zombies[i].object.move(0, zombieSpeed*dt*dtMul);
					}
				}
			}
			if (zombieEatStep.getElapsedTime().asMilliseconds() > 10)
			{
				for (int i = 0; i < zombies.size(); i++)
				{
					if (player.getPoly().intersects(zombies[i].object.getGlobalBounds()) && !invinciblePerk && !timeFreezePerk)
					{
						player.health -= 1 * dt*dtMul;
						scoreNeg += dt * dtMul;
						if (scoreNeg > 1)
						{
							Score -= scoreNeg;
							scoreNeg = 0;
						}
						//zombies.erase(zombies.begin() + i);
						zombieEatStep.restart();
					}
				}
			}
		}

		// Exit level
		if (exitTimer.getElapsedTime().asSeconds() > 60.0)
		{
			door.setTextureRect(IntRect(doorTex.getSize().x / 2, 0, doorTex.getSize().x / 2, doorTex.getSize().y));
			//.setPosition(0, windowHeight - 60);
			if (player.intersects(door.getGlobalBounds()))
			{
				zombies.clear();
				ScoreText.setCharacterSize(50);
				ScoreText.setPosition(350, 200);
				scoreCard.setPosition(0, 0);
				
				if (Score > topScore)
				{
					if (!fileClose)
					{
						ofstream Boss2ScoreFileOut;
						Boss2ScoreFileOut.open("save/Boss2ScoreFile.txt");
						Boss2ScoreFileOut << Score;
						Boss2ScoreFileOut.close();
					}
					highestScoreTag.setPosition(350, 300);
				}
					else topScoreText.setPosition(400, 300);
				fileClose = 1;
				
				if(Keyboard::isKeyPressed(Keyboard::Enter))
					popScene(game);
			}
		}
	}
}


void Boss2::Draw(RenderWindow * app)
{
	app->draw(floor);
	app->draw(target);
	app->draw(door);
	player.drawTo(app);
	for (int i = 0; i < zombies.size(); i++)
		app->draw(zombies[i].object);
	app->draw(centreTable);
	app->draw(midPC);
	app->draw(bottomPC);
	for (int i = 0; i < player.bullets.size(); i++)
		app->draw(player.bullets[i].object);

	app->draw(scoreCard);
	app->draw(ScoreText);
	app->draw(topScoreText);
	app->draw(highestScoreTag);
	for (i = 0; i < diffInt; i++) app->draw(heartSprite[i]);
	
	
};