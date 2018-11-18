#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Door
{
public:
	Door();
	~Door();

	enum state { OPEN, CLOSED };

	state DoorState = CLOSED;

	void Init(sf::Texture& tex);

	void setScale(sf::Vector2f vec) { obj.setScale(vec); }
	void setScale(float x, float y) { obj.setScale(x, y); }
	void setOrigin(sf::Vector2f vec) { obj.setOrigin(vec); }
	void setOrigin(float x, float y) { obj.setOrigin(x, y); }
	void setPosition(sf::Vector2f vec) { obj.setPosition(vec); }
	void setPosition(float x, float y) { obj.setPosition(x, y); }
	void setColor(const sf::Color color) { obj.setColor(color); }
	sf::Vector2f getPosition() const { return obj.getPosition(); }
	sf::FloatRect getGlobalBounds() const { return obj.getGlobalBounds(); }

	void open();
	void close();

	void drawTo(sf::RenderWindow* app);

private:
	sf::Sprite obj;
};

