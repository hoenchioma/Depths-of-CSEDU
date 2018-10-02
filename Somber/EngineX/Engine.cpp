#include "Engine.h"
#include "Scene.h"
#include <iostream>

Engine::Engine(sf::RenderWindow * app)
{
	this->Init(app);
}

Engine::~Engine()
{
	this->Cleanup();
}

void Engine::Init(sf::RenderWindow * app)
{
	this->app = app;
	this->width = app->getSize().x;
	this->height = app->getSize().y;
}

void Engine::Cleanup()
{
	while (!this->_scenes.empty())
	{
		this->_popScene();
	}
}

void Engine::Pause()
{
	this->_scenes.top()->Pause();
}

void Engine::Resume()
{
	this->_scenes.top()->Resume();
}

void Engine::HandleEvents(sf::Event* event)
{
	if (!_scenes.empty())
		this->_scenes.top()->HandleEvents(this, event);
}

void Engine::Update(double dt)
{
	if (!_scenes.empty())
		this->_scenes.top()->Update(this, dt);
}

void Engine::Draw()
{
	if (!_scenes.empty())
		this->_scenes.top()->Draw(this->app);
}

void Engine::_changeScene(Scene * newScene)
{
	if (!this->_scenes.empty())
	{
		this->_scenes.top()->Cleanup();
		this->_scenes.pop();
	}
	this->_scenes.push(newScene);
	this->_scenes.top()->Init(this);

#ifdef _DEBUG
	std::cerr << "changed state" << std::endl;
#endif // _DEBUG
}

void Engine::_pushScene(Scene * newScene)
{
	if (!this->_scenes.empty())
	{
		this->_scenes.top()->Pause();
	}
	this->_scenes.push(newScene);
	this->_scenes.top()->Init(this);

#ifdef _DEBUG
	std::cerr << "pushed state" << std::endl;
#endif // _DEBUG
}

void Engine::_popScene()
{
	if (!this->_scenes.empty())
	{
		this->_scenes.top()->Cleanup();
		this->_scenes.pop();
	}
	if (!this->_scenes.empty())
	{
		this->_scenes.top()->Resume();
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
		this->close();
	}
}
