#pragma once

/*
	The menu shown after dying in a level
	shows the options of retrying and exiting
*/

#include <TGUI/TGUI.hpp>

#include "EngineX/EngineX.h"

class RestartMenu
{
public:
	RestartMenu();
	~RestartMenu();

	void Init(Engine* game, Scene * scene, const sf::Font& font);
	void handleEvent(sf::Event* event);
	void draw(sf::RenderWindow* app);
	inline void turnOn() { on = true; }
	inline void turnOff() { on = false; }

private:
	tgui::Gui gui;

	bool on = false;
	bool once = false;
};

