#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stack>
#include <queue>

class Scene;

class Engine
{
public:
	Engine() {}
	Engine(sf::RenderWindow* app);
	~Engine();

	sf::RenderWindow* app;
	sf::View* gameView;
	double width;
	double height;

	void Init(sf::RenderWindow* app);
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

