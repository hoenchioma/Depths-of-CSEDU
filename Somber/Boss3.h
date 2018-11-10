#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>

#include "EngineX/Scene.h"

#include "MainChar.h"
#include "Grid.h"
#include "Snek.h"
#include "Walls.h"
#include "TextBox.h"
#include "RestartMenu.h"
#include "TimeText.h"
#include "InvShow.h"

class Boss3 : public Scene
{
public:
	~Boss3() { this->Cleanup(); }

	void LoadRes();
	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static Boss3* getInstance()
	{
		static Boss3 inst;
		return &inst;
	}

private:
	Boss3() {}
	Boss3(Boss3 const&) = delete;
	void operator= (Boss3 const&) = delete;
	bool pause = false;
	Engine* game;

	const int CanvasWidth = 2000;
	const int CanvasHeight = 2000;

	bool InitOnce = false;

	sf::Texture characterSpriteSheet;

	MainChar mainChar;
	Grid grid;

	Snek snek;
	sf::Texture headTex;
	sf::Texture bodyTex;
	sf::Texture tailTex;
	sf::Texture jointTex;

	sf::Texture wallTexture;
	Walls walls;

	sf::Texture appleTex;
	sf::Sprite apple;

	sf::Font textBoxFont;
	TextBox textBox;

	InvShow invShow;

	sf::Texture floorTex;
	sf::Sprite floor;

	RestartMenu menu;

	TimeText timeText;
	sf::View timeView;

	// score and high score card
	sf::Texture highestScoreTex;
	sf::Texture scoreCardTex;
	sf::Font highScoreFont;

	sf::Sprite highestScoreTag;
	sf::Sprite scoreCard;

	sf::Text scoreToText;
	sf::Text topScoreText;

	// game control
	bool GameOver;
	bool instantWin;

	// perks
	eClock speedT;
	eClock reLifeT;
	eClock timeFreezeT;
	eClock phaseT;

	bool speedB;
	bool reLifeB;
	bool timeFreezeB;
	bool phaseB;
	bool phaseBOnce;

	// sound effects
	sf::Sound snakehiss;
	sf::SoundBuffer hissBuff;
	eClock hissTime;

	sf::Sound snakehit;
	sf::SoundBuffer hitBuff;
};