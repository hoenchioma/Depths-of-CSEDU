#include "Room1.h"

#include "EngineX/Utility.h"

#include <iostream>

using namespace sf;
using namespace std;

void Room1::LoadRes()
{
	floorTexture.loadFromFile("res/floor_back.png");////////////load files
	tableTexture.loadFromFile("res/table.png");
	computerTexture.loadFromFile("res/computerTable.png");
}

void Room1::Init(Engine* game)
{
	windowWidth=670;
	windowHeight = 720;
	chairBeginX = 60;
	chairBeginY = 45;
	chairDis = 85;
	for (i = 0; i < 7; i++)
		for (j = 0; j < 7;j++) chair[i][j].object.setPosition(chairBeginX + i * chairDis, chairBeginY + j * chairDis);
	
	floor.setTexture(floorTexture);
	table.setTexture(tableTexture);
	computer.setTexture(computerTexture);
	table.setScale(.5, .5);
	computer.setScale(.15, .18);
	table.setPosition((windowWidth / 2) - 75, windowHeight - 70);
	computer.setPosition((windowWidth / 2)+60, windowHeight - 80);
	
	//Init
}

void Room1::Cleanup()
{
	
}

void Room1::Pause()
{
	//player.running = false;
	pause = true;

	// this function is going to be called when the game is paused
}

void Room1::Resume()
{
	pause = false;

	// this function is going to be called when the game is resumed
}

void Room1::togglePause()
{
	if (this->pause) Resume();
	else Pause();
}

void Room1::HandleEvents(Engine * game, Event * event)
{
	// handle events here (keyboard/ mouse)

	if (event->type == Event::EventType::KeyPressed)
	{
		switch (event->key.code)
		{
		case Keyboard::Escape:
			togglePause();
			break;
		default:
			break;
		}
	}
}

void Room1::Update(Engine * game, double dt)
{
	if (!pause)
	{

	}
}


void Room1::Draw(RenderWindow * app)
{
	app->draw(floor);
	app->draw(table);
	app->draw(computer);
		for(i=0;i<7;i++) for(j=0;j<7;j++) app->draw(chair[i][j].object);
	
};