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
	font.loadFromFile("res/Font/unispace bd.ttf");
	//Boss1ScoreFile.open("save/Boss1ScoreFile.txt", ios::in | ios::out);
	highestScoreTex.loadFromFile("res/HighScoreTag.png");
	scoreCardTex.loadFromFile("res/scoreCard.png");
	floorTexture.loadFromFile("res/floorBoss1.png");
	tableFlipTex.loadFromFile("res/tableEEEFlip.png");
	tableHorTex.loadFromFile("res/tableEEEHorizontal.png");
	tableNormTex.loadFromFile("res/tableEEE.png");
	tableBotTex.loadFromFile("res/tableBottom.png");
	doorCloseTex.loadFromFile("res/doubleDoorClose.png");
	doorOpenTex.loadFromFile("res/doubleDoorOpen.png");
	fuseBotSideOpenTex.loadFromFile("res/fuseBottomSideOpen.png");
	fuse[3].fuseOpenTex.loadFromFile("res/fuseBottomOpen.png");
	fuse[4].fuseOpenTex.loadFromFile("res/fuseBottomOpen.png");
	fuse[3].fuseCloseTex.loadFromFile("res/fuseBottomClose.png");
	fuse[4].fuseCloseTex.loadFromFile("res/fuseBottomClose.png");
	perkBuffer.loadFromFile("res/Sounds/powerUp.wav");
	loadFromFile(textBoxFont, "res/Font/PressStart2P.ttf");
}

