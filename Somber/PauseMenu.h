#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "EngineX/Engine.h"
#include "EngineX/Scene.h"

#include "Button.h"


class PauseMenu : public Scene
{
public:
	~PauseMenu() { this->Cleanup(); }

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

	static PauseMenu* getInstance()
	{
		static PauseMenu inst;
		return &inst;
	}

private:
	PauseMenu() {}
	PauseMenu(PauseMenu const&) = delete;
	void operator= (PauseMenu const&) = delete;
	bool pause = false;

	sf::Mouse mouse;
	float dtMul = 60;
	int windowWidth = 1280;
	int windowHeight = 720;
	float backgroundScale = 1.05;
	int negPos = -500;
	int resumeX = 130;
	int resumeY = 360;
	int invInfoX = 73;
	int invInfoY = 410;
	int saveNQuitX = 73;
	int saveNQuitY = 460;
	int quitX = 150;
	int quitY = 510;
	bool levelAc=0;
	bool scaleFlag = 0;
	sf::Texture ResumeButton;
	sf::Texture ResumeButtonAc;
	sf::Texture InvInfoButton;
	sf::Texture InvInfoButtonAc;
	sf::Texture SaveNQuitButton;
	sf::Texture SaveNQuitButtonAc;
	sf::Texture SaveNQuitButtonUnavail;
	sf::Texture QuitButton;
	sf::Texture QuitButtonAc;
	sf::Texture Background;
	sf::Sprite background;
	sf::Music PauseMenuSound;
	Button resumeButton;
	Button invInfoButton;
	Button saveNQuitButton;
	Button quitButton;
	
	
	// declare variables here
};

