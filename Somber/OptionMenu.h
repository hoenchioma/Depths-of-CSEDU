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
	bool soundFlag = 1;////////////////sound flag
	sf::Mouse mouse;
	float dtMul = 60;
	int windowWidth = 1280;
	int windowHeight = 720;
	float backgroundScale = 1.05;
	int negPos = -500;
	int soundX = 60;
	int soundY = 360;
	//int fullscreenX = 73;
	//int fullscreenY = 460;
	int backX = 100;
	int backY = 410;
	bool scaleFlag = 0;
	sf::Texture SoundButtonOn;
	sf::Texture SoundButtonOff;
	//sf::Texture FullScreenButtonOn;
	//sf::Texture FullScreenButtonOff;
	sf::Texture BackButton;
	sf::Texture BackButtonAc;
	sf::Texture Background;
	sf::Sprite background;
	Button soundButton;
	//Button fullscreenButton;
	Button backButton;
	
	// declare variables here
};

