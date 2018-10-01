#pragma once

#include "EngineX/Scene.h"

class test1: public Scene
{
public:
	~test1() { this->Cleanup(); }

	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static test1* getInstance()
	{
		static test1 inst;
		return &inst;
	}

private:
	test1() {}
	test1(test1 const&) = delete;
	void operator= (test1 const&) = delete;

	sf::RectangleShape box;
	double vel = 200;
};

