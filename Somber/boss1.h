#pragma once

#include "EngineX/Scene.h"
#include "EngineX/AniSprite.h"
#include "MainChar.h"

class Boss1 : public Scene
{
public:
	~Boss1() { this->Cleanup(); }

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

	struct fuseInfo {
		float Health = 100;
		float X;
		float Y;
	};
	int windowWidth = 2000;
	int windowHeight = 1500;
	float dtMul = 50;
	float radiusSpotlight = 125;
	float diameterSpotlight = 2 * radiusSpotlight;
	float spriteSize = 20;
	float spotlight1X = 0;
	float spotlight1Y = 0;
	float spotlight2X = windowWidth / 2;
	float spotlight2Y = windowHeight;
	float spotlight3X = windowWidth;
	float spotlight3Y = windowHeight / 5;
	const float LEFT = -1;
	const float RIGHT = 1;
	const float UP = -1;
	const float DOWN = 1;
	float spotlight1DirX = RIGHT;
	float spotlight1DirY = DOWN;
	float spotlight2DirX = LEFT;
	float spotlight2DirY = UP;
	float spotlight3DirX = LEFT;
	float spotlight3DirY = UP;
	float speedSpotlight = 2.5*dtMul;
	float fuseHealth = 100;
	float speed = 5;
	float damageFuse;// = .5*dtMul;
	float fuseDis = 70;
	float range = 25;
	float fuseWidth = 30;
	float fuseHeight = 45;
	float spotlightDamageRange = radiusSpotlight + spriteSize - 5;
	float spriteHealth = 150;
	float lightDamage = .5*dtMul;
	float healthBar = 10;
	float heartDim = 16;
	float barDis = 50-fuseWidth/2;
	int randLimitW = fuseWidth + 200;
	int randLimitH = fuseHeight + 200;
	fuseInfo fuse[10];
	sf::Texture tex;
	sf::Texture fuseClosed;
	sf::Texture fuseOpened;
	sf::Texture heartFull;
	sf::Texture heartHalf;
	sf::Texture heartEmpty;
	sf::Texture exitDim;
	sf::Texture exitLit;
	MainChar Sprite;
	sf::CircleShape spotlight1;
	sf::CircleShape spotlight2;
	sf::CircleShape spotlight3;
	sf::RectangleShape fuse1;
	sf::RectangleShape fuse2;
	sf::RectangleShape fuse3;
	sf::RectangleShape fuse4;
	sf::RectangleShape fuse5;
	sf::RectangleShape fuse1Bar;
	sf::RectangleShape fuse2Bar;
	sf::RectangleShape fuse3Bar;
	sf::RectangleShape fuse4Bar;
	sf::RectangleShape fuse5Bar;
	sf::RectangleShape heart1;
	sf::RectangleShape heart2;
	sf::RectangleShape heart3;
	sf::RectangleShape heart4;
	sf::RectangleShape heart5;
	sf::RectangleShape exit;
	sf::Vector2f position = Sprite.getPosition();
	//sf::View view1;
	

	sf::RectangleShape* fuseArray[5] = { &fuse1, &fuse2, &fuse3, &fuse4, &fuse5 };
	sf::CircleShape* spotlightArray[3] = { &spotlight1, &spotlight2, &spotlight3 };

	sf::Uint8 light;

	// temporarily stores the gameView
	sf::View* _gameViewtemp;
};

