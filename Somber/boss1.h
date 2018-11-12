#pragma once

#include "EngineX/Scene.h"
#include "EngineX/AniSprite.h"
#include "MainChar.h"
#include "Spotlight.h"
#include "FuseInfo.h"

#include "TextBox.h"
#include "RestartMenu.h"
#include <fstream>
#include <SFML/Audio.hpp>
#include "InvShow.h"

class TableEEE
{
public:
	sf::Sprite object;
};


class Boss1 : public Scene
{
public:
	~Boss1() {}

	void LoadRes();
	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static Boss1* getInstance()
	{
		static Boss1 inst;
		return &inst;
	}

private:
	Boss1() {}
	Boss1(Boss1 const&) = delete;
	void operator= (Boss1 const&) = delete;
	bool pause = false;

	const int LEFT = -1;
	const int RIGHT = 1;
	const int UP = -1;
	const int DOWN = 1;

	int windowWidth = 1280;
	int windowHeight = 720;
	int fuseCount;
	int randLimitW = fuseWidth + 400;
	int randLimitH = fuseHeight + 400;
	int i;
	int timeTextSec;						//stores time in seconds
	int timeTextMin;						//stores time in minutes
	int topTime;
	int timeTotal;
	int perkTime = 10;
	int healthDiff;
	int diffInt;
										
	float dtMul = 50;						//multiplier for framerame independency
	float spriteSize = 20;
	float speedSpotlight = 3 * dtMul;
	float fuseHealth = 100;
	float damageFuse;
	float fuseDis = 70;
	float range = 25;
	float fuseWidth = 30;
	float fuseHeight = 45;
	float spotlightDamageRange = RADIUS_SPOTLIGHT + spriteSize - 5;
	float spriteHealth = 150;
	float lightDamage = .5*dtMul;
	float healthBar = 10;
	float heartDim = 16;
	float barDis = 40 - fuseWidth / 2;
	float diffFloat;
	float preUpdateHealth;
	float timeStore;

	bool exitFlag;
	bool gameOverFlag;
	bool fileClose;
	bool speedPerk;
	bool invinciblePerk;
	bool timeFreezePerk;
	bool once = false;
											//sprites
	sf::Sprite heartSprite[10];
	sf::Sprite highestScoreTag;
	sf::Sprite  scoreCard;
	sf::Sprite floor;
	sf::Sprite door;
	sf::Sprite bot3Side;
	sf::Sprite bot4Side;
											//textures
	sf::Texture highestScoreTex;
	sf::Texture scoreCardTex;
	sf::Texture floorTexture;
	sf::Texture tex;
	sf::Texture fuseOpened;
	sf::Texture heartFull;
	sf::Texture heartHalf;
	sf::Texture heartEmpty;
	sf::Texture tableFlipTex;
	sf::Texture tableHorTex;
	sf::Texture tableNormTex;
	sf::Texture tableBotTex;
	sf::Texture doorOpenTex;
	sf::Texture doorCloseTex;
	sf::Texture fuseBotSideOpenTex;
											//declaration of custom classes for boss1
	FuseInfo fuse[7];						//fuses declaration

	TableEEE tableDLD[7], tableBottom;		//tables declaration

	Spotlight lights[4];

	MainChar player;

	eClock speedPerkTime;
	eClock invinciblePerkTime;
	eClock timeFreezeTime;
	
	sf::SoundBuffer perkBuffer;				//soundBuffer declaration
	sf::SoundBuffer playerHurtBuffer;

	sf::Sound perkSound;					//sound declaration
	sf::Sound playerHurt;

	sf::Font displayFont;							//font declaration
	sf::Font textBoxFont;

	sf::Text scoreToText;					//text declaration
	sf::Text fuseNumber;
	sf::Text topScoreText;

	sf::Uint8 light;

	sf::View* _gameViewtemp;           		// temporarily stores the gameView

	Engine* game;							//Engine

	TextBox textBox;						//textBox

	RestartMenu menu;						//Restart menu

	InvShow invShow;						//Inventory

	// Declare variables here
};


