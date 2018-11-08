#include "Boss1.h"

#include "EngineX/Utility.h"

#include <iostream>


using namespace sf;
using namespace std;


inline double centreDis(float X1, float Y1, float X2, float Y2)
{
	double  distance = sqrt(pow((X1 - X2), 2) + pow((Y1 - Y2), 2));
	return distance;
}


void Boss1::LoadRes()
{
	if (!tex.loadFromFile("res/running_1.png"))
	{
		cout << "can't load Sprite" << endl;
	}
	if (!fuseClosed.loadFromFile("res/fuseClosed.png"))
	{
		cout << "can't load texture fuseClosed" << endl;
	}
	if (!fuseOpened.loadFromFile("res/fuseOpened.png"))
	{
		cout << "can't load texture fuseOpened" << endl;
	}
	if (!heartFull.loadFromFile("res/heart_full.png"))
	{
		cout << "can't load full heart" << endl;
	}
	if (!heartHalf.loadFromFile("res/heart_half.png"))
	{
		cout << "can't load half heart" << endl;
	}
	if (!heartEmpty.loadFromFile("res/heart_empty.png"))
	{
		cout << "can't load empty heart" << endl;
	}
	if (!exitDim.loadFromFile("res/exitDim.png"))
	{
		cout << "can't load dim exit" << endl;
	}
	if (!exitLit.loadFromFile("res/exitLit.png"))
	{
		cout << "can't load lit exit" << endl;
	}
	font.loadFromFile("res/Font/unispace bd.ttf");
	Boss1ScoreFile.open("res/file/Boss1ScoreFile.txt", ios::in | ios::out);
	highestScoreTex.loadFromFile("res/HighScoreTag.png");
	scoreCardTex.loadFromFile("res/scoreCard.png");
	floorTexture.loadFromFile("res/floorExtended.png");
}

