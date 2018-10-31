#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "EngineX/Scene.h"
#include "EngineX/Anisprite.h"

#include <vector>
#include <cmath>
#include <cstdlib>

#include "MainChar.h"
#include "Bullet.h"
#include "Player.h"
#include "Undead.h"
#include "EngineX/eClock.h"

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
	//sf::Texture playerTexture;
	sf::Texture playerSpriteSheet;
	Player player;
	sf::Texture undeadTexture1;
	sf::Texture undeadTexture2;
	sf::Texture undeadTexture3;
	sf::Texture crosshair;
	sf::Mouse mouse;
	eClock zombieEatStep;

	// life variables
	float heartDim = 16;

	sf::Texture heartFull;
	sf::Texture heartHalf;
	sf::Texture heartEmpty;

	sf::RectangleShape heart1;
	sf::RectangleShape heart2;
	sf::RectangleShape heart3;
	sf::RectangleShape heart4;
	sf::RectangleShape heart5;

	// exit variables
	sf::Texture exitLit;
	sf::Sprite exit;
	eClock exitTimer;

	// bullet sound
	sf::SoundBuffer bulletSoundBuf;
	sf::Sound bulletSound;

	// zombie sound
	std::map <std::string, sf::SoundBuffer> zombieSoundBuf;
	std::vector <sf::Sound> zombieSound;
	std::vector <sf::Sound> zombieAttacked;

	eClock bulletSoundOffSet;

	// Declare variables here
};

