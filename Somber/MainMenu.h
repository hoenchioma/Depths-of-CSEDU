#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "EngineX/Engine.h"
#include "EngineX/Scene.h"

#include "Button.h"



class MainMenu : public Scene
{
public:
	~MainMenu() { this->Cleanup(); }

	//bool _immortal = true;
	//bool _fullScreen = true;

	void LoadRes();
	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static MainMenu* getInstance()
	{
		static MainMenu inst;
		return &inst;
	}

private:
	MainMenu() {}
	MainMenu(MainMenu const&) = delete;
	void operator= (MainMenu const&) = delete;
	bool pause = false;

	sf::Mouse mouse;
	float dtMul = 60;
	int windowWidth = 1280;
	int windowHeight = 720;
	float backgroundScale = 1.05;
	int negPos = -500;
	int playX = 100;
	int playY = 360;
	int optionX = 73;
	int optionY = 460;
	int quitX = 100;
	int quitY = 510;
	int continueX = 61;
	int continueY = 410;
	bool fileCont = 0;
	bool scaleFlag = 0;
	sf::Texture PlayButton;
	sf::Texture PlayButtonAc;
	sf::Texture ContinueButtonAvail;
	sf::Texture ContinueButtonAvailAc;
	sf::Texture ContinueButtonUnavail;
	sf::Texture OptionButton;
	sf::Texture OptionButtonAc;
	sf::Texture QuitButton;
	sf::Texture QuitButtonAc;
	sf::Texture Background;
	sf::Sprite background;
	sf::Music mainMenuSound;
	Button playButton;
	Button optionButton;
	Button quitButton;
	Button continueButton;
	
	// declare variables here
};

