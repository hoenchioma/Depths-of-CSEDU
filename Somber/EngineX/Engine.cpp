#include <iostream>
#include "Engine.h"
#include "Scene.h"

Engine::Engine(sf::RenderWindow * app)
{
	Init(app);
}

Engine::~Engine()
{
	Cleanup();
}

void Engine::Init(sf::RenderWindow * app)
{
	this->app = app; // do not remove "this->"
	this->width = app->getSize().x;
	this->height = app->getSize().y;
}

void Engine::Cleanup()
{
	while (!_scenes.empty())
	{
		_popScene();
	}
}

void Engine::Pause()
{
	_scenes.top()->Pause();
}

void Engine::Resume()
{
	_scenes.top()->Resume();
}

void Engine::HandleEvents(sf::Event* event)
{
	if (!_scenes.empty())
		_scenes.top()->HandleEvents(this, event);
}

void Engine::Update(double dt)
{
	if (!_scenes.empty())
		_scenes.top()->Update(this, dt);
}

void Engine::Draw()
{
	if (!_scenes.empty())
		_scenes.top()->Draw(app);
}

void Engine::_changeScene(Scene * newScene)
{
	if (!_scenes.empty())
	{
		_scenes.top()->Cleanup();
		_scenes.pop();
	}
	_scenes.push(newScene);

	// load resources only if it is the first time
	if (!_scenes.top()->resourceLoaded)
	{
		// time the resource loading process (only in debug)
#ifdef _DEBUG
		sf::Clock timer;
#endif // _DEBUG
		_scenes.top()->LoadRes();
#ifdef _DEBUG
		std::cerr << "Resources Loaded in " << timer.getElapsedTime().asMilliseconds() << "ms" << std::endl;
#endif // _DEBUG

		_scenes.top()->resourceLoaded = true;
	}

	// initializes the scene
	if (_scenes.top()->immortal)
	{
		if (!_scenes.top()->loadedOnce)
			_scenes.top()->Init(this);
	}
	else _scenes.top()->Init(this);

	_scenes.top()->loadedOnce = true;

#ifdef _DEBUG
	std::cerr << "changed state" << std::endl;
#endif // _DEBUG
}

void Engine::_pushScene(Scene * newScene)
{
	if (!_scenes.empty())
	{
		_scenes.top()->Pause();
	}
	_scenes.push(newScene);
	// load resources only if it is the first time
	if (!_scenes.top()->resourceLoaded)
	{
		// time the resource loading process (only in debug)
#ifdef _DEBUG
		sf::Clock timer;
#endif // _DEBUG
		_scenes.top()->LoadRes();
#ifdef _DEBUG
		std::cerr << "Resources Loaded in " << timer.getElapsedTime().asMilliseconds() << "ms" << std::endl;
#endif // _DEBUG

		_scenes.top()->resourceLoaded = true;
	}
	// initializes the scene
	if (_scenes.top()->immortal)
	{
		if (!_scenes.top()->loadedOnce)
			_scenes.top()->Init(this);
	}
	else _scenes.top()->Init(this);

	_scenes.top()->loadedOnce = true;

#ifdef _DEBUG
	std::cerr << "pushed state" << std::endl;
#endif // _DEBUG
}

void Engine::_popScene()
{
	if (!_scenes.empty())
	{
		_scenes.top()->Cleanup();
		_scenes.pop();
	}
	if (!_scenes.empty())
	{
		_scenes.top()->Resume();
	}

#ifdef _DEBUG
	std::cerr << "popped state" << std::endl;
#endif // _DEBUG
}

void Engine::changeScene(Scene * newScene)
{
	_sceneQ.push(newScene);
	_sceneControlQ.push(change);
}

void Engine::pushScene(Scene * newScene)
{
	_sceneQ.push(newScene);
	_sceneControlQ.push(push);
}

void Engine::popScene()
{
	_sceneQ.push(NULL);
	_sceneControlQ.push(pop);
}

void Engine::handleChange()
{
	while (!_sceneQ.empty())
	{
		switch (_sceneControlQ.front())
		{
		case change:
			_changeScene(_sceneQ.front());
			break;
		case push:
			_pushScene(_sceneQ.front());
			break;
		case pop:
			_popScene();
			break;
		default:
			break;
		}
		_sceneQ.pop();
		_sceneControlQ.pop();
	}

	// closes engine if stack is empty
	if (_scenes.empty())
	{
#ifdef _DEBUG
		std::cerr << "There were no scenes in the stack" << std::endl;
#endif // _DEBUG
		close();
	}
}
