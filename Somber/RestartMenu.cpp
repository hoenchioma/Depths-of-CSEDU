#include "pch.h"
#include "RestartMenu.h"

#include <iostream>

using namespace sf;


RestartMenu::RestartMenu()
{
}


RestartMenu::~RestartMenu()
{
}

void RestartMenu::Init(Engine * game, Scene * scene, const sf::Font& font)
{
	if (!once)
	{
		gui.setTarget(*game->app);
		tgui::Theme theme{ "extra/tgui_themes/BabyBlue.txt" };
		tgui::Theme theme2{ "extra/tgui_themes/Custom.txt" };

		auto back = tgui::Picture::create("res/back_darken.png");
		back->setPosition(0, 0);
		gui.add(back);

		auto retryButton = tgui::Button::create();
		retryButton->setSize(120, 70);
		retryButton->setPosition(
			game->fullWidth / 2.0 + 40, 
			game->fullHeight / 2.0 - retryButton->getSize().y / 2.0
		);
		retryButton->setText("Retry");
		retryButton->setInheritedFont(font);
		retryButton->setRenderer(theme.getRenderer("Button"));
		retryButton->connect("Pressed", [=]() {
			scene->reset(game); 
			scene->Resume();
			//this->turnOff();
		});
		gui.add(retryButton);

		auto exitButton = tgui::Button::create();
		exitButton->setSize(120, 70);
		exitButton->setPosition(
			game->fullWidth / 2.0 - 40 - exitButton->getSize().x, 
			game->fullHeight / 2.0 - exitButton->getSize().y / 2.0
		);
		exitButton->setText("Exit");
		exitButton->setInheritedFont(font);
		exitButton->setRenderer(theme.getRenderer("Button"));
		exitButton->connect("Pressed", [=]() {
			scene->popScene(game); 
			scene->Resume();
			//this->turnOff();
		});
		gui.add(exitButton);

		auto label = tgui::Label::create();
		label->setText("Oh no! You died. Wanna try again?");
		label->setTextSize(14);
		label->setInheritedFont(font);
		label->setPosition(
			game->fullWidth / 2.0 - label->getSize().x / 2.0,
			game->fullHeight / 2.0 - label->getSize().y / 2.0 - 90
		);
		label->setRenderer(theme2.getRenderer("label"));
		gui.add(label);

		once = true;
	}
}

void RestartMenu::handleEvent(sf::Event * event)
{
	if (on) gui.handleEvent(*event);
}

void RestartMenu::draw(sf::RenderWindow * app)
{
	if (on) gui.draw();
}
