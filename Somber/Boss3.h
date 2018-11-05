#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "EngineX/Scene.h"

#include "MainChar.h"
#include "Grid.h"
#include "Snek.h"

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

	sf::Texture characterSpriteSheet;

	MainChar mainChar;
	Grid grid;
	Snek snek;
};