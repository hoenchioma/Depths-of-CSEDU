#pragma once

#include "EngineX/EngineX.h"

class TimeText
{
public:
	TimeText();
	~TimeText();

	eClock time;

	void resLoad();
	void Init(Engine* game);
	void update();
	void drawTo(sf::RenderWindow* app);

	inline int getTime() { return time.getElapsedTime().asSeconds(); }
	inline char* getStr() { return this->str; }

private:
	sf::Font font;
	sf::Text text;
	Point pos;

	char str[100];

	Engine* game;
};

