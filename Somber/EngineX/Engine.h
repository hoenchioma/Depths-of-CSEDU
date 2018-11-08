#pragma once

/*
	The class that handles all the states and their changes
	It also handles views for textbox, inventory and minimap
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>

#include <stack>
#include <queue>

class Scene;

class Engine
{
public:
	Engine() {}
	Engine(sf::RenderWindow * app, double gameWidth, double gameHeight);
	~Engine();

	sf::RenderWindow* app;
	double width;
	double height;
	double fullWidth;
	double fullHeight;

	// view management
	sf::View gameView;
	// reset the views before using them (viewport is already set)
	// the flags whether the view is drawn
	sf::View textBox;
	bool textBoxOn = false;
	sf::View inventory;
	bool inventoryOn = false;
	sf::View miniMap;
	bool miniMapOn = false;
	sf::View fullScreen;

	void Init(sf::RenderWindow * app, double gameWidth, double gameHeight);
	void Cleanup();

	void Pause();
	void Resume();

	//calls the present scene's version of the same functions
	void HandleEvents(sf::Event* event);
	void Update(double dt);
	void Draw();

	//queues control commands to be called by handleChange()
	void changeScene(Scene* newScene);
	void pushScene(Scene* newScene);
	void popScene();

	//called at the beginning of frame (loop iteration) to handle Scene change
	void handleChange();

	bool running() { return app->isOpen(); }
	void close() { app->close(); }

private:
	std::stack <Scene*> _scenes;

	enum StateControl { change, push, pop };
	std::queue <Scene*> _sceneQ;
	std::queue <StateControl> _sceneControlQ;

	//control functions called called by handleChange()
	void _changeScene(Scene* newScene);
	void _pushScene(Scene* newScene);
	void _popScene();
};

