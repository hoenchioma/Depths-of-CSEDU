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
}

void Boss1::Init(Engine* game)
{
	resetView(game->gameView);
	_gameViewtemp = &game->gameView;

	player.Init(tex, 0.1f, 300);
	player.setScale(1.4f, 1.4f);
	player.setPosition(30, game->height - 130);
	player.setDirec(Direction::UP);
	lights[0].x = 0;
	lights[0].y = 0;
	lights[1].x = windowWidth;
	lights[1].y = 0;
	lights[2].x = windowWidth;
	lights[2].y = windowHeight;
	lights[3].x = 0;
	lights[3].y = windowHeight;
	lights[4].x = windowWidth/2;
	lights[4].y = windowHeight/2;
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
	fuse[1].X = rand() % (windowWidth-randLimitW) + 200;
	fuse[1].Y = fuseDis;
	fuse[2].X = windowWidth - fuseDis;
	fuse[2].Y = rand() % (windowHeight - randLimitH) + 200;
	fuse[3].X = rand() % (windowWidth  - randLimitW) + 200;
	fuse[3].Y = windowHeight - fuseDis - fuseHeight;
	fuse[4].X = fuseDis;
	fuse[4].Y = rand() % (windowHeight - randLimitH) + 200;
	fuse[5].X = (windowWidth - fuseWidth) / 2;
	fuse[5].Y = (windowHeight - fuseHeight) / 2;
	fuse[6].X = 50;
	fuse[6].Y = windowHeight-150;
	fuse[7].X = windowWidth - 150;
	fuse[7].Y = windowHeight - 150;
	fuse[8].X = windowWidth-150;
	fuse[8].Y = 50;
	for (i = 0; i < 9; i++)
	{
		fuse[i].fuseBox.setPosition(fuse[i].X, fuse[i].Y);
		fuse[i].fuseHealthBar.setPosition(fuse[i].X - barDis, fuse[i].Y + fuseHeight + 15);
	}
	/*fuse1Bar.setPosition(fuse[1].X-barDis, fuseDis + fuseHeight +10);
	fuse2Bar.setPosition(windowWidth-fuseDis-barDis, fuse[2].Y+fuseHeight +10 );
	fuse3Bar.setPosition(fuse[3].X-barDis, windowHeight - fuseDis +10);
	fuse4Bar.setPosition(fuseDis - barDis, fuse[4].Y+fuseHeight+10);
	fuse5Bar.setPosition(fuse[5].X-barDis, fuse[5].Y + fuseHeight+10);
	fuse1.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse2.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse3.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse4.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse5.setSize(Vector2f(fuseWidth, fuseHeight));*/
	heart1.setSize(Vector2f(heartDim, heartDim));
	heart2.setSize(Vector2f(heartDim, heartDim));
	heart3.setSize(Vector2f(heartDim, heartDim));
	heart4.setSize(Vector2f(heartDim, heartDim));
	heart5.setSize(Vector2f(heartDim, heartDim));
	exit.setSize(Vector2f(110, 60));
	/*fuse1.setOutlineColor(sf::Color::Transparent);
	fuse2.setOutlineColor(sf::Color::Transparent);
	fuse3.setOutlineColor(sf::Color::Transparent);
	fuse4.setOutlineColor(sf::Color::Transparent);
	fuse5.setOutlineColor(sf::Color::Transparent);*/
	heart1.setOutlineColor(sf::Color::Transparent);
	heart2.setOutlineColor(sf::Color::Transparent);
	heart3.setOutlineColor(sf::Color::Transparent);
	heart4.setOutlineColor(sf::Color::Transparent);
	heart5.setOutlineColor(sf::Color::Transparent);
	heart5.setPosition(5, 5);
	heart4.setPosition(heartDim+7, 5);
	heart3.setPosition(2*heartDim+9, 5);
	heart2.setPosition(3*heartDim+11, 5);
	heart1.setPosition(4*heartDim+13, 5);
	exit.setPosition(0, windowHeight - 60);
	heart1.setTexture(&heartFull);
	heart2.setTexture(&heartFull);
	heart3.setTexture(&heartFull);
	heart4.setTexture(&heartFull);
	heart5.setTexture(&heartFull);
	/*fuse1.setTexture(&fuseClosed);
	fuse2.setTexture(&fuseClosed);
	fuse3.setTexture(&fuseClosed);
	fuse4.setTexture(&fuseClosed);
	fuse5.setTexture(&fuseClosed);*/
	exit.setTexture(&exitDim);
	//view1.setSize(sf::Vector2f(windowWidth, windowHeight));

	
	//view1.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	// for dark effect
	light = 100;
	player.setColor(Color(light, light, light));
	/*fuse1.setFillColor(Color(light, light, light));
	fuse2.setFillColor(Color(light, light, light));
	fuse3.setFillColor(Color(light, light, light));
	fuse4.setFillColor(Color(light, light, light));
	fuse5.setFillColor(Color(light, light, light));*/

	// reinitialization of variables if boss1 is played a second time
	windowWidth = 2000;
	windowHeight = 1500;
	dtMul = 50;
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
	speedSpotlight = 2.5*dtMul;
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
		//view1.setCenter(Sprite.getPosition().x, Sprite.getPosition().y);
		//view1.setCenter(sf::Vector2f(350.f, 300.f));
		// Key press & release handle
		player.keyHandle();

		player.update(dt);

		position = player.getPosition();
		centreView(game->gameView, player.getPosition(), Vector2f(windowWidth, windowHeight));
		for(i=0;i<5;i++)
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
		if (fuse[1].health <= 0 && fuse[2].health <= 0 && fuse[3].health <= 0 && fuse[4].health <= 0 && fuse[5].health)
		{
			exit.setTexture(&exitLit);
			if (position.x <= 110 && position.y >= (windowHeight - 60))
			{
				//////// return to previous scene /////////
				popScene(game);
			}
		}

		// controlling light and dark with respect to spotlight

		/*int i = 0;
		cout << centreDis(
			spotlightArray[i]->getPosition().x + spotlightArray[i]->getRadius(),
			spotlightArray[i]->getPosition().y + spotlightArray[i]->getRadius(),
			Sprite.getPosition().x,
			Sprite.getPosition().y
		) << " " << spotlightArray[i]->getRadius() << endl;*/

		bool LitFuse;
		bool LitSprite;

		/*for (int j = 0; j < 5; j++)
		{
			LitFuse = false;
			for (int i = 0; i < 3; i++)
			{
				/*cout << centreDis(
					spotlightArray[i]->getPosition().x + spotlightArray[i]->getRadius(),
					spotlightArray[i]->getPosition().y + spotlightArray[i]->getRadius(),
					fuseArray[j]->getPosition().x,
					fuseArray[j]->getPosition().y
				) << " " << spotlightArray[i]->getRadius() << endl;
				if (centreDis(
					spotlightArray[i]->getPosition().x + spotlightArray[i]->getRadius(),
					spotlightArray[i]->getPosition().y + spotlightArray[i]->getRadius(),
					fuseArray[j]->getPosition().x,
					fuseArray[j]->getPosition().y
				) < spotlightArray[i]->getRadius())
				{
					LitFuse = true;
					fuseArray[j]->setFillColor(Color(255, 255, 255));
				}
			}
			if (!LitFuse)
				fuseArray[j]->setFillColor(Color(light, light, light));
		}
		LitSprite = false;
		for (int i = 0; i < 3; i++)
		{
			if (centreDis(
				spotlightArray[i]->getPosition().x + spotlightArray[i]->getRadius(),
				spotlightArray[i]->getPosition().y + spotlightArray[i]->getRadius(),
				Sprite.getPosition().x,
				Sprite.getPosition().y
			) < spotlightArray[i]->getRadius())
			{
				LitSprite = true;
				Sprite.setColor(Color(255, 255, 255));
			}
		}
		if (!LitSprite)
			Sprite.setColor(Color(light, light, light));*/

	}

	// handle collision and other logic
	// update the sprites
	// use dt (interval between two frames) for framerate independent movement
}

