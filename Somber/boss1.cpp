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
	fuse[1].X = rand() % 1880 + 40;
	fuse[2].Y = rand() % 1040 + 40;
	fuse[3].X = rand() % 1880 + 40;
	fuse[4].Y = rand() % 1040 + 40;
	fuse[5].X = (windowWidth - fuseWidth) / 2;
	fuse[5].Y = (windowHeight - fuseHeight) / 2;
	sprite.setPointCount(4);
	sprite.setFillColor(sf::Color(0, 0, 255));
	spotlight1.setPointCount(50);
	spotlight2.setPointCount(50);
	spotlight3.setPointCount(50);
	spotlight1.setRadius(radiusSpotlight);
	spotlight2.setRadius(radiusSpotlight);
	spotlight3.setRadius(radiusSpotlight);
	fuse1.setPosition(Vector2f(fuseWidth, fuseHeight));
	fuse2.setPosition(Vector2f(fuseHeight,fuseWidth));
	fuse3.setPosition(Vector2f(fuseWidth, fuseHeight));
	fuse4.setPosition(Vector2f(fuseHeight,fuseWidth));
	fuse5.setPosition(Vector2f(fuseWidth, fuseHeight));

	// Initialize variables here
}

void boss1::Cleanup()
{
}

void boss1::Pause()
{
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
	// handle collision and other logic
	// update the sprites
	// use dt (interval between two frames) for framerate independent movement
}

