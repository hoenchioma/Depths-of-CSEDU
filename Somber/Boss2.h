#pragma once
#pragma once

#include "EngineX/Scene.h"
#include "EngineX/Anisprite.h"

#include <vector>
#include <cmath>
#include <cstdlib>

#include "MainChar.h"
#include "Bullet.h"
#include "Player.h"
#include "Undead.h"

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

	float dtMul = 60;
	int windowWidth = 1280;
	int windowHeight = 720;
	float speed = 5;
	float bulletTime = 60;
	float zombieSpeed = .5;
	float spawnTime = 0;
	sf::Sprite target;
	std::vector<Undead>zombies;
	sf::Texture bulletTexture;
	sf::Texture playerTexture;
	Player player;
	sf::Texture undeadTexture1;
	sf::Texture undeadTexture2;
	sf::Texture undeadTexture3;
	sf::Texture crosshair;
	sf::Mouse mouse;

	// Declare variables here
};

