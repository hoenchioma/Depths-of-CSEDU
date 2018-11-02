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
	loadFromFile(exitLit, "res/exitLit.png");
	loadFromFile(bulletSoundBuf, "res/Sounds/40_smith_wesson_8x_gunshot-mike-koenig_2.wav");
	sf::SoundBuffer tempBuf;
	loadFromFile(tempBuf, "res/Sounds/Zombie Gets Attacked-SoundBible.com-20348330.wav");
	zombieSoundBuf.insert({ "zombie_attacked", tempBuf });
}

void Boss2::Init(Engine* game)
{
	game->app->setMouseCursorVisible(false);
	undeadTexture1.setSmooth(true);
	undeadTexture2.setSmooth(true);
	undeadTexture3.setSmooth(true);
	//player.Init(&playerTexture);

	player.Init(playerSpriteSheet, 0.1f, 300.f);
	//player.setScale(1.4f, 1.4f);
	player.setPosition(windowWidth / 2.0, windowHeight / 2.0);

	target.setTexture(crosshair);
	target.setScale(0.1, 0.1);
	sf::Mouse mouse;
	
	// life variables
	heartDim = 16;

	heart1.setSize(Vector2f(heartDim, heartDim));
	heart2.setSize(Vector2f(heartDim, heartDim));
	heart3.setSize(Vector2f(heartDim, heartDim));
	heart4.setSize(Vector2f(heartDim, heartDim));
	heart5.setSize(Vector2f(heartDim, heartDim));

	heart1.setOutlineColor(sf::Color::Transparent);
	heart2.setOutlineColor(sf::Color::Transparent);
	heart3.setOutlineColor(sf::Color::Transparent);
	heart4.setOutlineColor(sf::Color::Transparent);
	heart5.setOutlineColor(sf::Color::Transparent);

	heart5.setPosition(5, 5);
	heart4.setPosition(heartDim + 7, 5);
	heart3.setPosition(2 * heartDim + 9, 5);
	heart2.setPosition(3 * heartDim + 11, 5);
	heart1.setPosition(4 * heartDim + 13, 5);

	heart1.setTexture(&heartFull);
	heart2.setTexture(&heartFull);
	heart3.setTexture(&heartFull);
	heart4.setTexture(&heartFull);
	heart5.setTexture(&heartFull);

	// exit variables
	exit.setScale(0.4f, 0.4f);
	//exit.setPosition(0, windowHeight - 60);
	exit.setPosition(1e7, 1e7);
	exit.setTexture(exitLit);
	exitTimer.restart();

	// sound
	bulletSound.setBuffer(bulletSoundBuf);
	bulletSound.setVolume(20);

	zombieAttacked.push_back(Sound(zombieSoundBuf["zombie_attacked"]));
	zombieAttacked.back().setVolume(50);
	zombieAttacked.push_back(Sound());

	//Init
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
		target.setPosition(mouse.getPosition(*game->app).x - crosshair.getSize().x / 20, mouse.getPosition(*game->app).y - crosshair.getSize().y / 20);

		if		(player.health <= 140	&&	player.health > 130)	heart1.setTexture(&heartHalf);
		else if (player.health <= 130	&&	player.health > 120)	heart1.setTexture(&heartEmpty);
		else if (player.health <= 120	&&	player.health > 110)	heart1.setPosition(-500, 0);
		else if (player.health <= 110	&&	player.health > 100)	heart2.setTexture(&heartHalf);
		else if (player.health <= 100	&&	player.health > 90)		heart2.setTexture(&heartEmpty);
		else if (player.health <= 90	&&	player.health > 80)		heart2.setPosition(-500, 0);
		else if (player.health <= 80	&&	player.health > 70)		heart3.setTexture(&heartHalf);
		else if (player.health <= 70	&&	player.health > 60)		heart3.setTexture(&heartEmpty);
		else if (player.health <= 60	&&	player.health > 50)		heart3.setPosition(-500, 0);
		else if (player.health <= 50	&&	player.health > 40)		heart4.setTexture(&heartHalf);
		else if (player.health <= 40	&&	player.health > 30)		heart4.setTexture(&heartEmpty);
		else if (player.health <= 30	&&	player.health > 20)		heart4.setPosition(-500, 0);
		else if (player.health <= 20	&&	player.health > 10)		heart5.setTexture(&heartHalf);
		else if (player.health <= 10	&&	player.health > 0)		heart5.setTexture(&heartEmpty);
		else if (player.health <= 0)
		{
			// restarts game
			reset(game);
		}

		if (player.health > 0)
		{
			/*if (Keyboard::isKeyPressed(Keyboard::Up))
				player.object.move(0, -speed * dt*dtMul);
			if (Keyboard::isKeyPressed(Keyboard::Down))
				player.object.move(0, speed*dt*dtMul);
			if (Keyboard::isKeyPressed(Keyboard::Left))
				player.object.move(-speed * dt*dtMul, 0);
			if (Keyboard::isKeyPressed(Keyboard::Right))
				player.object.move(speed*dt*dtMul, 0);*/

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
				if (zombies[i].object.getPosition().x > player.getPosition().x) zombies[i].object.move(-zombieSpeed * dt*dtMul, 0);
				if (zombies[i].object.getPosition().x < player.getPosition().x) zombies[i].object.move(zombieSpeed*dt*dtMul, 0);
				if (zombies[i].object.getPosition().y > player.getPosition().y) zombies[i].object.move(0, -zombieSpeed * dt*dtMul);
				if (zombies[i].object.getPosition().y < player.getPosition().y) zombies[i].object.move(0, zombieSpeed*dt*dtMul);
				if (zombies[i].object.getPosition().x < 0 || zombies[i].object.getPosition().y < 0 || zombies[i].object.getPosition().x >windowWidth || zombies[i].object.getPosition().y > windowHeight)
				{
					zombies.erase(zombies.begin() + i);
				}
			}
			if (zombieEatStep.getElapsedTime().asMilliseconds() > 10)
			{
				for (int i = 0; i < zombies.size(); i++)
				{
					if (player.getPoly().intersects(zombies[i].object.getGlobalBounds()))
					{
						player.health--;
						//zombies.erase(zombies.begin() + i);
						zombieEatStep.restart();
					}
				}
			}
		}

		// Exit level
		if (exitTimer.getElapsedTime().asSeconds() > 60.0)
		{
			exit.setPosition(0, windowHeight - 60);
			if (player.intersects(exit.getGlobalBounds()))
			{
				popScene(game);
			}
		}
	}
}


void Boss2::Draw(RenderWindow * app)
{
	app->draw(target);
	//app->draw(player.object);
	player.drawTo(app);
	for (int i = 0; i < player.bullets.size(); i++)
		app->draw(player.bullets[i].object);
	for (int i = 0; i < zombies.size(); i++)
		app->draw(zombies[i].object);

	app->draw(heart1);
	app->draw(heart2);
	app->draw(heart3);
	app->draw(heart4);
	app->draw(heart5);

	app->draw(exit);
};






