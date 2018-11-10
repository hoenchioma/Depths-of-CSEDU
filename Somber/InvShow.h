#pragma once

#include "EngineX/EngineX.h"

#define DEFAULT_INV_LOC_X -2e6
#define DEFAULT_INV_LOC_Y 2e6

#define INV_CELL_SIZE_X 69
#define INV_CELL_SIZE_Y 63

class InvShow
{
public:
	InvShow();
	~InvShow();

	void loadRes();
	void Init(Engine* game);
	void update();
	void draw(sf::RenderWindow* app);

	inline void activate(const std::string str) { iconActive[str] = true; }
	inline void deActivate(const std::string str) { iconActive[str] = false; }

	void setProgress(const std::string str, float prog);

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

