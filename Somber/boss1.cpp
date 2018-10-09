#include "boss1.h"

#include "EngineX/Utility.h"

using namespace sf;
using namespace std;


double centreDis(float X1, float Y1, float X2, float Y2)
{
	double  distance = sqrt(pow((X1 - X2), 2) + pow((Y1 - Y2), 2));
	return distance;
}


void boss1::Init(Engine* game)
{
	cout << "scene created" << endl;
	if (!tex.loadFromFile("res/running_1.png"))
	{
		cout << "can't load texture" << endl;
	}
	Sprite.Init(tex, 0.1, 300);
	Sprite.setScale(1.25, 1.25);
	fuse[1].X = rand() % (windowWidth - 40) + 40;
	fuse[2].Y = rand() % (windowHeight - 40) + 40;
	fuse[3].X = rand() % (windowWidth - 40) + 40;
	fuse[4].Y = rand() % (windowHeight - 40) + 40;
	fuse[5].X = (windowWidth - fuseWidth) / 2;
	fuse[5].Y = (windowHeight - fuseHeight) / 2;
	//sprite.setPointCount(4);
	spotlight1.setPointCount(50);
	spotlight2.setPointCount(50);
	spotlight3.setPointCount(50);
	spotlight1.setRadius(radiusSpotlight);
	spotlight2.setRadius(radiusSpotlight);
	spotlight3.setRadius(radiusSpotlight);
	//sprite.setFillColor(sf::Color(0, 0, 255));
	//sprite.setRadius(spriteSize);
	fuse1.setPosition(fuse[1].X, fuseDis);
	fuse2.setPosition(windowWidth - fuseDis, fuse[2].Y);
	fuse3.setPosition(fuse[3].X, windowHeight - fuseDis);
	fuse4.setPosition(fuseDis, fuse[4].Y);
	fuse5.setPosition(fuse[5].X, fuse[5].Y);
	fuse1Bar.setPosition(fuse[1].X, fuseDis + fuseHeight / 2);
	fuse2Bar.setPosition(windowWidth - barDis - fuseHealth, fuse[2].Y);
	fuse3Bar.setPosition(fuse[3].X, windowHeight - fuseDis + barDis);
	fuse4Bar.setPosition(fuseDis - barDis, fuse[4].Y);
	fuse5Bar.setPosition(fuse[5].X, fuse[5].Y + barDis);
	healthBarSprite.setFillColor(sf::Color(255, 0, 0));
	fuse1.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse2.setSize(Vector2f(fuseHeight, fuseWidth));
	fuse3.setSize(Vector2f(fuseWidth, fuseHeight));
	fuse4.setSize(Vector2f(fuseHeight, fuseWidth));
	fuse5.setSize(Vector2f(fuseWidth, fuseHeight));
	// Initialize variables here
}

void boss1::Cleanup()
{
}

void boss1::Pause()
{
	Sprite.running = false;
	pause = true;

	// handle what happens when the game is paused
	// this function is going to be called when the game is paused
}

void boss1::Resume()
{
	pause = false;

	// handle what happens when the game is resumed
	// this function is going to be called when the game is resumed
}

void boss1::togglePause()
{
	if (this->pause) Resume();
	else Pause();
}

void boss1::HandleEvents(Engine * game, Event * event)
{
	// handle events here (keyboard/ mouse)
	// see main.cpp for clarification of location of call

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

void boss1::Update(Engine * game, double dt)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position.x >= speed) position.x -= speed*dt*dtMul;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && position.x <= windowWidth - spriteSize * 2 - speed)	position.x += speed * dt*dtMul;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && position.y <= windowHeight - spriteSize * 2 - speed) position.y += speed * dt*dtMul;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position.y >= speed) position.y -= speed * dt*dtMul;*/

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
	if (spriteHealth < 0) gameOver = 1;							//GAME OVER FLAG
	healthBarSprite.setSize(sf::Vector2f(spriteHealth, 20));
	spotlight1X += speedSpotlight * spotlight1DirX *dt;
	spotlight1Y += speedSpotlight * spotlight1DirY *dt;
	spotlight2X += speedSpotlight * spotlight2DirX *dt;
	spotlight2Y += speedSpotlight * spotlight2DirY *dt;
	spotlight3X += speedSpotlight * spotlight3DirX *dt;
	spotlight3Y += speedSpotlight * spotlight3DirY *dt;
	spotlight1.setPosition(spotlight1X, spotlight1Y);
	spotlight2.setPosition(spotlight2X, spotlight2Y);
	spotlight3.setPosition(spotlight3X, spotlight3Y);
	//sprite.setPosition(position.x, position.y);
	fuse1Bar.setSize(sf::Vector2f(fuse[1].Health, healthBar));
	fuse2Bar.setSize(sf::Vector2f(fuse[2].Health, healthBar));
	fuse3Bar.setSize(sf::Vector2f(fuse[3].Health, healthBar));
	fuse4Bar.setSize(sf::Vector2f(fuse[4].Health, healthBar));
	fuse5Bar.setSize(sf::Vector2f(fuse[5].Health, healthBar));
	damageFuse = .5*dtMul*dt;
	// handle collision and other logic
	// update the sprites
	// use dt (interval between two frames) for framerate independent movement
}

void boss1::Draw(RenderWindow * app)
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
		}
	}
	else if (centreDis(position.x + spriteSize, position.y + spriteSize, windowWidth - fuseDis + fuseHeight / 2, fuse[2].Y + fuseWidth / 2) < range)
	{
		app->draw(fuse2Bar);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (fuse[2].Health > 0)
			{
				fuse[2].Health -= damageFuse;
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
		}
	}
	else if (centreDis(position.x + spriteSize, position.y + spriteSize, fuseDis + fuseHeight / 2, fuse[4].Y + fuseWidth / 2) < range)
	{
		app->draw(fuse4Bar);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (fuse[4].Health > 0)
			{
				fuse[4].Health -= damageFuse;
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
		}
	}
	app->draw(fuse1);
	app->draw(fuse2);
	app->draw(fuse3);
	app->draw(fuse4);
	app->draw(fuse5);
	//app->draw(sprite);
	app->draw(spotlight1);
	app->draw(spotlight2);
	app->draw(spotlight3);
	app->draw(healthBarSprite);
	Sprite.drawTo(app);
	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
