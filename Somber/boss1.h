#pragma once

#include "EngineX/Scene.h"
#include "EngineX/AniSprite.h"
#include "MainChar.h"
#include "Spotlight.h"
#include "FuseInfo.h"

#include "TextBox.h"
#include "RestartMenu.h"
#include <fstream>

class TableEEE
{
public:
	sf::Sprite object;
	//int ICnum;
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


	int windowWidth = 1280;
	int windowHeight = 720;
	int fuseCount;
	Spotlight lights[4];
	float dtMul = 50;
	float spriteSize = 20;
	const int LEFT = -1;
	const int RIGHT = 1;
	const int UP = -1;
	const int DOWN = 1;
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
	int randLimitW = fuseWidth + 400;
	int randLimitH = fuseHeight + 400;
	int i;
	int timeTextSec;
	int timeTextMin;
	double timeStore;
	int timeTotal;
	bool exitFlag;
	bool gameOverFlag;
	int topTime;
	bool fileClose;
	bool speedPerk;
	bool invinciblePerk;
	bool timeFreeze;
	int perkTime = 10;
	int healthDiff;
	int diffInt;
	float diffFloat;

	sf::Sprite heartSprite[10];
	sf::Sprite highestScoreTag;
	sf::Sprite  scoreCard;
	sf::Sprite floor;
	sf::Sprite door;
	sf::Sprite bot3Side;
	sf::Sprite bot4Side;
	FuseInfo fuse[7];
	TableEEE tableDLD[7],tableBottom;
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
	MainChar player;
	eClock speedPerkTime;
	eClock invinciblePerkTime;
	eClock timeFreezeTime;
	
	/*sf::RectangleShape heart1;
	sf::RectangleShape heart2;
	sf::RectangleShape heart3;
	sf::RectangleShape heart4;
	sf::RectangleShape heart5;*/
	//sf::Vector2f position = player.getPosition();


	sf::Font font;
	sf::Text scoreToText;
	//sf::Text secToText;
	sf::Text fuseNumber;
	sf::Text topScoreText;

	//std::fstream Boss1ScoreFile;


	//sf::View view1;

	//sf::RectangleShape* fuseArray[5] = { &fuse1, &fuse2, &fuse3, &fuse4, &fuse5 };
	//sf::CircleShape* spotlightArray[3] = { &spotlight1, &spotlight2, &spotlight3 };

	sf::Uint8 light;

	// temporarily stores the gameView
	sf::View* _gameViewtemp;

	Engine* game;

	sf::Font textBoxFont;
	TextBox textBox;
	RestartMenu menu;
};