void Boss1::Init(Engine* game)
{
	resetView(game->gameView);
	_gameViewtemp = &game->gameView;
	Boss1ScoreFile >> topTime;
	player.Init(tex, 0.1f, 300);
	player.setScale(1.4f, 1.4f);
	player.setPosition(30, game->height - 130);
	player.setDirec(Direction::UP);
	floor.setTexture(floorTexture);
	lights[0].x = 0;
	lights[0].y = 0;
	lights[1].x = windowWidth;
	lights[1].y = 0;
	lights[2].x = windowWidth;
	lights[2].y = windowHeight;
	lights[3].x = 0;
	lights[3].y = windowHeight;
	lights[4].x = windowWidth / 2;
	lights[4].y = windowHeight / 2;
	lights[0].dirX = RIGHT;
	lights[0].dirY = DOWN;
	lights[1].dirX = LEFT;
	lights[1].dirY = DOWN;
	lights[2].dirX = LEFT;
	lights[2].dirY = UP;
	lights[3].dirX = RIGHT;
	lights[3].dirY = UP;
	lights[4].dirX = RIGHT;
	lights[4].dirY = DOWN;

	fuse[0].X = 50;
	fuse[0].Y = 50;
	fuse[1].X = rand() % (windowWidth - randLimitW) + 200;
	fuse[1].Y = fuseDis;
	fuse[2].X = windowWidth - fuseDis;
	fuse[2].Y = rand() % (windowHeight - randLimitH) + 200;
	fuse[3].X = rand() % (windowWidth - randLimitW) + 200;
	fuse[3].Y = windowHeight - fuseDis - fuseHeight;
	fuse[4].X = fuseDis;
	fuse[4].Y = rand() % (windowHeight - randLimitH) + 200;
	fuse[5].X = (windowWidth - fuseWidth) / 2;
	fuse[5].Y = (windowHeight - fuseHeight) / 2;
	fuse[6].X = 50;
	fuse[6].Y = windowHeight - 150;
	fuse[7].X = windowWidth - 150;
	fuse[7].Y = windowHeight - 150;
	fuse[8].X = windowWidth - 150;
	fuse[8].Y = 50;

	exitFlag = 0;
	gameOverFlag = 0;
	timeStore = 0;
	timeTextMin = 0;

	scoreToText.setFont(font);
	//secToText.setFont(font);
	fuseNumber.setFont(font);
	topScoreText.setFont(font);
	//secToText.setCharacterSize(20);
	scoreToText.setCharacterSize(20);
	fuseNumber.setCharacterSize(20);
	topScoreText.setCharacterSize(30);
	scoreToText.setPosition(windowWidth - 220, 0);
	//secToText.setPosition(windowWidth - 120, 0);
	topScoreText.setPosition(3000, 3000);
	fuseNumber.setPosition(0, 20);

	highestScoreTag.setTexture(highestScoreTex);
	scoreCard.setTexture(scoreCardTex);


	scoreCard.setPosition(3000, 3000);
	highestScoreTag.setPosition(3000, 3000);


	std::ostringstream topTimetoText;
	topTimetoText << "TOP TIME:" << topTime/60 << ":" << topTime%60;
	topScoreText.setString(topTimetoText.str());

	for (i = 0; i < 9; i++)
	{
		fuse[i].fuseBox.setPosition(fuse[i].X, fuse[i].Y);
		fuse[i].fuseHealthBar.setPosition(fuse[i].X - barDis, fuse[i].Y + fuseHeight + 15);
	}
	heart1.setSize(Vector2f(heartDim, heartDim));
	heart2.setSize(Vector2f(heartDim, heartDim));
	heart3.setSize(Vector2f(heartDim, heartDim));
	heart4.setSize(Vector2f(heartDim, heartDim));
	heart5.setSize(Vector2f(heartDim, heartDim));
	exit.setSize(Vector2f(110, 60));
	heart1.setOutlineColor(sf::Color::Transparent);
	heart2.setOutlineColor(sf::Color::Transparent);
	heart3.setOutlineColor(sf::Color::Transparent);
	heart4.setOutlineColor(sf::Color::Transparent);
	heart5.setOutlineColor(sf::Color::Transparent);
	heart5.setPosition(5, 5);
	heart4.setPosition(heartDim + 7, 5);
	heart3.setPosition(2 * heartDim + 9, 5);
	heart2.setPosition(3 * heartDim + 11, 5);
	heart1.setPosition(4 * heartDim + 13, 5);
	exit.setPosition(0, windowHeight - 60);
	heart1.setTexture(&heartFull);
	heart2.setTexture(&heartFull);
	heart3.setTexture(&heartFull);
	heart4.setTexture(&heartFull);
	heart5.setTexture(&heartFull);
	exit.setTexture(&exitDim);

	// for dark effect
	light = 100;
	player.setColor(Color(light, light, light));

	// reinitialization of variables if boss1 is played a second time
	windowWidth = 2000;
	windowHeight = 1500;
	dtMul = 60;
	//RADIUS_SPOTLIGHT = 125;
	//DIAMETER_SPOTLIGHT = 2 * radiusSpotlight;
	spriteSize = 20;
	lights[0].x = 0;
	lights[0].y = 0;
	lights[1].x = windowWidth;
	lights[1].y = 0;
	lights[2].x = windowWidth;
	lights[2].y = windowHeight;
	lights[3].x = 0;
	lights[3].y = windowHeight;
	lights[4].x = windowWidth / 2;
	lights[4].y = windowHeight / 2;
	lights[0].dirX = RIGHT;
	lights[0].dirY = DOWN;
	lights[1].dirX = LEFT;
	lights[1].dirY = DOWN;
	lights[2].dirX = LEFT;
	lights[2].dirY = UP;
	lights[3].dirX = RIGHT;
	lights[3].dirY = UP;
	lights[4].dirX = RIGHT;
	lights[4].dirY = DOWN;
	speedSpotlight = 7 * dtMul;
	fuseHealth = 100;
	//speed = 5;
	fuseDis = 70;
	range = 25;
	fuseWidth = 30;
	fuseHeight = 45;
	spotlightDamageRange = RADIUS_SPOTLIGHT + spriteSize - 5;
	spriteHealth = 150;
	lightDamage = .5*dtMul;
	healthBar = 10;
	heartDim = 16;
	barDis = 50 - fuseWidth / 2;
	randLimitW = fuseWidth + 200;
	randLimitH = fuseHeight + 200;

	// set the boundary of Sprite movement
	player.setBoundary(0, 0, windowWidth, windowHeight);

#ifdef _DEBUG
	cout << "boss1 scene initialized" << endl;
#endif // _DEBUG
}

void Boss1::Cleanup()
{
	resetView(*_gameViewtemp);
}

void Boss1::Pause()
{
	player.running = false;
	pause = true;

	// this function is going to be called when the game is paused
}

void Boss1::Resume()
{
	pause = false;

	// this function is going to be called when the game is resumed
}

void Boss1::togglePause()
{
	if (this->pause) Resume();
	else Pause();
}

void Boss1::HandleEvents(Engine * game, Event * event)
{
	// handle events here (keyboard/ mouse)

	if (event->type == Event::EventType::KeyPressed)
	{
		switch (event->key.code)
		{
		case Keyboard::Escape:
			togglePause();
			break;
		default:
			break;
		}
	}
}