void Boss1::Init(Engine* game)
{
	resetView(game->gameView);
	_gameViewtemp = &game->gameView;
	this->game = game;

	ifstream Boss1ScoreFileIn;
	Boss1ScoreFileIn.open("save/Boss2ScoreFile.txt");
	Boss1ScoreFileIn >> topTime;
	Boss1ScoreFileIn.close();

	fileClose = 0;
	//Boss1ScoreFile >> topTime;
	player.Init(tex, 0.1f, 300);
	player.setScale(1.4f, 1.4f);
	player.setPosition(game->width-50,  60);
	player.setDirec(Direction::DOWN);
	
	lights[0].x = 0;
	lights[0].y = 0;
	lights[1].x = windowWidth;
	lights[1].y = 0;
	lights[2].x = windowWidth;
	lights[2].y = windowHeight;
	lights[3].x = 0;
	lights[3].y = windowHeight;
	lights[0].dirX = RIGHT;
	lights[0].dirY = DOWN;
	lights[1].dirX = LEFT;
	lights[1].dirY = DOWN;
	lights[2].dirX = LEFT;
	lights[2].dirY = UP;
	lights[3].dirX = RIGHT;
	lights[3].dirY = UP;

	fuse[0].X = 90;
	fuse[0].Y = 18;
	fuse[1].X = 2;
	fuse[1].Y = windowHeight/2+30;
	fuse[2].X = 2;
	fuse[2].Y = windowHeight - 20;
	fuse[3].X = 410;
	fuse[3].Y = windowHeight-21;
	fuse[4].X = 740;
	fuse[4].Y = windowHeight-21;
	fuse[5].X = windowWidth - 3;
	fuse[5].Y = windowHeight - 70;
	fuse[6].X = windowWidth -3;
	fuse[6].Y = windowHeight/2-15;

	exitFlag = 0;
	gameOverFlag = 0;
	timeStore = 0;
	timeTextMin = 0;

	speedPerk = 0;
	invinciblePerk = 0;
	timeFreezePerk = 0;

	scoreToText.setFont(font);
	fuseNumber.setFont(font);
	topScoreText.setFont(font);
	scoreToText.setCharacterSize(20);
	fuseNumber.setCharacterSize(20);
	topScoreText.setCharacterSize(30);
	scoreToText.setPosition(windowWidth - 220, 0);
	topScoreText.setPosition(3000, 3000);
	fuseNumber.setPosition(0, 20);

	
	highestScoreTag.setTexture(highestScoreTex);
	scoreCard.setTexture(scoreCardTex);
	floor.setTexture(floorTexture);
	door.setTexture(doorCloseTex);
	door.setPosition(windowWidth - 100, 0);

	tableBottom.object.setTexture(tableBotTex);
	tableDLD[0].object.setTexture(tableNormTex);
	tableDLD[1].object.setTexture(tableNormTex);
	tableDLD[2].object.setTexture(tableHorTex);
	tableDLD[3].object.setTexture(tableHorTex);
	tableDLD[4].object.setTexture(tableHorTex);
	tableDLD[5].object.setTexture(tableFlipTex);
	tableDLD[6].object.setTexture(tableFlipTex);
	tableDLD[0].object.setPosition(5, 410);
	tableDLD[1].object.setPosition(5, 110);
	tableDLD[2].object.setPosition(190, windowHeight-105);
	tableDLD[3].object.setPosition(510, windowHeight - 105);
	tableDLD[4].object.setPosition(850, windowHeight - 105);
	tableDLD[5].object.setPosition(1165, 110);
	tableDLD[6].object.setPosition(1165, 410);
	for (i = 0; i < 7; i++)
	{
		tableDLD[i].object.setScale(.7, .7);
		//tableDLD[i].ICnum = i+1;
	}
	tableBottom.object.setScale(.7, .7);
	tableBottom.object.setPosition(500, 20);

	for (i = 0; i < 7; i++) player.dontIntersect(tableDLD[i].object.getGlobalBounds());
	player.dontIntersect(tableBottom.object.getGlobalBounds());

	

	scoreCard.setPosition(3000, 3000);
	highestScoreTag.setPosition(3000, 3000);


	std::ostringstream topTimetoText;
	topTimetoText << "TOP TIME:" << topTime/60 << ":" << topTime%60;
	topScoreText.setString(topTimetoText.str());

	for (i = 0; i < 7; i++)
	{
		fuse[i].fuseBox.setPosition(fuse[i].X, fuse[i].Y);
		fuse[i].fuseHealthBar.setPosition(3000,3000);
	}
	bot3Side.setTexture(fuseBotSideOpenTex);
	bot4Side.setTexture(fuseBotSideOpenTex);
	bot3Side.setScale(.15, .2);
	bot4Side.setScale(.15, .2);
	bot4Side.setPosition(3000, 3000);
	bot3Side.setPosition(3000, 3000);

	for (i = 0; i < 7; i++)
	{
		fuse[i].fuseBox.setTexture(fuse[i].fuseCloseTex);
		fuse[i].health = 100;
		fuse[i].fuseState = 1;
	}
	//fuse[3].fuseBox.setTexture(fuseBotCloseTex);
	fuse[3].fuseBox.setScale(.15,.2);
	//fuse[4].fuseBox.setTexture(fuseBotCloseTex);
	fuse[4].fuseBox.setScale(.15, .2);

	fuse[1].fuseBox.setRotation(-90);
	fuse[2].fuseBox.setRotation(-90);
	fuse[5].fuseBox.setRotation(90);
	fuse[6].fuseBox.setRotation(90);

	// for dark effect
	light = 100;
	player.setColor(Color(light, light, light));

	// set the boundary of Sprite movement
	player.setBoundary(40, 55, windowWidth-50, windowHeight-70);

	///////// textBox /////////////
	textBox.Init(game, textBoxFont);
	textBox.addTextTyped("Hello world!!");

	///////// restart menu ///////////
	menu.Init(game, this, textBoxFont);

	///////// minimap ////////////
	game->miniMapOn = true;
	game->miniMap.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));


	////////sound
	perkSound.setBuffer(perkBuffer);
	perkSound.setVolume(15);

#ifdef _DEBUG
	cout << "boss1 scene initialized" << endl;
#endif // _DEBUG
}

void Boss1::Cleanup()
{
	resetView(*_gameViewtemp);

	menu.turnOff();
	textBox.setText("");
	textBox.turnOn();

	this->game->miniMapOn = false;
	_fullScreen = false;
	game->fullScreen.reset(FloatRect(0, 0, game->fullWidth, game->fullHeight));

	//Resume();
}

