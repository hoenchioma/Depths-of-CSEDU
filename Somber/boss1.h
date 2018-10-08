#pragma once

#include "EngineX/Scene.h"
#include "EngineX/AniSprite.h"
#include "mainChar.h"

class boss1 : public Scene
{
public:
	~boss1() { this->Cleanup(); }

	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static boss1* getInstance()
	{
		static boss1 inst;
		return &inst;
	}

private:
	boss1() {}
	boss1(boss1 const&) = delete;
	void operator= (boss1 const&) = delete;
	bool pause = false;

	// Declare variables here
};

