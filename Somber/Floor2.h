#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "EngineX/Scene.h"
#include "EngineX/AniSprite.h"

#include "MainChar.h"
#include "Door.h"
#include "Coin.h"
#include "Balcony.h"

class Floor2 : public Scene
{
public:
	~Floor2() { this->Cleanup(); }

	bool _immortal = true;

	void LoadRes();
	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static Floor2* getInstance()
	{
		static Floor2 inst;
		return &inst;
	}

private:
	Floor2() {}
	Floor2(Floor2 const&) = delete;
	void operator= (Floor2 const&) = delete;
	bool pause = false;

	//sf::View& view;

	sf::Texture spriteSheet;
	MainChar mainChar;

	sf::Texture backgroundImage;
	sf::Sprite background;

	sf::Texture DoorImage;
	Door door;
	

	sf::Texture coinSpriteSheet;
	sf::SoundBuffer sound;
	Coin coins[20];
	int coinCollected = 0;
	sf::RectangleShape box;
	Balcony balcony;
	sf::Texture balconyTop;
	sf::Texture balconyBottom;
	sf::Texture balconyUnder;
	sf::Sprite floor2Cover;
	sf::Texture floor2CovTex;


	bool enteringdoor = false;
};