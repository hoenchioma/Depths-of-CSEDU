#include <iostream>
#include "Engine.h"
#include "Scene.h"

Engine::Engine(sf::RenderWindow * app, double gameWidth, double gameHeight)
{
	Init(app, gameWidth, gameHeight);
}

Engine::~Engine()
{
	Cleanup();
}

void Engine::Init(sf::RenderWindow * app, double gameWidth, double gameHeight)
{
	this->app = app; // do not remove "this->"
	this->fullWidth = app->getSize().x;
	this->fullHeight = app->getSize().y;
	this->width = gameWidth;
	this->height = gameHeight;

	// set game view
	gameView.reset(sf::FloatRect(0, 0, gameWidth, gameHeight));
	//gameView.setCenter(sf::gameWidth / 2.f, gameHeight / 2.f);
	gameView.setViewport(sf::FloatRect(0.f, 0.f, 0.8f, 0.8f));

	// set textbox view
	textBox.setViewport(sf::FloatRect(0.f, 0.8f, 0.8f, 0.2f));

	// set mini map view
	miniMap.setViewport(sf::FloatRect(0.8f, 0.8f, 0.2f, 0.2f));

	// set inventory view
	inventory.setViewport(sf::FloatRect(0.8f, 0.f, 0.2f, 0.8f));

	// set the fullscreen view
	fullScreen.reset(sf::FloatRect(0, 0, fullWidth, fullHeight));
	fullScreen.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
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
	{
		if (!_scenes.top()->_fullScreen)
		{
			app->setView(gameView);
			_scenes.top()->Draw(app);

			// only draw them if their respective flags are set
			if (textBoxOn)
			{
				app->setView(textBox);
				_scenes.top()->Draw(app);
			}
			if (miniMapOn)
			{
				app->setView(miniMap);
				_scenes.top()->Draw(app);
			}
			if (inventoryOn)
			{
				app->setView(inventory);
				_scenes.top()->Draw(app);
			}
		}
		else // if fullScreen flag is set load the fullscreen view
		{
			//std::cout << "mew" << std::endl;
			app->setView(fullScreen);
			_scenes.top()->Draw(app);
		}
	}
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
	if (!_scenes.top()->_resourceLoaded)
	{
		// time the resource loading process (only in debug)
#ifdef _DEBUG
		sf::Clock timer;
#endif // _DEBUG
		_scenes.top()->LoadRes();
#ifdef _DEBUG
		std::cerr << "Resources Loaded in " << timer.getElapsedTime().asMilliseconds() << "ms" << std::endl;
#endif // _DEBUG

		_scenes.top()->_resourceLoaded = true;
	}

	// initializes the scene
	if (_scenes.top()->_immortal)
	{
		if (!_scenes.top()->_loadedOnce)
			_scenes.top()->Init(this);
	}
	else _scenes.top()->Init(this);

	_scenes.top()->_loadedOnce = true;

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
	if (!_scenes.top()->_resourceLoaded)
	{
		// time the resource loading process (only in debug)
#ifdef _DEBUG
		sf::Clock timer;
#endif // _DEBUG
		_scenes.top()->LoadRes();
#ifdef _DEBUG
		std::cerr << "Resources Loaded in " << timer.getElapsedTime().asMilliseconds() << "ms" << std::endl;
#endif // _DEBUG

		_scenes.top()->_resourceLoaded = true;
	}
	// initializes the scene
	if (_scenes.top()->_immortal)
	{
		if (!_scenes.top()->_loadedOnce)
			_scenes.top()->Init(this);
	}
	else _scenes.top()->Init(this);

	_scenes.top()->_loadedOnce = true;

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