void boss1::Draw(RenderWindow * app)
{
		sf::RectangleShape fuse1Bar(sf::Vector2f(fuse[1].Health, healthBar));
		sf::RectangleShape fuse2Bar(sf::Vector2f(fuse[2].Health, healthBar));
		sf::RectangleShape fuse3Bar(sf::Vector2f(fuse[3].Health, healthBar));
		sf::RectangleShape fuse4Bar(sf::Vector2f(fuse[4].Health, healthBar));
		sf::RectangleShape fuse5Bar(sf::Vector2f(fuse[5].Health, healthBar));
		sf::RectangleShape healthBarSprite(sf::Vector2f(spriteHealth, 40));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && spriteX >= speed) spriteX -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && spriteX <= windowWidth - spriteSize * 2 - speed)	spriteX += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && spriteY <= windowHeight - spriteSize * 2 - speed) spriteY += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && spriteY >= speed) spriteY -= speed;
		if ((fuse[1].X - range < spriteX && spriteX < fuse[1].X + fuseWidth + range) && (fuseDis - range < spriteY && spriteY < fuseDis + fuseHeight + range))  //   Fuse range thing
		{
			fuse1Bar.setPosition(fuse[1].X, fuseDis + fuseHeight);
			app->draw(fuse1Bar);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (fuse[1].Health > 0)
				{
					fuse[1].Health -= damageFuse;
				}
			}
		}
		else if ((windowWidth - fuseDis - range < spriteX && spriteX < windowWidth + range) && (fuse[2].Y - range < spriteY && spriteY < fuse[2].Y + fuseWidth + range))
		{
			fuse2Bar.setPosition(windowWidth - barDis - fuseHealth, fuse[2].Y);
			app->draw(fuse2Bar);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (fuse[2].Health > 0)
				{
					fuse[2].Health -= damageFuse;
				}
			}
		}
		else if ((fuse[3].X - range < spriteX && spriteX < fuse[3].X + fuseWidth + range) && (windowHeight - fuseDis - range < spriteY && spriteY < windowHeight - fuseDis + fuseHeight + range))
		{
			fuse3Bar.setPosition(fuse[3].X, windowHeight - fuseDis + barDis);
			app->draw(fuse3Bar);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (fuse[3].Health > 0)
				{
					fuse[3].Health -= damageFuse;
				}
			}
		}
		else if ((fuseDis - range < spriteX && spriteX < fuseDis + fuseWidth + range) && (fuse[4].Y - fuseHeight - range < spriteY && spriteY < fuse[4].Y + range))
		{
			fuse4Bar.setPosition(fuseDis - barDis, fuse[4].Y + barDis);
			app->draw(fuse4Bar);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (fuse[4].Health > 0)
				{
					fuse[4].Health -= damageFuse;
				}
			}
		}
		else if ((fuse[5].X - range < spriteX && spriteX < fuse[5].X + fuseWidth + range) && (fuse[5].Y - range < spriteY && spriteY < fuse[5].Y + fuseHeight + range))
		{
			fuse5Bar.setPosition(fuse[5].X, fuse[5].Y + barDis);
			app->draw(fuse5Bar);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (fuse[5].Health > 0)
				{
					fuse[5].Health -= damageFuse;
				}
			}
		}																																	//Fuse range thing
		if (spotlight1X > windowWidth)		spotlight1DirX = LEFT;
		else if (spotlight1X < (-1)*(diameterSpotlight + 50))			spotlight1DirX = RIGHT;
		if (spotlight1Y > windowHeight)	spotlight1DirY = UP;
		else if (spotlight1Y < (-1)*(diameterSpotlight + 50))			spotlight1DirY = DOWN;
		if (spotlight2X > windowWidth)	spotlight2DirX = LEFT;
		else if (spotlight2X < (-1)*(diameterSpotlight + 50))		spotlight2DirX = RIGHT;
		if (spotlight2Y > windowHeight)	spotlight2DirY = UP;
		else if (spotlight2Y < (-1)*(diameterSpotlight + 50))		spotlight2DirY = DOWN;
		if (spotlight3X > windowWidth)	spotlight3DirX = LEFT;
		else if (spotlight3X < (-1)*(diameterSpotlight + 50))		spotlight3DirX = RIGHT;
		if (spotlight3Y > windowHeight)	spotlight3DirY = UP;
		else if (spotlight3Y < (-1)*(diameterSpotlight + 50))		spotlight3DirY = DOWN;
		if ((centreDis(spotlight1X+radiusSpotlight, spotlight1Y+radiusSpotlight, spriteX+spriteSize, spriteY+spriteSize) < spotlightDamageRange) || (centreDis(spotlight2X + radiusSpotlight, spotlight2Y + radiusSpotlight, spriteX + spriteSize, spriteY + spriteSize) < spotlightDamageRange) || (centreDis(spotlight3X + radiusSpotlight, spotlight3Y + radiusSpotlight, spriteX + spriteSize, spriteY + spriteSize) < spotlightDamageRange))	spriteHealth -= lightDamage;
		if (spriteHealth < 0) gameOver = 1;							//GAME OVER FLAG
		spotlight1X += speedSpotlight * spotlight1DirX;
		spotlight1Y += speedSpotlight * spotlight1DirY;
		spotlight2X += speedSpotlight * spotlight2DirX;
		spotlight2Y += speedSpotlight * spotlight2DirY;
		spotlight3X += speedSpotlight * spotlight3DirX;
		spotlight3Y += speedSpotlight * spotlight3DirY;
		spotlight1.setPosition(spotlight1X, spotlight1Y);
		spotlight2.setPosition(spotlight2X, spotlight2Y);
		spotlight3.setPosition(spotlight3X, spotlight3Y);
		sprite.setPosition(spriteX, spriteY);
		fuse1.setPosition(fuse[1].X, fuseDis);
		fuse2.setPosition(windowWidth - fuseDis, fuse[2].Y);
		fuse3.setPosition(fuse[3].X, windowHeight - fuseDis);
		fuse4.setPosition(fuseDis, fuse[4].Y);
		fuse5.setPosition(fuse[5].X, fuse[5].Y);
		fuse2Bar.setPosition(windowWidth - barDis - fuseHealth, fuse[2].Y);
		fuse3Bar.setPosition(fuse[3].X, windowHeight - fuseDis + barDis);
		fuse4Bar.setPosition(fuseDis - barDis, fuse[4].Y);
		healthBarSprite.setFillColor(sf::Color(255, 0, 0));
		app->draw(fuse1);
		app->draw(fuse2);
		app->draw(fuse3);
		app->draw(fuse4);
		app->draw(fuse5);
		app->draw(sprite);
		app->draw(spotlight1);
		app->draw(spotlight2);
		app->draw(spotlight3);
		app->draw(healthBarSprite);
	// draw to screen
	// note: use app->draw() instead of app.draw() as it is a pointer
}
