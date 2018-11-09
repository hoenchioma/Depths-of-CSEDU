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

	void addText(std::string str);
	void addTextTyped(std::string str);
	void setText(std::string str);

	tgui::TextBox::Ptr box;

	float delay = DEFAULT_DELAY;
	eClock time;

private:
	tgui::Gui gui;
	bool once = false;

	std::queue <char> textQ;
};

