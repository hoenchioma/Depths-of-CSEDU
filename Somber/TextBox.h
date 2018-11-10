#pragma once

/*
	Textbox containing the instruction and player interaction
*/

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <queue>

#include "EngineX/EngineX.h"

#define DEFAULT_DELAY 0.05

class TextBox
{
public:
	TextBox();
	~TextBox();

	void Init(Engine* game, const sf::Font& font);

	void handleEvent(sf::Event* event);
	void update();
	void draw();

	// append the string to the current text
	void addText(std::string str);
	// add the text but each letter at a certain delay
	void addTextTyped(std::string str);
	// replace the current text
	void setText(std::string str);

	inline void turnOn() { on = true; }
	inline void turnOff() { on = false; }

	tgui::TextBox::Ptr box;

	float delay = DEFAULT_DELAY;
	eClock time;

private:
	tgui::Gui gui;
	bool once = false;

	std::queue <char> textQ;

	bool on = true;
};

