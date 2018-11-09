#include "pch.h"
#include "TextBox.h"


TextBox::TextBox()
{
}


TextBox::~TextBox()
{
}

void TextBox::Init(Engine* game, const sf::Font& font)
{
	if (!once)
	{
		tgui::Theme theme{ "extra/tgui_themes/Custom.txt" };
		tgui::Theme theme2{ "extra/tgui_themes/Black.txt" };
		gui.setTarget(*game->app);

		// the size and position to draw the text box
		sf::Vector2f pos(0, game->fullHeight * 0.8);
		sf::Vector2f size(game->fullWidth * 0.8, game->fullHeight * 0.2);

		box = tgui::TextBox::create();
		box->setPosition(pos);
		box->setSize(size);

		box->setTextSize(15);
		box->setText("Hello!!");
		box->setEnabled(false);
		box->setInheritedFont(font);

		box->setRenderer(theme.getRenderer("TextBox"));

		gui.add(box);

		/*tgui::Button::Ptr button = tgui::Button::create();
		button->setPosition("50%", "50%");
		button->setSize(200, 100);

		button->setText("Oooh Button");
		button->setTextSize(20);

		gui.add(button);*/

		once = true;
	}
}

void TextBox::handleEvent(sf::Event * event)
{
	gui.handleEvent(*event);
}

void TextBox::draw()
{
	gui.draw();
}
