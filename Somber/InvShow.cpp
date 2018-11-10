#include "pch.h"
#include "InvShow.h"

std::map <std::string, Point> iconLoc = 
{
	{"speed",		{ 38, 256}},
	{"invincible",	{118, 256}},
	{"healthBoost",	{198, 256}},
	{"bandage",		{278, 256}},
	{"reLife",		{ 38, 329}},
	{"timeFreeze",	{118, 329}},
	{"phase",		{198, 329}},
	//{{278, 329}},
	//{"keys",		{ 38, 720}}
};


InvShow::InvShow()
{
}


InvShow::~InvShow()
{
}

void InvShow::loadRes()
{
	loadFromFile(backTex, "res/Inventory-384x864.png");
	for (const auto& i : iconLoc)
	{
		iconTex[i.first] = sf::Texture();
		iconTex[i.first].loadFromFile("res/" + i.first + ".png");
	}
	loadFromFile(font, "res/Font/unispace bd.ttf");
}

void InvShow::Init(Engine * game)
{
	this->game = game;
	
	back.setTexture(backTex);
	back.setPosition(getDefaultLoc());

	sf::Text temp;
	temp.setFont(font);
	temp.setFillColor(sf::Color::White);
	temp.setCharacterSize(15);

	for (const auto& i : iconTex)
	{
		icon[i.first].setTexture(i.second);
		icon[i.first].setPosition(getDefaultLoc() + iconLoc[i.first]);

		temp.setPosition(getDefaultLoc() + iconLoc[i.first] + Point(63, 0));
		iconNum.insert({ i.first, temp });

		iconRect[i.first] = sf::RectangleShape(sf::Vector2f(INV_CELL_SIZE_X, INV_CELL_SIZE_Y));
		iconRect[i.first].setPosition(getDefaultLoc() + iconLoc[i.first]);
		iconRect[i.first].setFillColor(sf::Color::Green);
	}
}

void InvShow::update()
{
	for (auto& i : icon)
	{
		if (INVI(i.first) == 0)
		{
			i.second.setColor(sf::Color(255, 255, 255, 0));
			iconNum[i.first].setFillColor(sf::Color(255, 255, 255, 0));
		}
		else
		{
			i.second.setColor(sf::Color(255, 255, 255, 255));
			iconNum[i.first].setFillColor(sf::Color(255, 255, 255, 255));
		}

		iconNum[i.first].setString(std::to_string(INVI(i.first)));

		if (!iconActive[i.first]) 
			iconRect[i.first].setSize(sf::Vector2f(0, INV_CELL_SIZE_Y));
	}
}

void InvShow::draw(sf::RenderWindow * app)
{
	app->draw(back);
	for (const auto& i : icon)		app->draw(i.second);
	for (const auto& i : iconRect)	app->draw(i.second);
	for (const auto& i : iconNum)	app->draw(i.second);
}

void InvShow::setProgress(const std::string str, float prog)
{
	iconRect[str].setSize(sf::Vector2f(prog * INV_CELL_SIZE_X, INV_CELL_SIZE_Y));
}
