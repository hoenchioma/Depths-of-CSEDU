#include "MainMenu.h"

#include "DefaultInv.h"
#include "Floor1.h"
#include "OptionMenu.h"
#include "Boss3.h"

#include <fstream>

using namespace sf;
using namespace std;


void MainMenu::LoadRes()
{
	loadFromFile(PlayButton,"res/Main Menu/PlayButton.png");
	loadFromFile(PlayButtonAc,"res/Main Menu/PlayButtonAc.png");
	loadFromFile(ContinueButtonAvail,"res/Main Menu/ContinueButtonAvail.png");
	loadFromFile(ContinueButtonAvailAc,"res/Main Menu/ContinueButtonAvailAc.png");
	loadFromFile(ContinueButtonUnavail,"res/Main Menu/ContinueButtonUnavail.png");
	loadFromFile(OptionButton,"res/Main Menu/OptionButton.png");
	loadFromFile(OptionButtonAc,"res/Main Menu/OptionButtonAc.png");
	loadFromFile(QuitButton,"res/Main Menu/QuitButton.png");
	loadFromFile(QuitButtonAc,"res/Main Menu/QuitButtonAc.png");
	loadFromFile(Background,"res/Main Menu/Background.png");
	mainMenuSound.openFromFile("res/Main Menu/Sounds/mainMenuAudio.wav");
	// load resources
}

void MainMenu::Init(Engine* game)
{
	game->fullScreen.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
	_fullScreen = true;

	if (ifstream("save/inv.txt")) fileCont = true;												//checks for save files if available

	continueButton.Init(&ContinueButtonAvailAc, &ContinueButtonAvail, continueX, continueY);
	if (fileCont)																				//sets continue button active textures if fileCount flag is active 
	{
		continueButton.object.setTexture(ContinueButtonAvail);
		continueButton.objectAc.setTexture(ContinueButtonAvailAc);
	}
	else
	{																							//sets continue button inactive textures if fileCount flag is inactive 
		continueButton.object.setTexture(ContinueButtonUnavail);
		continueButton.objectAc.setTexture(ContinueButtonUnavail);
	}	
	playButton.Init(&PlayButtonAc,&PlayButton, playX,playY);										//sets button textures and positions
	optionButton.Init(&OptionButtonAc, &OptionButton, optionX, optionY);
	quitButton.Init(&QuitButtonAc, &QuitButton, quitX, quitY);
	background.setTexture(Background);
	mainMenuSound.setVolume(50);
	mainMenuSound.setLoop(true);
	mainMenuSound.play();
	// initialize variables
}

void MainMenu::Cleanup()
{
}

void MainMenu::Pause()
{
	pause = true;
	// this function is going to be called when the game is paused
}

void MainMenu::Resume()
{
	pause = false;
	// this function is going to be called when the game is resumed
}

void MainMenu::togglePause()
{
	if (this->pause) Resume();
	else Pause();
}

void MainMenu::HandleEvents(Engine * game, Event * event)
{
	sf::Vector2f mouseCor = game->app->mapPixelToCoords(mouse.getPosition(*game->app));
	if (mouseCor.x >= playX && mouseCor.x <= 680 && mouseCor.y >= playY && mouseCor.y <= 408)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			mainMenuSound.stop();
			makeDefault(game->inv);
			pushScene(game, Floor1::getInstance());
		}/////////////////////////////////play button
		playButton.objectAc.setPosition(playX, playY);
	}
	else playButton.objectAc.setPosition(negPos, negPos);
	if (fileCont && mouseCor.x >= continueX && mouseCor.x <= 719 && mouseCor.y >= continueY && mouseCor.y <= 458)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			mainMenuSound.stop();
			// if file is corrupt load default
			game->inv.loadFromFile("save/inv.txt");
			game->inv.saveToFile("save/test.txt");
			if (INVI("floor") == 0) pushScene(game, Floor1::getInstance());
		}
		continueButton.objectAc.setPosition(continueX, continueY);
	}
	else continueButton.objectAc.setPosition(negPos, negPos);
	if (mouseCor.x >= optionX && mouseCor.x <= 707 && mouseCor.y >= optionY && mouseCor.y <= 508)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			pushScene(game, OptionMenu::getInstance());
		}
		optionButton.objectAc.setPosition(optionX, optionY);
	}
	else optionButton.objectAc.setPosition(negPos, negPos);
	if (mouseCor.x >= quitX && mouseCor.x <= 680 && mouseCor.y >= quitY && mouseCor.y <= 558)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			game->close();
		}////////////////////////////////////////quit game
		quitButton.objectAc.setPosition(quitX, quitY);
	}
	else quitButton.objectAc.setPosition(negPos, negPos);
	// handle events here (keyboard/ mouse)

	if (event->type == Event::EventType::KeyPressed && event->key.code == Keyboard::S)
		pushScene(game, Boss3::getInstance()), mainMenuSound.stop();
}

void MainMenu::Update(Engine * game, double dt)
{
	if (!pause)
	{
		if (backgroundScale < 1) scaleFlag = 0;
		if (backgroundScale > 1.05) scaleFlag = 1;
		if(scaleFlag==0)backgroundScale += .0001*dt*dtMul;
		else  backgroundScale -= .0001*dt*dtMul;
		background.setScale(backgroundScale,backgroundScale);
		// Key press & release handle
		// handle collision and other logic
		// update the sprites
		// use dt (interval between two frames) for framerate independent movement
	}
}

void MainMenu::Draw(RenderWindow * app)
{
	app->draw(background);
	app->draw(playButton.object);
	app->draw(playButton.objectAc);
	app->draw(continueButton.object);
	app->draw(continueButton.objectAc);
	app->draw(optionButton.object);
	app->draw(optionButton.objectAc);
	app->draw(quitButton.object);
	app->draw(quitButton.objectAc);
	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
