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
#include "InvShow.h"
#include "TextBox.h"

class Floor1: public Scene
{
public:
	~Floor1() {}

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

	static Floor1* getInstance()
	{
		static Floor1 inst;
		return &inst;
	}

private:
	Floor1() {}
	Floor1(Floor1 const&) = delete;
	void operator= (Floor1 const&) = delete;
	bool pause = false;

	//sf::View& view;

	sf::Texture spriteSheet;
	MainChar mainChar;

	sf::Texture backgroundImage;
	sf::Sprite background;

	sf::Texture DoorImage;
	Door door;
	Door door2;

	sf::Texture coinSpriteSheet;
	sf::SoundBuffer coinSoundBuff;
	Coin coins[40];
	int coinCollected = 0;

	Balcony balcony;
	sf::Texture balconyTop;
	sf::Texture balconyBottom;
	sf::Texture balconyUnder;

	bool enteringdoor = false;

	sf::Font textBoxFont;
	TextBox textBox;

	InvShow invShow;

	Engine* game;

	// game successfully completed the game
	bool endGame = false;
};
