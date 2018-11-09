#pragma once

/*
	Textbox containing the instruction and player interaction
*/

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "EngineX/EngineX.h"

class TextBox
{
public:
	TextBox();
	~TextBox();

	void Init(Engine* game, const sf::Font& font);

	void handleEvent(sf::Event* event);
	void draw();

	tgui::TextBox::Ptr box;

private:
	tgui::Gui gui;
	bool once = false;
};

