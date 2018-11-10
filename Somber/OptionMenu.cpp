#include "OptionMenu.h"

#include "DefaultInv.h"
#include "MainMenu.h"
#include "Floor1.h"
#include "Boss3.h"

using namespace sf;
using namespace std;


void OptionMenu::LoadRes()
{
	loadFromFile(SoundButtonOn,"res/Main Menu/Option/SoundButtonOn.png");
	loadFromFile(SoundButtonOff,"res/Main Menu/Option/SoundButtonOff.png");
	//loadFromFile(FullscreenButtonOn,"res/Main Menu/Option/FullscreenButtonOn.png");
	//loadFromFile(FullscreenButtonAcOff,"res/Main Menu/Option/FullscreenButtonOff.png");
	loadFromFile(BackButton,"res/Main Menu/Option/BackButton.png");
	loadFromFile(BackButtonAc,"res/Main Menu/Option/BackButtonAc.png");
	loadFromFile(Background,"res/Main Menu/Background.png");
	// load resources
}

void OptionMenu::Init(Engine* game)
{
	game->fullScreen.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
	_fullScreen = true;


		
	soundButton.Init(&SoundButtonOn,&SoundButtonOff, soundX,soundY);
	//fullscreenButton.Init(&FullscreenButtonAc, &FullscreenButton, fullscreenX, fullscreenY);
	backButton.Init(&BackButtonAc, &BackButton, backX, backY);
	background.setTexture(Background);
	soundButton.object.setPosition(soundX,soundY);
	//fullscreenButton.object.setPosition(fullscreenX,fullscreenY);
	// initialize variables
}

void OptionMenu::Cleanup()
{
}

void OptionMenu::Pause()
{
	pause = true;
	// this function is going to be called when the game is paused
}

void OptionMenu::Resume()
{
	pause = false;
	// this function is going to be called when the game is resumed
}

void OptionMenu::togglePause()
{
	if (this->pause) Resume();
	else Pause();
}

void OptionMenu::HandleEvents(Engine * game, Event * event)
{
	sf::Vector2f mouseCor = game->app->mapPixelToCoords(mouse.getPosition(*game->app));
	if (mouseCor.x >= soundX && mouseCor.x <= soundX+158 && mouseCor.y >= soundY && mouseCor.y <= soundY+50)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			soundFlag = soundFlag ^ 1;
		}/////////////////////////////////sound button
	}
	
	
	if (mouseCor.x >= backX && mouseCor.x <= backX+84 && mouseCor.y >= backY && mouseCor.y <= backY+50)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			pushScene(game, MainMenu::getInstance());
		}////////////////////////////////////////back button
		backButton.objectAc.setPosition(backX, backY);
	}
	else backButton.objectAc.setPosition(negPos, negPos);
	// handle events here (keyboard/ mouse)

}

void OptionMenu::Update(Engine * game, double dt)
{
	if (!pause)
	{
		if( soundFlag==0 ) soundButton.object.setTexture(SoundButtonOff); //////////////sound variable
		else soundButton.object.setTexture(SoundButtonOn);
		//if(_fullScreen==true) fullscreenButton.object.setTexture(FullscreenButtonOn);/////////////fullscreen variable
		//else fullscreenButton.object.setTexture(FullscreenButtonOff);
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

void OptionMenu::Draw(RenderWindow * app)
{
	app->draw(background);
	app->draw(soundButton.object);
	//app->draw(fullscreenButton.object);
	app->draw(backButton.object);
	app->draw(backButton.objectAc);
	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
