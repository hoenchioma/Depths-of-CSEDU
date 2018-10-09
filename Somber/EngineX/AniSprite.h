#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class AniSprite
{
public:
	AniSprite() : _obj(), _clock() {}
	AniSprite(const sf::Texture& tex, float delay) : _obj(tex), _clock(), _delay(delay) {}

	static enum dir { horizontal, vertical };
	bool play = true;

	void setSpriteSheet(const sf::Texture& tex);
	//add rect containing containing frame
	void addFrame(sf::IntRect rect);

	//add the whole animation sequence
	//this method overwrites earlier frames
	void addSheet(dir direc, int width, int height, int in_x = 0, int in_y = 0);
	//default frame shown when paused
	void setDefault(sf::IntRect rect);

	void setDelay(float delay) { _delay = delay; }
	void pause() { play = false; }
	void resume() { play = true; }

	//overloads for normal sprite methods
	sf::Vector2f getSize() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const { _obj.getPosition(); }
	void setScale(float x, float y) { _obj.setScale(x, y); }
	void setScale(sf::Vector2f vec) { _obj.setScale(vec); }
	void move(float x, float y) { _obj.move(x, y); }
	void move(sf::Vector2f vec) { _obj.move(vec); }
	void setPosition(float x, float y) { _obj.setPosition(x, y); }
	void setPosition(sf::Vector2f vec) { _obj.setPosition(vec); }
	void setOrigin(float x, float y) { _obj.setOrigin(x, y); }
	void setOrigin(sf::Vector2f vec) { _obj.setOrigin(vec); }

	void drawTo(sf::RenderWindow* app);

	~AniSprite() {}

private:
	sf::Sprite _obj;
	sf::Clock _clock;

	float _delay = 0.1;
	std::vector<sf::IntRect> _frames;
	sf::IntRect _default;
	size_t _currentIndex = 0;

	bool _defaultSet = false;
};


