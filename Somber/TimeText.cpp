#include "pch.h"
#include "TimeText.h"

#include "EngineX/CompResolve.h"


TimeText::TimeText()
{
}


TimeText::~TimeText()
{
}

void TimeText::resLoad()
{
	loadFromFile(font, "res/Font/unispace bd.ttf");
}

void TimeText::Init(Engine* game)
{
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	pos = Point(game->width - 150, 0);

	this->game = game;

	time.restart();
}

void TimeText::update()
{
	Point corner(
		game->gameView.getCenter().x - game->width / 2.0,
		game->gameView.getCenter().y - game->height / 2.0
	);
	text.setPosition(corner + pos);

	int totalSecs = time.getElapsedTime().asSeconds();
	int mins = totalSecs / 60;
	int secs = totalSecs % 60;

	sprintf(str, "TIME: %02d:%02d", mins, secs);
	text.setString(str);
}

void TimeText::drawTo(sf::RenderWindow * app)
{
	app->draw(text);
}
