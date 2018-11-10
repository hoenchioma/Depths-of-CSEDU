#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EngineX/Scene.h"
#include "EngineX/Anisprite.h"


#include "MainChar.h"
#include "Chair.h"
#include "EngineX/eClock.h"

#include <fstream>

class Room1 : public Scene
{
public:
	~Room1() { this->Cleanup(); }

	void LoadRes();
	void Init(Engine* game);
	void Cleanup();

	void Pause();
	void Resume();
	void togglePause();

	void HandleEvents(Engine* game, sf::Event* event);
	void Update(Engine* game, double dt);
	void Draw(sf::RenderWindow* app);

	static Room1* getInstance()
	{
		static Room1 inst;
		return &inst;
	}

private:
	Room1() {}
	Room1(Room1 const&) = delete;
	void operator= (Room1 const&) = delete;
	bool pause = false;
	long long int Score;
	
	//sf::Texture playerTexture;
	Texture tableTexture;
	Texture computerTexture;
	Texture floorTexture;
	Sprite table;
	Sprite computer;
	Sprite floor;
//////variables
	int windowWidth;
	int windowHeight;
	int i,j;
	int chairBeginX;
	int chairBeginY;
	int chairDis;
	Chairs chair[7][7];



	// Declare variables here
};