void Boss1::Draw(RenderWindow * app)
{
	//app->setView(view1);
	for(i = 0; i < 9; i++) 
		if (player.intersects(fuse[i].fuseBox.getGlobalBounds())) //player.intersects(fuse[i].fuseBox))
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
					//fuse[i].setSize(Vector2f(fuseWidth + 20, fuseHeight + 30));
				}
			}
		}
	/*else if (centreDis(position.x + spriteSize, position.y + spriteSize, windowWidth - fuseDis + fuseWidth / 2, fuse[2].Y + fuseHeight / 2) < range)
	{
		app->draw(fuse2Bar);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (fuse[2].health > 0)
			{
				fuse[2].health -= damageFuse;
			}
			if (fuse[2].health <= 0)
			{
				fuse2.setTexture(&fuseOpened);
				fuse2.setSize(Vector2f(fuseWidth + 20, fuseHeight + 30));
			}
		}
	}
	else if (centreDis(position.x + spriteSize, position.y + spriteSize, fuse[3].X + fuseWidth / 2, windowHeight - fuseDis) < range)
	{
		app->draw(fuse3Bar);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (fuse[3].health > 0)
			{
				fuse[3].health -= damageFuse;
			}
			if (fuse[3].health <= 0)
			{
				fuse3.setTexture(&fuseOpened);
				fuse3.setSize(Vector2f(fuseWidth + 20, fuseHeight + 30));
			}
		}
	}
	else if (centreDis(position.x + spriteSize, position.y + spriteSize, fuseDis + fuseWidth / 2, fuse[4].Y + fuseHeight / 2) < range)
	{
		app->draw(fuse4Bar);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (fuse[4].health > 0)
			{
				fuse[4].health -= damageFuse;
			}
			if (fuse[4].health <= 0)
			{
				fuse4.setTexture(&fuseOpened);
				fuse4.setSize(Vector2f(fuseWidth + 20, fuseHeight + 30));
			}
		}
	}
	else if (centreDis(position.x + spriteSize, position.y + spriteSize, fuse[5].X + fuseWidth / 2, fuse[5].Y + fuseWidth / 2) < range)
	{
		app->draw(fuse5Bar);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (fuse[5].health > 0)
			{
				fuse[5].health -= damageFuse;
			}
			if (fuse[5].health <= 0)
			{
				fuse5.setTexture(&fuseOpened);
				fuse5.setSize(Vector2f(fuseWidth+20, fuseHeight+30));
			}
		}
	}*/
	for (i = 0; i < 5; i++) app->draw(lights[i].circleSpot);
	for (i = 0; i < 9; i++) app->draw(fuse[i].fuseBox);
	player.drawTo(app);
	app->draw(heart1);
	app->draw(heart2);
	app->draw(heart3);
	app->draw(heart4);
	app->draw(heart5);
	app->draw(exit);

	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
