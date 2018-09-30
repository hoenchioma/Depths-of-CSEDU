#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <ctime>
using namespace std;
using namespace sf;

int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(700, 300), "Hello SFML");
	Event event;
	Text text;
	Font font;
	
	font.loadFromFile("28 Days Later.ttf");
	text.setString("Hello World");
	text.setFont(font);
	text.setCharacterSize(100);

	while (window.isOpen())
	{	
		while (window.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
			{
				window.close();
			}
		}
		window.clear();

		window.draw(text);

		window.display();
	}
	return 0;
}