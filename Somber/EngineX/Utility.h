#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>

static enum Direction { LEFT, RIGHT, UP, DOWN };

const Direction DirectionArr[4] = { LEFT, RIGHT, UP, DOWN };

const std::map <sf::Keyboard::Key, Direction> KeyMap =
{
	{sf::Keyboard::Left, LEFT},
	{sf::Keyboard::Right, RIGHT},
	{sf::Keyboard::Up, UP},
	{sf::Keyboard::Down, DOWN}
};

const sf::Keyboard::Key KeyArr[4] =
{
	sf::Keyboard::Left,
	sf::Keyboard::Right,
	sf::Keyboard::Up,
	sf::Keyboard::Down,
};