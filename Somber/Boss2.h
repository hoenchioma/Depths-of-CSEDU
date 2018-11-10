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

#include <fstream>




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
	long long int Score;
	float dtMul = 60;
	float scoreNeg;
	int windowWidth = 1280;
	int windowHeight = 720;
	float speed = 5;
	float bulletTime = 60;
	float zombieSpeed = .5;
	float spawnTime = 0;
	float moveTime;
	int topScore;
	bool fileClose;

	bool speedPerk;
	bool invinciblePerk;
	bool timeFreezePerk;
	int perkTime = 10;
	int i;
	int healthDiff;
	int diffInt;
	float diffFloat;



	sf::Sprite target;
	sf::Sprite highestScoreTag;
	sf::Sprite  scoreCard;
	sf::Sprite floor;
	sf::Sprite bottomPC;
	sf::Sprite midPC;

	sf::Sprite centreTable;
	std::vector<Undead>zombies;
	sf::Texture bulletTexture;
	sf::Texture highestScoreTex;
	sf::Texture scoreCardTex;
	//sf::Texture playerTexture;
	sf::Texture playerSpriteSheet;
	Player player;
	sf::Texture undeadTexture1;
	sf::Texture undeadTexture2;
	sf::Texture undeadTexture3;
	sf::Texture crosshair;
	sf::Texture floorTex;
	sf::Texture midPCTex;
	sf::Texture centreTableTex;
	sf::Mouse mouse;
	eClock zombieEatStep;
	eClock speedPerkTime;
	eClock invinciblePerkTime;
	eClock timeFreezeTime;

	sf::SoundBuffer perkBuffer;
	sf::Sound perkSound;
	

	sf::Sprite heartSprite[10];
	// life variables
	float heartDim = 16;

	sf::Texture heartFull;
	sf::Texture heartHalf;
	sf::Texture heartEmpty;

	//sf::RectangleShape heart1;
	//sf::RectangleShape heart2;
	//sf::RectangleShape heart3;
	//sf::RectangleShape heart4;
	//sf::RectangleShape heart5;

	// exit variables
	sf::Texture doorTex;
	//sf::Texture doorOpenTex;
	sf::Sprite door;
	sf::Font font;
	sf::Text ScoreText;
	sf::Text topScoreText;
	eClock exitTimer;
	
	// bullet sound
	sf::SoundBuffer bulletSoundBuf;
	sf::Sound bulletSound;

	// zombie sound
	std::map <std::string, sf::SoundBuffer> zombieSoundBuf;
	std::vector <sf::Sound> zombieSound;
	std::vector <sf::Sound> zombieAttacked;


	//eClock bulletSoundOffSet;

	// Declare variables here
};

