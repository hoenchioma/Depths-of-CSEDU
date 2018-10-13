#include "Boss1.h"

#include "EngineX/Utility.h"

#include <iostream>

using namespace sf;
using namespace std;


double centreDis(float X1, float Y1, float X2, float Y2)
{
	double  distance = sqrt(pow((X1 - X2), 2) + pow((Y1 - Y2), 2));
	return distance;
}


void Boss1::Init(Engine* game)
{
	cout << "scene created" << endl;

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
	Sprite.Init(tex, 0.1f, 300);
	Sprite.setScale(1.25, 1.25);
	Sprite.setPosition(30, game->height - 130);
	fuse[1].X = rand() % (windowWidth-randLimitW) + 200;
	fuse[2].Y = rand() % (windowHeight - randLimitH) + 200;
	fuse[3].X = rand() % (windowWidth  - randLimitW) + 200;
	fuse[4].Y = rand() % (windowHeight - randLimitH) + 200;
	fuse[5].X = (windowWidth - fuseWidth) / 2;
	fuse[5].Y = (windowHeight - fuseHeight) / 2;
	spotlight1.setPointCount(50);
	spotlight2.setPointCount(50);
	spotlight3.setPointCount(50);
	spotlight1.setRadius(radiusSpotlight);
	spotlight2.setRadius(radiusSpotlight);
	spotlight3.setRadius(radiusSpotlight);
	fuse1.setPosition(fuse[1].X, fuseDis);
	fuse2.setPosition(windowWidth - fuseDis, fuse[2].Y);
	fuse3.setPosition(fuse[3].X, windowHeight - fuseDis-fuseHeight);
	fuse4.setPosition(fuseDis, fuse[4].Y);
	fuse5.setPosition(fuse[5].X, fuse[5].Y);
	fuse1Bar.setPosition(fuse[1].X-barDis, fuseDis + fuseHeight +10);
	fuse2Bar.setPosition(windowWidth-fuseDis-barDis, fuse[2].Y+fuseHeight +10 );
	fuse3Bar.setPosition(fuse[3].X-barDis, windowHeight - fuseDis +10);
	fuse4Bar.setPosition(fuseDis - barDis, fuse[4].Y+fuseHeight+10);
	fuse5Bar.setPosition(fuse[5].X-barDis, fuse[5].Y + fuseHeight+10);
	fuse1.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse2.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse3.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse4.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse5.setSize(Vector2f(fuseWidth, fuseHeight));
	heart1.setSize(Vector2f(heartDim, heartDim));
	heart2.setSize(Vector2f(heartDim, heartDim));
	heart3.setSize(Vector2f(heartDim, heartDim));
	heart4.setSize(Vector2f(heartDim, heartDim));
	heart5.setSize(Vector2f(heartDim, heartDim));
	exit.setSize(Vector2f(110, 60));
	fuse1.setOutlineColor(sf::Color::Transparent);
	fuse2.setOutlineColor(sf::Color::Transparent);
	fuse3.setOutlineColor(sf::Color::Transparent);
	fuse4.setOutlineColor(sf::Color::Transparent);
	fuse5.setOutlineColor(sf::Color::Transparent);
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
	fuse1.setTexture(&fuseClosed);
	fuse2.setTexture(&fuseClosed);
	fuse3.setTexture(&fuseClosed);
	fuse4.setTexture(&fuseClosed);
	fuse5.setTexture(&fuseClosed);
	exit.setTexture(&exitDim);

	// for dark effect
	light = 100;
	Sprite.setColor(Color(light, light, light));
	fuse1.setFillColor(Color(light, light, light));
	fuse2.setFillColor(Color(light, light, light));
	fuse3.setFillColor(Color(light, light, light));
	fuse4.setFillColor(Color(light, light, light));
	fuse5.setFillColor(Color(light, light, light));
}

void Boss1::Cleanup()
{
}