void Boss1::Pause()
{
	pause = true;

	player.pause();
	textBox.time.pause();

	// this function is going to be called when the game is paused
}

void Boss1::Resume()
{
	pause = false;

	player.resume();
	textBox.time.resume();

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

	textBox.handleEvent(event);
	menu.handleEvent(event);
}

void Boss1::Update(Engine * game, double dt)
{
	if (!pause)
	{
		if ((speedPerk || invinciblePerk || timeFreezePerk) && perkSound.getStatus() != Sound::Status::Playing) perkSound.play();

		if (Keyboard::isKeyPressed(Keyboard::Num1) && !fileClose && INVI("speed")>0 && !speedPerk)
		{
			player.setVel(800);
			speedPerk = 1;
			INVI("speed")--;
			speedPerkTime.restart();

		}
		if (speedPerkTime.getElapsedTime().asSeconds() > perkTime && speedPerk) player.setVel(300);


		if (Keyboard::isKeyPressed(Keyboard::Num2) && !fileClose && INVI("invincible") > 0 && !invinciblePerk)
		{
			invinciblePerk = 1;
			invinciblePerkTime.restart();
			INVI("invincible")--;
		}
		if (invinciblePerkTime.getElapsedTime().asSeconds() > perkTime && invinciblePerk) invinciblePerk = 0;

		if (Keyboard::isKeyPressed(Keyboard::Num3) && !fileClose && INVI("timeFreeze") > 0 && !timeFreezePerk)
		{
			timeFreezePerk = 1;
			timeFreezeTime.restart();
			INVI("timeFreeze")--;
		}
		
		if (timeFreezeTime.getElapsedTime().asSeconds() > perkTime && timeFreezePerk) timeFreezePerk = 0;

		if(!gameOverFlag)
		{
			if(!timeFreezePerk)timeStore += dt;
			if (timeStore >= 60)
			{
				timeStore = 0;
				timeTextMin++;
			}
			timeTextSec = timeStore;
			fuseCount = 0;
			for (i = 0; i < 7; i++) fuseCount += fuse[i].fuseState;
			if(fuseCount==0) door.setTexture(doorOpenTex);
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

		//centreView(game->gameView, player.getPosition(), Vector2f(windowWidth, windowHeight));
		for (i = 0; i < 4; i++)
		{
			if (!invinciblePerk && (centreDis(lights[i].x + RADIUS_SPOTLIGHT, lights[i].y + RADIUS_SPOTLIGHT, player.getPosition().x + spriteSize, player.getPosition().y + spriteSize) < spotlightDamageRange))
			{

				spriteHealth -= lightDamage * dt;
			}

			if (lights[i].x > windowWidth)								lights[i].dirX = LEFT;
			else if (lights[i].x < (-1)*(DIAMETER_SPOTLIGHT + 50))		lights[i].dirX = RIGHT;
			if (lights[i].y > windowHeight)								lights[i].dirY = UP;
			else if (lights[i].y < (-1)*(DIAMETER_SPOTLIGHT + 50))		lights[i].dirY = DOWN;

			if(!timeFreezePerk)
			{
				lights[i].x += speedSpotlight * lights[i].dirX *dt;
				lights[i].y += speedSpotlight * lights[i].dirY *dt;
				lights[i].circleSpot.setPosition(lights[i].x, lights[i].y);
			}


			

		}
			
			//////// restarts level ///////////
			
		
		diffInt = spriteHealth/ 30;
		diffFloat = spriteHealth / 30.0;
		if (diffInt < diffFloat) diffInt++;
		for (i = 0; i < diffInt; i++)
		{
			healthDiff = spriteHealth-i*30;
			
			if (healthDiff > 0)
			{
				if (healthDiff > 20)	heartSprite[i].setTexture(heartFull);
				else if (healthDiff <= 20 && healthDiff > 10) heartSprite[i].setTexture(heartHalf);
				else if (healthDiff <= 10 ) heartSprite[i].setTexture(heartEmpty);
				heartSprite[i].setPosition(i * 20 + 10, 0);
			}
			else heartSprite[i].setPosition(-300, -3000);
		}


		if (spriteHealth <= 0 && INVI("reLife") <= 0)
		{
			Pause();
			menu.turnOn();
		}
		else if (INVI("reLife") > 0 && spriteHealth<=0)
		{
			spriteHealth = 60;
			player.setPosition(game->width - 50, 60);
			player.setDirec(Direction::DOWN);
			INVI("reLife")--;
		}
		for (i = 0; i < 7; i++) fuse[i].fuseHealthBar.setSize(sf::Vector2f(fuse[i].health, healthBar));



		damageFuse = .5*dtMul*dt;
		for (i = 0; i < 7; i++)
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
			if (player.intersects(door.getGlobalBounds()))
			{
				//////// return to previous scene /////////
				_fullScreen = true;
				game->fullScreen.reset(FloatRect(0, 0, windowWidth, windowHeight));
				textBox.turnOff();

				for (i = 0; i < 4; i++) 
				{
					lights[i].x = 3000; 
					lights[i].y = 3000;
				}
				scoreToText.setCharacterSize(50);
				scoreToText.setPosition(500, 200);
				scoreCard.setPosition(0, 0);
				if (topTime!=0 && topTime <= timeTextMin * 60 + timeTextSec )
				{
					topScoreText.setPosition(500, 300);
				}
				else
				{
					highestScoreTag.setPosition(350, 300);
					if (!fileClose)
					{
						ofstream Boss1ScoreFileOut;
						Boss1ScoreFileOut.open("save/Boss1ScoreFile.txt");
						Boss1ScoreFileOut << timeTextMin * 60 + timeTextSec;
						Boss1ScoreFileOut.close();
					}
				}
				fileClose = 1;
				//Boss1ScoreFile.close();
				if(Keyboard::isKeyPressed(Keyboard::Enter)) popScene(game);
			}
		}

		// updates the textBox
		textBox.update();

	}

	// handle collision and other logic
	// update the sprites
	// use dt (interval between two frames) for framerate independent movement
}

