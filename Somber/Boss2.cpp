#include "Boss2.h"

#include "EngineX/Utility.h"

#include <iostream>

using namespace sf;
using namespace std;

void Boss2::LoadRes()
{
	bulletTexture.loadFromFile("bullet.png");
	spriteTexture.loadFromFile("sprite.png");
	undeadTexture1.loadFromFile("undead1.png");
	undeadTexture2.loadFromFile("undead2.png");
	undeadTexture3.loadFromFile("undead3.png");
	crosshair.loadFromFile("res/crosshair.png");
}

void Boss2::Init(Engine* game)
{
	game->app->setMouseCursorVisible(false);
	undeadTexture1.setSmooth(true);
	undeadTexture2.setSmooth(true);
	undeadTexture3.setSmooth(true);
	sprite.object.setPosition(windowWidth / 2, windowHeight / 2);
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
	//Sprite.running = false;
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
		target.setPosition(mouse.getPosition(*game->app).x - crosshair.getSize().x / 20, mouse.getPosition(window).y - crosshair.getSize().y / 20);

		if (sprite.health > 0)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up))
				sprite.object.move(0, -speed * dt*dtMul);
			if (Keyboard::isKeyPressed(Keyboard::Down))
				sprite.object.move(0, speed*dt*dtMul);
			if (Keyboard::isKeyPressed(Keyboard::Left))
				sprite.object.move(-speed * dt*dtMul, 0);
			if (Keyboard::isKeyPressed(Keyboard::Right))
				sprite.object.move(speed*dt*dtMul, 0);
			if (bulletTime < 35)
				bulletTime += 1 * dt*dtMul;
			if (Mouse::isButtonPressed(Mouse::Left) && bulletTime >= 35)
			{
				sprite.bullets.push_back(bullet(&bulletTexture, sprite.object.getPosition(), Mouse::getPosition(window)));
				bulletTime = 0;
			}
			for (int i = 0; i < sprite.bullets.size(); i++)
			{
				sprite.bullets[i].object.move(15 * sprite.bullets[i].bulletMulX*dt*dtMul, 15 * sprite.bullets[i].bulletMulY*dt*dtMul);
				if (sprite.bullets[i].object.getPosition().x > windowWidth || sprite.bullets[i].object.getPosition().x < 0 || sprite.bullets[i].object.getPosition().y > windowHeight || sprite.bullets[i].object.getPosition().y > windowHeight)
				{
					sprite.bullets.erase(sprite.bullets.begin() + i);
					break;
				}
				for (j = 0; j < zombies.size(); j++)
				{
					if (sprite.bullets[i].object.getGlobalBounds().intersects(zombies[j].object.getGlobalBounds()))
					{
						if (zombies[j].health <= 1)
						{
							zombies.erase(zombies.begin() + j);
						}
						else
						{
							zombies[j].health--;
						}
						sprite.bullets.erase(sprite.bullets.begin() + i);
						break;
					}
				}
			}
			if (spawnTime < 80) spawnTime += 1 * dt*dtMul;
			if (spawnTime >= 80)
			{
				zombies.push_back(undead(&undeadTexture1, &undeadTexture2, &undeadTexture3));
				spawnTime = 0;
			}
			for (int i = 0; i < zombies.size(); i++)
			{
				if (zombies[i].object.getPosition().x > sprite.object.getPosition().x) zombies[i].object.move(-zombieSpeed * dt*dtMul, 0);
				if (zombies[i].object.getPosition().x < sprite.object.getPosition().x) zombies[i].object.move(zombieSpeed*dt*dtMul, 0);
				if (zombies[i].object.getPosition().y > sprite.object.getPosition().y) zombies[i].object.move(0, -zombieSpeed * dt*dtMul);
				if (zombies[i].object.getPosition().y < sprite.object.getPosition().y) zombies[i].object.move(0, zombieSpeed*dt*dtMul);
				if (zombies[i].object.getPosition().x < 0 || zombies[i].object.getPosition().y < 0 || zombies[i].object.getPosition().x >windowWidth || zombies[i].object.getPosition().y > windowHeight)
				{
					zombies.erase(zombies.begin() + i);
				}
				if (sprite.object.getGlobalBounds().intersects(zombies[i].object.getGlobalBounds()))
				{
					sprite.health--;
					zombies.erase(zombies.begin() + i);
				}
			}
		}
	}
}


void Boss2::Draw(RenderWindow * app)
{
	app->draw(target);
	app->draw(sprite.object);
	for (int i = 0; i < sprite.bullets.size(); i++)
	{
		app->draw(sprite.bullets[i].object);
	}
	for (int i = 0; i < zombies.size(); i++)
		app->draw(zombies[i].object);
};






