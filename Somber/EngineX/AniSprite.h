#pragma once

/*
	A animated sprite class
	capable of playing an array of textures on a loop
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "eClock.h"

class AniSprite
{
public:
	AniSprite() : _obj(), _clock() {}
	AniSprite(const sf::Texture& tex, float delay) : _obj(tex), _clock(), _delay(delay) {}

	enum dir { horizontal, vertical };
	bool play = true;

	void setSpriteSheet(const sf::Texture& tex);
	//add rect containing containing frame
	void addFrame(sf::IntRect rect);

	//add the whole animation sequence
	//this method overwrites earlier frames
	void addSheet(dir direc, int width, int height, int in_x = 0, int in_y = 0);
	// sets the default frame (shown when paused)
	void setDefault(sf::IntRect rect);

	inline void setDelay(float delay) { _delay = delay; }
	// pauses animation (shows default frame if set)
	inline void pause() { play = false; }
	// resumes animation
	inline void resume() { play = true; }

	// pauses animation (pauses the clock)
	inline void freeze() { _clock.pause(); }
	// resumes animation (resumes the clock)
	inline void unfreeze() { _clock.resume(); }

	// returns the actual size (considering all transformations)
	sf::Vector2f getSize() const;

	//overloads for normal sprite methods
	sf::FloatRect getGlobalBounds() const;
	sf::IntRect getTextureRect() const;
	inline sf::Vector2f getPosition() const			{ return _obj.getPosition(); }
	inline void setColor(const sf::Color& color)	{ _obj.setColor(color); }
	inline void setScale(float x, float y)			{ _obj.setScale(x, y); }
	inline void setScale(sf::Vector2f vec)			{ _obj.setScale(vec); }
	inline void move(float x, float y)				{ _obj.move(x, y); }
	inline void move(sf::Vector2f vec)				{ _obj.move(vec); }
	inline void setPosition(float x, float y)		{ _obj.setPosition(x, y); }
	inline void setPosition(sf::Vector2f vec)		{ _obj.setPosition(vec); }
	inline void setOrigin(float x, float y)			{ _obj.setOrigin(x, y); }
	inline void setOrigin(sf::Vector2f vec)			{ _obj.setOrigin(vec); }

	void drawTo(sf::RenderWindow* app);

	~AniSprite() {}

private:
	sf::Sprite _obj;
	eClock _clock;

	// delay at which each frame will be played
	float _delay = 0.1f;
	// vector containing the location of the frames in the sprite sheet
	std::vector<sf::IntRect> _frames;
	// the default frame (shown when paused)
	sf::IntRect _default;
	size_t _currentIndex = 0;

	bool _defaultSet = false;
};


