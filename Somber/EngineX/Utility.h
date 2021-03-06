#pragma once

/*
	header with usefull utlity functions
*/

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
// #include <Utility>

enum Direction { LEFT, RIGHT, UP, DOWN };

const Direction DirectionArr[4] = { LEFT, RIGHT, UP, DOWN };

const std::pair<Direction, Direction> DiagArr[4] = 
{
	{LEFT, UP},
	{LEFT, DOWN},
	{RIGHT, UP},
	{RIGHT, DOWN}
};

const std::unordered_map <sf::Keyboard::Key, Direction> KeyMap =
{
	{sf::Keyboard::Left, LEFT},
	{sf::Keyboard::Right, RIGHT},
	{sf::Keyboard::Up, UP},
	{sf::Keyboard::Down, DOWN}
};

const std::unordered_map <Direction, sf::Keyboard::Key> revKeyMap =
{
	{LEFT, sf::Keyboard::Left},
	{RIGHT, sf::Keyboard::Right},
	{UP, sf::Keyboard::Up},
	{DOWN, sf::Keyboard::Down}
};

const sf::Keyboard::Key KeyArr[4] =
{
	sf::Keyboard::Left,
	sf::Keyboard::Right,
	sf::Keyboard::Up,
	sf::Keyboard::Down,
};

// load from file with failure message
template <class T>
void loadFromFile(T& res, const std::string& fileName)
{
	if (!res.loadFromFile(fileName))
	{
		std::cerr << "can't load " << fileName << std::endl;
	}
}

// math variables
const float invSqrtTwo = 0.7071067811865475f;

// view centering
// gameSize is the size of the actual game map
// pos is the position to centre the camera to
inline void centreView(sf::View& view, sf::Vector2f pos, sf::Vector2f gameSize)
{
	if (pos.x >= view.getSize().x / 2.0 and pos.x + view.getSize().x / 2.0 <= gameSize.x)
		view.setCenter(pos.x, view.getCenter().y);
	if (pos.y >= view.getSize().y / 2.0 and pos.y + view.getSize().y / 2.0 <= gameSize.y)
		view.setCenter(view.getCenter().x, pos.y);
}
inline void centreView(sf::View& view, sf::Vector2f pos, sf::FloatRect gameSizeRect)
{
	centreView(view, pos, sf::Vector2f(gameSizeRect.width, gameSizeRect.height));
}

// resets the camera to the upper left corner
// use this when initializing scenes
inline void resetView(sf::View& view)
{
	view.setCenter(view.getSize().x / 2.0, view.getSize().y / 2.0);
}

// centres view even when the character is at the edge of the screen at start
inline void smartCentre(sf::View& view, sf::Vector2f pos, sf::Vector2f screenSize, sf::Vector2f canvasSize)
{
	sf::Vector2f temp = pos;
	if (temp.x < screenSize.x / 2.0) temp.x = screenSize.x / 2.0;
	if (temp.y < screenSize.y / 2.0) temp.y = screenSize.y / 2.0;
	if (temp.x > canvasSize.x - screenSize.x / 2.0) temp.x = canvasSize.x - screenSize.x / 2.0;
	if (temp.y > canvasSize.y - screenSize.y / 2.0) temp.y = canvasSize.y - screenSize.y / 2.0;
	view.setCenter(temp);
}