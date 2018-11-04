#pragma once

#include "Engine.h"

class Scene
{
public:
	Scene() {}
	~Scene() {}

	bool _immortal = false; // immortal scenes still get cleaned on pop
	bool _fullScreen = false; // if the scene is a menu, gameView will take fullscreen
	
	bool _resourceLoaded = false;
	bool _loadedOnce = false;

	virtual void LoadRes() = 0;
	virtual void Init(Engine* game) = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(Engine* game, sf::Event* event) = 0;
	virtual void Update(Engine* game, double dt) = 0;
	virtual void Draw(sf::RenderWindow* app) = 0;

	void changeScene(Engine* game, Scene* scene)
	{
		game->changeScene(scene);
	}
	void pushScene(Engine* game, Scene* scene)
	{
		game->pushScene(scene);
	}
	void popScene(Engine* game)
	{
		game->popScene();
	}
	void reset(Engine* game)
	{
		game->popScene();
		game->pushScene(this);
	}
};