void Boss1::Draw(RenderWindow * app)
{
	//app->setView(view1);
	app->draw(floor);
	app->draw(door);

	for (i = 0; i < 7; i++) app->draw(tableDLD[i].object);
	for (i = 0; i < 7; i++)
		if(player.intersects(fuse[i].fuseBox.getGlobalBounds()) && fuse[i].health>0) 
		{
			fuse[i].fuseHealthBar.setPosition(player.getPosition().x - 50, player.getPosition().y+11);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (fuse[i].health > 0)
				{
					fuse[i].health -= damageFuse;
				}
				if (fuse[i].health <= 0)
				{
					fuse[i].fuseBox.setTexture(fuse[i].fuseOpenTex);
					//fuse[4].fuseBox.setScale(1, 1);
					fuse[i].fuseState = 0;
				}
			}
		}
		else fuse[i].fuseHealthBar.setPosition(3000, 3000);


	if(fuse[3].health<=0) 	bot3Side.setPosition(fuse[3].X + 68, fuse[3].Y - 22);
	if(fuse[4].health<=0) bot4Side.setPosition(fuse[4].X + 68, fuse[4].Y - 22);

	
	
	app->draw(tableBottom.object);
	for (i = 0; i < 7; i++) app->draw(fuse[i].fuseBox);
	player.drawTo(app);
	for (i = 0; i < 7; i++) app->draw(fuse[i].fuseHealthBar);
	app->draw(bot3Side);
	app->draw(bot4Side);
	/*app->draw(heart1);
	app->draw(heart2);
	app->draw(heart3);
	app->draw(heart4);
	app->draw(heart5);*/
	for (i = 0; i < diffInt; i++) app->draw(heartSprite[i]);
	app->draw(fuseNumber);
	app->draw(scoreCard);
	app->draw(scoreToText);
	app->draw(topScoreText);
	app->draw(highestScoreTag);
	for (i = 0; i < 4; i++) app->draw(lights[i].circleSpot);


	textBox.draw();
	menu.draw(app);
	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
