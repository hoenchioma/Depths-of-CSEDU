#include "PauseMenu.h"

#include "DefaultInv.h"



using namespace sf;
using namespace std;


void PauseMenu::LoadRes()
{
	loadFromFile(ResumeButton,"res/Main Menu/Pause/ResumeButton.png");
	loadFromFile(ResumeButtonAc,"res/Main Menu/Pause/ResumeButtonAc.png");
	loadFromFile(InvInfoButton,"res/Main Menu/Pause/InvInfoButton.png");
	loadFromFile(InvInfoButtonAc,"res/Main Menu/Pause/InvInfoButtonAc.png");
	//loadFromFile(SaveNQuitButtonUnavail,"res/Main Menu/ContinueButtonAvail.png");
	loadFromFile(SaveNQuitButton,"res/Main Menu/Pause/SaveNQuitButton.png");
	loadFromFile(SaveNQuitButtonAc,"res/Main Menu/Pause/SaveNQuitButtonAc.png");
	loadFromFile(SaveNQuitButtonUnavail,"res/Main Menu/Pause/SaveNQuitButtonUnavail.png");
	loadFromFile(QuitButton,"res/Main Menu/QuitButton.png");
	loadFromFile(QuitButtonAc,"res/Main Menu/QuitButtonAc.png");
	loadFromFile(Background,"res/Main Menu/Background.png");
	PauseMenuSound.openFromFile("res/Main Menu/Sounds/mainMenuAudio.wav");
	// load resources
}

void PauseMenu::Init(Engine* game)
{
	game->app->setMouseCursorVisible(true);
	
	game->fullScreen.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
	_fullScreen = true;
	levelAc = false;
	
	////////////////////////handle level active or not(by default not)

	saveNQuitButton.Init(&SaveNQuitButtonAc, &SaveNQuitButton, saveNQuitX, saveNQuitY);
	if (!levelAc)
	{
		saveNQuitButton.object.setTexture(SaveNQuitButton);
		saveNQuitButton.objectAc.setTexture(SaveNQuitButtonAc);
	}
	else
	{
		saveNQuitButton.object.setTexture(SaveNQuitButtonUnavail);
		saveNQuitButton.objectAc.setTexture(SaveNQuitButtonUnavail);
	}	
	resumeButton.Init(&ResumeButtonAc,&ResumeButton, resumeX,resumeY);
	invInfoButton.Init(&InvInfoButtonAc, &InvInfoButton, invInfoX, invInfoY);
	quitButton.Init(&QuitButtonAc, &QuitButton, quitX, quitY);
	background.setTexture(Background);
	PauseMenuSound.setVolume(50);
	PauseMenuSound.setLoop(true);
	PauseMenuSound.play();
	// initialize variables
}

void PauseMenu::Cleanup()
{
}

void PauseMenu::Pause()
{
	pause = true;
	// this function is going to be called when the game is paused
}

void PauseMenu::Resume()
{
	pause = false;
	// this function is going to be called when the game is resumed
}

void PauseMenu::togglePause()
{
	if (this->pause) Resume();
	else Pause();
}

void PauseMenu::HandleEvents(Engine * game, Event * event)
{
	sf::Vector2f mouseCor = game->app->mapPixelToCoords(mouse.getPosition(*game->app));
	if (mouseCor.x >= resumeX && mouseCor.x <= resumeX+125 && mouseCor.y >= resumeY && mouseCor.y <= resumeY+50)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			PauseMenuSound.stop();
			popScene(game);

		}/////////////////////////////////resume button
		resumeButton.objectAc.setPosition(resumeX, resumeY);
	}
	else resumeButton.objectAc.setPosition(negPos, negPos);
	if (!levelAc && mouseCor.x >= saveNQuitX && mouseCor.x <= saveNQuitX+232 && mouseCor.y >= saveNQuitY && mouseCor.y <= saveNQuitY+50)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			INVI("save") = 1;
			game->inv.saveToFile("save/inv.txt");
			game->close();
		}
		saveNQuitButton.objectAc.setPosition(saveNQuitX, saveNQuitY);
	
	}
	else
	{
		saveNQuitButton.objectAc.setPosition(negPos, negPos);
	}
	if (mouseCor.x >= invInfoX && mouseCor.x <= invInfoX+256 && mouseCor.y >= invInfoY && mouseCor.y <= invInfoY+50)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//////////////////////load inv file
		}
		invInfoButton.objectAc.setPosition(invInfoX, invInfoY);
	}
	else invInfoButton.objectAc.setPosition(negPos, negPos);
	if (mouseCor.x >= quitX && mouseCor.x <= quitX+80 && mouseCor.y >= quitY && mouseCor.y <= quitY+50)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			game->close();
		}////////////////////////////////////////quit game
		quitButton.objectAc.setPosition(quitX, quitY);
	}
	else quitButton.objectAc.setPosition(negPos, negPos);
	// handle events here (keyboard/ mouse)

}

void PauseMenu::Update(Engine * game, double dt)
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

void PauseMenu::Draw(RenderWindow * app)
{
	app->draw(background);
	app->draw(resumeButton.object);
	app->draw(resumeButton.objectAc);
	app->draw(saveNQuitButton.object);
	
	app->draw(invInfoButton.object);
	app->draw(invInfoButton.objectAc);
	app->draw(quitButton.object);
	app->draw(quitButton.objectAc);
	app->draw(saveNQuitButton.objectAc);
	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
