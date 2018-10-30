#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "EngineX/Scene.h"

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
};