void Boss1::Pause()
{
	Sprite.running = false;
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

	if (event->type == Event::EventType::KeyReleased)
	{
		for (auto& i : KeyArr)
		{
			if (event->key.code == i)
			{
				Sprite.moveOff();
			}
		}
	}

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
		// Key press handle
		for (auto& i : KeyArr)
		{
			if (Keyboard::isKeyPressed(i))
			{
				Sprite.moveOn(KeyMap.at(i));
			}
		}

		Sprite.update(dt);
	}
	position = Sprite.getPosition();

	if (spotlight1X > windowWidth)								spotlight1DirX = LEFT;
	else if (spotlight1X < (-1)*(diameterSpotlight + 50))		spotlight1DirX = RIGHT;
	if (spotlight1Y > windowHeight)								spotlight1DirY = UP;
	else if (spotlight1Y < (-1)*(diameterSpotlight + 50))		spotlight1DirY = DOWN;
	if (spotlight2X > windowWidth)								spotlight2DirX = LEFT;
	else if (spotlight2X < (-1)*(diameterSpotlight + 50))		spotlight2DirX = RIGHT;
	if (spotlight2Y > windowHeight)								spotlight2DirY = UP;
	else if (spotlight2Y < (-1)*(diameterSpotlight + 50))		spotlight2DirY = DOWN;
	if (spotlight3X > windowWidth)								spotlight3DirX = LEFT;
	else if (spotlight3X < (-1)*(diameterSpotlight + 50))		spotlight3DirX = RIGHT;
	if (spotlight3Y > windowHeight)								spotlight3DirY = UP;
	else if (spotlight3Y < (-1)*(diameterSpotlight + 50))		spotlight3DirY = DOWN;
	if ((centreDis(spotlight1X + radiusSpotlight, spotlight1Y + radiusSpotlight, position.x + spriteSize, position.y + spriteSize) < spotlightDamageRange) || (centreDis(spotlight2X + radiusSpotlight, spotlight2Y + radiusSpotlight, position.x + spriteSize, position.y + spriteSize) < spotlightDamageRange) || (centreDis(spotlight3X + radiusSpotlight, spotlight3Y + radiusSpotlight, position.x + spriteSize, position.y + spriteSize) < spotlightDamageRange))
		spriteHealth -= lightDamage * dt;
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
	spotlight1X += speedSpotlight * spotlight1DirX *dt;
	spotlight1Y += speedSpotlight * spotlight1DirY *dt;
	spotlight2X += speedSpotlight * spotlight2DirX *dt;
	spotlight2Y += speedSpotlight * spotlight2DirY *dt;
	spotlight3X += speedSpotlight * spotlight3DirX *dt;
	spotlight3Y += speedSpotlight * spotlight3DirY *dt;
	spotlight1.setPosition(spotlight1X, spotlight1Y);
	spotlight2.setPosition(spotlight2X, spotlight2Y);
	spotlight3.setPosition(spotlight3X, spotlight3Y);
	fuse1Bar.setSize(sf::Vector2f(fuse[1].Health, healthBar));
	fuse2Bar.setSize(sf::Vector2f(fuse[2].Health, healthBar));
	fuse3Bar.setSize(sf::Vector2f(fuse[3].Health, healthBar));
	fuse4Bar.setSize(sf::Vector2f(fuse[4].Health, healthBar));
	fuse5Bar.setSize(sf::Vector2f(fuse[5].Health, healthBar));
	damageFuse = .5*dtMul*dt;
	if (fuse[1].Health <= 0 && fuse[2].Health <= 0 && fuse[3].Health <= 0 && fuse[4].Health <= 0 && fuse[5].Health)
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

	for (int j = 0; j < 5; j++)
	{
		LitFuse = false;
		for (int i = 0; i < 3; i++)
		{
			/*cout << centreDis(
				spotlightArray[i]->getPosition().x + spotlightArray[i]->getRadius(),
				spotlightArray[i]->getPosition().y + spotlightArray[i]->getRadius(),
				fuseArray[j]->getPosition().x,
				fuseArray[j]->getPosition().y
			) << " " << spotlightArray[i]->getRadius() << endl;*/
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
		Sprite.setColor(Color(light, light, light));

	// handle collision and other logic
	// update the sprites
	// use dt (interval between two frames) for framerate independent movement
}

void Boss1::Draw(RenderWindow * app)
{
	if (centreDis(position.x + spriteSize, position.y + spriteSize, fuse[1].X + fuseWidth / 2, fuseDis + fuseHeight / 2) < range)
	{
		app->draw(fuse1Bar);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (fuse[1].Health > 0)
			{
				fuse[1].Health -= damageFuse;
			}
			if (fuse[1].Health <= 0)
			{
				fuse1.setTexture(&fuseOpened);
				fuse1.setSize(Vector2f(fuseWidth + 20, fuseHeight + 30));
			}
		}
	}
	else if (centreDis(position.x + spriteSize, position.y + spriteSize, windowWidth - fuseDis + fuseWidth / 2, fuse[2].Y + fuseHeight / 2) < range)
	{
		app->draw(fuse2Bar);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (fuse[2].Health > 0)
			{
				fuse[2].Health -= damageFuse;
			}
			if (fuse[2].Health <= 0)
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
			if (fuse[3].Health > 0)
			{
				fuse[3].Health -= damageFuse;
			}
			if (fuse[3].Health <= 0)
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
			if (fuse[4].Health > 0)
			{
				fuse[4].Health -= damageFuse;
			}
			if (fuse[4].Health <= 0)
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
			if (fuse[5].Health > 0)
			{
				fuse[5].Health -= damageFuse;
			}
			if (fuse[5].Health <= 0)
			{
				fuse5.setTexture(&fuseOpened);
				fuse5.setSize(Vector2f(fuseWidth+20, fuseHeight+30));
			}
		}
	}
	app->draw(spotlight1);
	app->draw(spotlight2);
	app->draw(spotlight3);
	app->draw(fuse1);
	app->draw(fuse2);
	app->draw(fuse3);
	app->draw(fuse4);
	app->draw(fuse5);
	Sprite.drawTo(app);
	app->draw(heart1);
	app->draw(heart2);
	app->draw(heart3);
	app->draw(heart4);
	app->draw(heart5);
	app->draw(exit);

	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
