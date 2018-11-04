#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EngineX/Engine.h"
#include "EngineX/Scene.h"

class Boss4 : public Scene
{
public:
	~Boss4() { this->Cleanup(); }

	void LoadRes();
	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static Boss4* getInstance()
	{
		static Boss4 inst;
		return &inst;
	}

private:
	Boss4() {}
	Boss4(Boss4 const&) = delete;
	void operator= (Boss4 const&) = delete;
	bool pause = false;
	
	// declare variables here
};

