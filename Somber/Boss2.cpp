#include "Boss2.h"

#include "EngineX/Utility.h"
#include "Floor1.h"

#include <iostream>

using namespace sf;
using namespace std;

void Boss2::LoadRes()
{
	loadFromFile(bulletTexture, "res/bullet.png");
	loadFromFile(playerTexture, "res/player.png");
	loadFromFile(undeadTexture1, "res/undead1.png");
	loadFromFile(undeadTexture2, "res/undead2.png");
	loadFromFile(undeadTexture3, "res/undead3.png");
	loadFromFile(crosshair, "res/crosshair.png");
}

void Boss2::Init(Engine* game)
{
	game->app->setMouseCursorVisible(false);
	undeadTexture1.setSmooth(true);
	undeadTexture2.setSmooth(true);
	undeadTexture3.setSmooth(true);
	player.Init(&playerTexture);
	player.object.setPosition(windowWidth / 2, windowHeight / 2);
	target.setTexture(crosshair);
	target.setScale(0.1, 0.1);
	sf::Mouse mouse;

	//Init
}

void Boss2::Cleanup()
{
}

void Boss2::Pause()
{
	//player.running = false;
	pause = true;

	// this function is going to be called when the game is paused
}

void Boss2::Resume()
{
	pause = false;

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

		if (player.health > 0)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up))
				player.object.move(0, -speed * dt*dtMul);
			if (Keyboard::isKeyPressed(Keyboard::Down))
				player.object.move(0, speed*dt*dtMul);
			if (Keyboard::isKeyPressed(Keyboard::Left))
				player.object.move(-speed * dt*dtMul, 0);
			if (Keyboard::isKeyPressed(Keyboard::Right))
				player.object.move(speed*dt*dtMul, 0);
			if (bulletTime < 35)
				bulletTime += 1 * dt*dtMul;
			if (Mouse::isButtonPressed(Mouse::Left) && bulletTime >= 35)
			{
				player.bullets.push_back(Bullet(&bulletTexture, player.object.getPosition(), Mouse::getPosition(*game->app)));
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
				if (zombies[i].object.getPosition().x > player.object.getPosition().x) zombies[i].object.move(-zombieSpeed * dt*dtMul, 0);
				if (zombies[i].object.getPosition().x < player.object.getPosition().x) zombies[i].object.move(zombieSpeed*dt*dtMul, 0);
				if (zombies[i].object.getPosition().y > player.object.getPosition().y) zombies[i].object.move(0, -zombieSpeed * dt*dtMul);
				if (zombies[i].object.getPosition().y < player.object.getPosition().y) zombies[i].object.move(0, zombieSpeed*dt*dtMul);
				if (zombies[i].object.getPosition().x < 0 || zombies[i].object.getPosition().y < 0 || zombies[i].object.getPosition().x >windowWidth || zombies[i].object.getPosition().y > windowHeight)
				{
					zombies.erase(zombies.begin() + i);
				}
				if (player.object.getGlobalBounds().intersects(zombies[i].object.getGlobalBounds()))
				{
					player.health--;
					zombies.erase(zombies.begin() + i);
				}
			}
		}
	}
}


void Boss2::Draw(RenderWindow * app)
{
	app->draw(target);
	app->draw(player.object);
	for (int i = 0; i < player.bullets.size(); i++)
	{
		app->draw(player.bullets[i].object);
	}
	for (int i = 0; i < zombies.size(); i++)
		app->draw(zombies[i].object);
};






