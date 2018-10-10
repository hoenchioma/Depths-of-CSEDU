#pragma once

#include "EngineX/Scene.h"
#include "EngineX/AniSprite.h"
#include "mainChar.h"
#include "door.h"

class floor1: public Scene
{
public:
	~floor1() { this->Cleanup(); }

	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static floor1* getInstance()
	{
		static floor1 inst;
		return &inst;
	}

private:
	floor1() {}
	floor1(floor1 const&) = delete;
	void operator= (floor1 const&) = delete;
	bool pause = false;

	sf::View view;

	sf::Texture spriteSheet;
	mainChar MainChar;

	sf::Texture backgroundImage;
	sf::Sprite background;

	sf::Texture doorImage;
	door Door;

	sf::Texture coinSpriteSheet;
	AniSprite coins[20];
	int coinCollected = 0;
};