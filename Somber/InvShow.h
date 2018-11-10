#pragma once

#include "EngineX/EngineX.h"

#define DEFAULT_INV_LOC_X -2e6
#define DEFAULT_INV_LOC_Y 2e6

class InvShow
{
public:
	InvShow();
	~InvShow();

	void loadRes();
	void Init(Engine* game);
	void update();
	void draw(sf::RenderWindow* app);

	static inline Point getDefaultLoc() { return { DEFAULT_INV_LOC_X, DEFAULT_INV_LOC_Y }; }

private:
	sf::Texture backTex;
	sf::Sprite back;
	sf::Font font;

	std::map <std::string, sf::Texture> iconTex;
	std::map <std::string, sf::Sprite> icon;
	std::map <std::string, sf::Text> iconNum;
	std::map <std::string, bool> iconActive;
	std::map <std::string, sf::RectangleShape> iconRect;

	Engine* game;
};