void Boss1::Update(Engine * game, double dt)
{
	if (!pause)
	{
		if(!gameOverFlag)
		{
			timeStore += dt;
			if (timeStore >= 60)
			{
				timeStore = 0;
				timeTextMin++;
			}
			timeTextSec = timeStore;
			fuseCount = 0;
			for (i = 0; i < 9; i++) fuseCount += fuse[i].fuseState;
			std::ostringstream timeMin;
			timeMin << "TIME:" << timeTextMin << ":" << timeTextSec;
			scoreToText.setString(timeMin.str());

			std::ostringstream numberToText;
			numberToText << "FUSES LEFT : " << fuseCount;
			fuseNumber.setString(numberToText.str()); 
		}
		// Key press & release handle
		player.keyHandle();

		player.update(dt);

		position = player.getPosition();
		centreView(game->gameView, player.getPosition(), Vector2f(windowWidth, windowHeight));
		for (i = 0; i < 5; i++)
		{
			if (lights[i].x > windowWidth)								lights[i].dirX = LEFT;
			else if (lights[i].x < (-1)*(DIAMETER_SPOTLIGHT + 50))		lights[i].dirX = RIGHT;
			if (lights[i].y > windowHeight)								lights[i].dirY = UP;
			else if (lights[i].y < (-1)*(DIAMETER_SPOTLIGHT + 50))		lights[i].dirY = DOWN;

			if ((centreDis(lights[i].x + RADIUS_SPOTLIGHT, lights[i].y + RADIUS_SPOTLIGHT, position.x + spriteSize, position.y + spriteSize) < spotlightDamageRange))
				spriteHealth -= lightDamage * dt;

			lights[i].x += speedSpotlight * lights[i].dirX *dt;
			lights[i].y += speedSpotlight * lights[i].dirY *dt;
			lights[i].circleSpot.setPosition(lights[i].x, lights[i].y);

		}

		if (spriteHealth <= 140 && spriteHealth > 130) heart1.setTexture(&heartHalf);
		else if (spriteHealth <= 130 && spriteHealth > 120) heart1.setTexture(&heartEmpty);
		else if (spriteHealth <= 120 && spriteHealth > 110) heart1.setPosition(-500, 0);
		else if (spriteHealth <= 110 && spriteHealth > 100) heart2.setTexture(&heartHalf);
		else if (spriteHealth <= 100 && spriteHealth > 90) heart2.setTexture(&heartEmpty);
		else if (spriteHealth <= 90 && spriteHealth > 80) heart2.setPosition(-500, 0);
		else if (spriteHealth <= 80 && spriteHealth > 70) heart3.setTexture(&heartHalf);
		else if (spriteHealth <= 70 && spriteHealth > 60) heart3.setTexture(&heartEmpty);
		else if (spriteHealth <= 60 && spriteHealth > 50) heart3.setPosition(-500, 0);
		else if (spriteHealth <= 50 && spriteHealth > 40) heart4.setTexture(&heartHalf);
		else if (spriteHealth <= 40 && spriteHealth > 30) heart4.setTexture(&heartEmpty);
		else if (spriteHealth <= 30 && spriteHealth > 20) heart4.setPosition(-500, 0);
		else if (spriteHealth <= 20 && spriteHealth > 10) heart5.setTexture(&heartHalf);
		else if (spriteHealth <= 10 && spriteHealth > 0) heart5.setTexture(&heartEmpty);
		else if (spriteHealth <= 0)
		{
			//////// restarts level ///////////
			heart5.setPosition(-500, 0);
			spriteHealth = 150;
			game->popScene();
			game->pushScene(Boss1::getInstance());
		}																		//GAME OVER FLAG

		for (i = 0; i < 9; i++) fuse[i].fuseHealthBar.setSize(sf::Vector2f(fuse[i].health, healthBar));



		damageFuse = .5*dtMul*dt;
		for (i = 0; i < 9; i++)
		{
			if (fuse[i].health > 0)
			{
				exitFlag = 0;
				break;
			}
			exitFlag = 1;
		}
		if (exitFlag)
		{
			gameOverFlag = 1;
			exit.setTexture(&exitLit);
			if (position.x <= 110 && position.y >= (windowHeight - 60))
			{
				//////// return to previous scene /////////
				for (i = 0; i < 5; i++) 
				{
					lights[i].x = 3000; 
					lights[i].y = 3000;
				}
				scoreToText.setCharacterSize(50);
				scoreToText.setPosition(550, 1100);
				scoreCard.setPosition(0, 778);
				if (topTime!=0 && topTime <= timeTextMin * 60 + timeTextSec )
				{
					topScoreText.setPosition(500, 1250);
				}
				else highestScoreTag.setPosition(350, 1250);
				Boss1ScoreFile.close();
				if(Keyboard::isKeyPressed(Keyboard::Enter)) popScene(game);
			}
		}

		// controlling light and dark with respect to spotlight

	}

	// handle collision and other logic
	// update the sprites
	// use dt (interval between two frames) for framerate independent movement
}

void Boss1::Draw(RenderWindow * app)
{
	//app->setView(view1);
	app->draw(floor);
	for (i = 0; i < 9; i++)
		if (player.intersects(fuse[i].fuseBox.getGlobalBounds())) 
		{
			app->draw(fuse[i].fuseHealthBar);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (fuse[i].health > 0)
				{
					fuse[i].health -= damageFuse;
				}
				if (fuse[i].health <= 0)
				{
					fuse[i].fuseBox.setTexture(fuseOpened);
					fuse[i].fuseState = 0;
				}
			}
		}
	
	
	for (i = 0; i < 9; i++) app->draw(fuse[i].fuseBox);
	player.drawTo(app);
	app->draw(heart1);
	app->draw(heart2);
	app->draw(heart3);
	app->draw(heart4);
	app->draw(heart5);
	app->draw(exit);
	app->draw(scoreCard);
	app->draw(scoreToText);
	app->draw(topScoreText);
	app->draw(fuseNumber);
	app->draw(highestScoreTag);
	for (i = 0; i < 5; i++) app->draw(lights[i].circleSpot);
	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
