#pragma once
#pragma once

#include "EngineX/Scene.h"
#include "EngineX/AniSprite.h"
#include "MainChar.h"
#include <cmath>
#include <cstdlib>
#include <vector>

class Boss2 : public Scene
{
public:
	~Boss2() { this->Cleanup(); }

	void LoadRes();
	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static Boss2* getInstance()
	{
		static Boss2 inst;
		return &inst;
	}

private:
	Boss2() {}
	Boss2(Boss2 const&) = delete;
	void operator= (Boss2 const&) = delete;
	bool pause = false;
	class bullet
	{
	public:
		Sprite object;
		double bulletMulX;
		double bulletMulY;
		double dis;
		bullet(Texture *texture, Vector2f position, Vector2i click)
		{
			object.setTexture(*texture);
			object.setScale(.06, .06);
			object.setPosition(position);
			bulletMulX = click.x - position.x;
			bulletMulY = click.y - position.y;
			dis = sqrt(pow(bulletMulX, 2) + pow(bulletMulY, 2));
			bulletMulX /= dis;
			bulletMulY /= dis;
		}
		~bullet() {}
	};
	class sprite
	{
	public:
		int health;
		Sprite object;
		std::vector<bullet> bullets;
		sprite(Texture *texture)
		{
			health = 150;
			object.setTexture(*texture);
		}
		~sprite() {}
	};
	class undead
	{
	public:
		Sprite object;
		int health;
		int maxHealth;
		int position;
		undead(Texture *texture1, Texture *texture2, Texture *texture3)
		{
			maxHealth = rand() % 3 + 1;
			position = rand() % 8 + 1;
			health = maxHealth;
			if (maxHealth == 1)
				object.setTexture(*texture1);
			else if (maxHealth == 2)
				object.setTexture(*texture2);
			else if (maxHealth == 3)
				object.setTexture(*texture3);
			object.setScale(.1, .1);
			if (position == 1)
				object.setPosition(1180, 100);
			else if (position == 2)
				object.setPosition(1180, 360);
			else if (position == 3)
				object.setPosition(1180, 620);
			else if (position == 4)
				object.setPosition(640, 620);
			else if (position == 5)
				object.setPosition(100, 620);
			else if (position == 6)
				object.setPosition(100, 360);
			else if (position == 7)
				object.setPosition(100, 100);
			else if (position == 8)
				object.setPosition(640, 100);

		}


		float dtMul = 60;
		int windowWidth = 1280;
		int windowHeight = 720;
		float speed = 5;
		float bulletTime = 60;
		float zombieSpeed = .5;
		float spawnTime = 0;
		Sprite target;
		std::vector<undead>zombies;
		//window.setFramerateLimit(60);
		Texture bulletTexture;
		Texture spriteTexture;
		sprite sprite(&spriteTexture);
		Texture undeadTexture1;
		Texture undeadTexture2;
		Texture undeadTexture3;
		Texture crosshair;
		sf::Mouse mouse;

	// Declare variables here
};

