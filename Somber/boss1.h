#pragma once

#include "EngineX/Scene.h"
#include "EngineX/AniSprite.h"
#include "mainChar.h"

class boss1 : public Scene
{
public:
	~boss1() { this->Cleanup(); }

	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static boss1* getInstance()
	{
		static boss1 inst;
		return &inst;
	}

private:
	boss1() {}
	boss1(boss1 const&) = delete;
	void operator= (boss1 const&) = delete;
	bool pause = false;

	// Declare variables here

	int windowWidth;
	int windowHeight;
	int gameOver = 0;
	float radiusSpotlight = 150;
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
	float speedSpotlight = 7;
	float spriteX = 1000;
	float fuseHealth = 100;
	float spriteY = 500;
	float speed = 5;
	float damageFuse = .2;
	float fuseDis = 40;
	float range = 15;
	float fuseWidth = 30;
	float fuseHeight = 15;
	float spotlightDamageRange = radiusSpotlight + spriteSize - 5;
	float spriteHealth = 100;
	float lightDamage = 1;
	float healthBar = 10;
	float barDis = 5;

	struct fuseInfo {
		float Health = 100;
		float X;
		float Y;
	};
	fuseInfo fuse[10];

	sf::CircleShape spotlight1;
	sf::CircleShape spotlight2;
	sf::CircleShape spotlight3;
	sf::CircleShape sprite;
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
	sf::RectangleShape healthBarSprite;

	double centreDis(float X1, float Y1, float X2, float Y2)
	{
		double  distance = sqrt(pow((X1 - X2), 2) + pow((Y1 - Y2), 2));
		return distance;
	}
};

