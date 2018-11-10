#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "EngineX/Engine.h"
#include "EngineX/Scene.h"

#include "Button.h"


class OptionMenu : public Scene
{
public:
	~OptionMenu() { this->Cleanup(); }

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

	static OptionMenu* getInstance()
	{
		static OptionMenu inst;
		return &inst;
	}

private:
	OptionMenu() {}
	OptionMenu(OptionMenu const&) = delete;
	void operator= (OptionMenu const&) = delete;
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
	bool scaleFlag = 0;
	sf::Texture SoundButtonOn;
	sf::Texture SoundButtonOff;
	sf::Texture FullScreenButtonOn;
	sf::Texture FullScreenButtonOff;
	sf::Texture BackButton;
	sf::Texture BackButttonAc;
	sf::Texture Background;
	sf::Sprite background;
	Button soundButton;
	Button fullscreenButton;
	Button backButton;
	
	// declare variables here
};

