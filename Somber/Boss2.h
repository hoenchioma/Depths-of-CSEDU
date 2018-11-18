#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "EngineX/Scene.h"
#include "EngineX/AniSprite.h"

#include <vector>
#include <cmath>
#include <cstdlib>

#include "MainChar.h"
#include "Bullet.h"
#include "Player.h"
#include "Undead.h"
#include "EngineX/eClock.h"

#include "InvShow.h"
#include "TextBox.h"

#include <fstream>

class PC
{
public:												//class for drawing tables
	sf::Sprite object;
};

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

	bool pause = false;					//variable declaration
	bool oonce = false;
	bool beingEaten;
	bool fileClose;
	bool perkSoundAc;
	bool speedPerk;
	bool invinciblePerk;
	bool timeFreezePerk;

	float dtMul = 60;
	float scoreNeg;
	float speed = 5;
	float bulletTime = 60;
	float zombieSpeed = .5;
	float spawnTime = 0;
	float moveTime;
	float diffFloat;
	float preUpdateHealth;
	float gameTime = 60;
	float heartDim = 16;

	long long int topScore;
	long long int Score;
	int windowWidth = 1280;
	int windowHeight = 720;
	int perkTime = 10;
	int i, j;
	int healthDiff;
	int diffInt;

	sf::Sprite target;					//declarations of sprites
	sf::Sprite highestScoreTag;
	sf::Sprite scoreCard;
	sf::Sprite floor;
	sf::Sprite pcIn;
	sf::Sprite heartSprite[10];			//declaration of health sprites
	sf::Sprite door;

	sf::Texture PCTex;						//declaration of textures
	sf::Texture PCInTex;
	sf::Texture bulletTexture;
	sf::Texture highestScoreTex;
	sf::Texture scoreCardTex;
	sf::Texture playerSpriteSheet;
	sf::Texture heartFull;
	sf::Texture heartHalf;
	sf::Texture heartEmpty;
	sf::Texture crosshair;
	sf::Texture floorTex;
	sf::Texture doorTex;
	sf::Texture zombieAttackTexL[3];		// zombie textures
	sf::Texture zombieAttackTexR[3];
	sf::Texture zombieRunTexL[3];
	sf::Texture zombieRunTexR[3];

	Player player;						//declaration of player
	std::vector<Undead>zombies;			//declaration if zombies as vectors
	PC pc[41];							//declaration of computer table or PCs on screen
	eClock zombieEatStep;
	eClock speedPerkTime;
	eClock invinciblePerkTime;
	eClock timeFreezeTime;
	eClock exitTimer;

	sf::SoundBuffer perkBuffer;			//soundBuffer declaration
	sf::SoundBuffer tempBuf;

	sf::Sound perkSound;				//sound declaration

	sf::Font displayFont;						//font declaration
	sf::Font textBoxFont;
	sf::Text ScoreText;					//text declaration
	sf::Text topScoreText;

	// bullet sound
	sf::SoundBuffer bulletSoundBuf;
	sf::SoundBuffer playerHurtBuffer;
	sf::Sound bulletSound;
	sf::Sound playerHurt;

	// zombie sound
	std::map <std::string, sf::SoundBuffer> zombieSoundBuf;
	std::vector <sf::Sound> zombieSound;
	std::vector <sf::Sound> zombieAttacked;

	sf::Mouse mouse;					//mouse information

	TextBox textBox;					//textBox

	InvShow invShow;					//Inventory

	Engine* game;						//Engine

	// Declare variables here
};


