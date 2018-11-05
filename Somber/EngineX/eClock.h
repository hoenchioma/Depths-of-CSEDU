#pragma once

/*
	Similar to sf::Clock with added functionality of pausing
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class eClock
{
private:
	sf::Clock _obj;
	sf::Time _ofSet = sf::Time::Zero;

public:
	eClock() :_obj(), isPaused(false) {}
	~eClock() {}

	bool isPaused;

	sf::Time restart() 
	{
		sf::Time temp = _ofSet + _obj.restart();
		_ofSet = sf::Time::Zero;
		return temp;
	}
	sf::Time getElapsedTime() const 
	{
		if (isPaused) return _ofSet;
		return _ofSet + _obj.getElapsedTime(); 
	}
	sf::Time pause()
	{
		if (!isPaused)
		{
			isPaused = true;
			sf::Time temp = _obj.restart();
			_ofSet += temp;
			return _ofSet;
		}
		else
		{
			return _ofSet;
		}
	}
	sf::Time resume()
	{
		if (isPaused)
		{
			isPaused = false;
			_obj.restart();
			return _ofSet;
		}
		else return this->getElapsedTime();
	}
};
