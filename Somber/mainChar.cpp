#include "MainChar.h"

using namespace sf;
using namespace std;

const float charTexOffsetX = 15;
const float charTexOffsetY = 10;

void MainChar::Init(sf::Texture& tex, float delay, float vel)
{
	this->vel = vel;
	
	int bitx = tex.getSize().x / 3;
	int bity = tex.getSize().y / 4;

	for (auto& i : ani)
	{
		i.setSpriteSheet(tex);
		i.setDelay(delay);
		i.pause();
	}
	ani[0].addSheet(AniSprite::dir::horizontal, bitx, bity, 0, bity);
	ani[0].setDefault(IntRect(bitx, bity, bitx, bity));

	ani[1].addSheet(AniSprite::dir::horizontal, bitx, bity, 0, bity * 2);
	ani[1].setDefault(IntRect(bitx, bity * 2, bitx, bity));

	ani[2].addSheet(AniSprite::dir::horizontal, bitx, bity, 0, bity * 3);
	ani[2].setDefault(IntRect(bitx, bity * 3, bitx, bity));

	ani[3].addSheet(AniSprite::dir::horizontal, bitx, bity, 0, 0);
	ani[3].setDefault(IntRect(bitx, 0, bitx, bity));

	// set the origin of the sprite to the centre
	setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f);

	// initializing polygon
	setPolyInit();
}

void MainChar::setScale(float x, float y)
{
	for (auto& i : ani)
	{
		i.setScale(x, y);
	}
	// resizing polygon after setScale
	setPoly();
}

void MainChar::setScale(sf::Vector2f vec)
{
	for (auto& i : ani)
	{
		i.setScale(vec);
	}
	// resizing polygon after setScale
	setPoly();
}

sf::Vector2f MainChar::getPosition() const
{
	return ani[0].getPosition();
}

sf::Vector2f MainChar::getSize() const
{
	return ani[0].getSize();
}

sf::IntRect MainChar::getTextureRect() const
{
	return ani[0].getTextureRect();
}

sf::FloatRect MainChar::getGlobalBounds() const
{
	return ani[0].getGlobalBounds();
}

void MainChar::setPosition(sf::Vector2f vec)
{
	for (auto& i : ani) i.setPosition(vec);
	// resetting polygon after position change
	setPoly();
}

void MainChar::setPosition(float x, float y)
{
	for (auto& i : ani) i.setPosition(x, y);
	// resetting polygon after position change
	setPoly();
}

void MainChar::setOrigin(sf::Vector2f vec)
{
	for (auto& i : ani) i.setOrigin(vec);
}

void MainChar::setOrigin(float x, float y)
{
	for (auto& i : ani) i.setOrigin(x, y);
}

void MainChar::setColor(const sf::Color& color)
{
	for (auto& i : ani) i.setColor(color);
}

void MainChar::moveOn(Direction direc)
{
	running = true;
	state = direc;
	ani[state].resume();
}

void MainChar::moveOff()
{
	running = false;
	ani[state].pause();
}

void MainChar::keyHandle()
{
	bool isOneKeyPressed = false;
	for (const auto& i : KeyArr)
	{
		if (Keyboard::isKeyPressed(i))
		{
			this->moveOn(KeyMap.at(i));
			diagOn = false; 
			// sets to false so that it can be set to true if diagonal movement takes place
			isOneKeyPressed = true;
			break;
		}
	}
	
	if (!isOneKeyPressed) this->moveOff(); // if no key is pressed stop moving
	else
	{
		// handle diagonal movement cases
		for (const auto& i : DiagArr)
		{
			if (Keyboard::isKeyPressed(revKeyMap.at(i.first)) && Keyboard::isKeyPressed(revKeyMap.at(i.second)))
			{
				diagOn = true;
				state_diag = i;
				state = i.first; // animation only shows left or right
				break;
			}
		}
	}
}

void MainChar::setBoundary(sf::Vector2f topLeft, sf::Vector2f size)
{
	setBoundary(topLeft.x, topLeft.y, size.x, size.y);
}

void MainChar::setBoundary(sf::FloatRect bound)
{
	setBoundary(bound.left, bound.top, bound.width, bound.height);
}

void MainChar::setBoundary(float left, float top, float width, float height)
{
	this->dontMoveIf([=]() {return this->getPosition().x < left or this->getPosition().x > left + width; });
	this->dontMoveIf([=]() {return this->getPosition().y < top or this->getPosition().y > top + height; });
}

bool MainChar::intersects(const Polygon & a)
{
	return this->getPoly().intersects(a);
}

void MainChar::dontIntersect(Polygon * a)
{
	offLimits.push_back(a);
}

void MainChar::dontIntersect(Polygon a)
{
	offLimits_hard.push_back(a);
}

void MainChar::dontMoveIf(std::function<bool(void)> comp)
{
	dontDo.push_back(comp);
}

void MainChar::update(float dt)
{
	if (running)
	{
		if (diagOn)
		{
			for (auto& i : ani)
			{
				i.move(
					dt * vel * invSqrtTwo * dirAr[state_diag.first][0], 
					dt * vel * invSqrtTwo * dirAr[state_diag.first][1]
				);
				i.move(
					dt * vel * invSqrtTwo * dirAr[state_diag.second][0], 
					dt * vel * invSqrtTwo * dirAr[state_diag.second][1]
				);

				// vx = vel cos 45 = vel * 1/sqrt(2)
				// vy = vel sin 45 = vel * 1/sqrt(2)

			}

			// updates the polygon after each movement
			setPoly();

			// if intersection takes place revert the movement and break the loop
			if (any_of(offLimits.begin(), offLimits.end(), [&](auto i) {return poly.intersects(*i); })
			or any_of(offLimits_hard.begin(), offLimits_hard.end(), [&](auto& i) {return poly.intersects(i); })
			or any_of(dontDo.begin(), dontDo.end(), [](auto i) {return i(); })
			)
			{
				float oppVel = -vel;
				for (auto& i : ani)
				{
					i.move(
						dt * oppVel * invSqrtTwo * dirAr[state_diag.first][0],
						dt * oppVel * invSqrtTwo * dirAr[state_diag.first][1]
					);
					i.move(
						dt * oppVel * invSqrtTwo * dirAr[state_diag.second][0],
						dt * oppVel * invSqrtTwo * dirAr[state_diag.second][1]
					);
				}
			}
		}
		else
		{
			for (auto& i : ani)
				i.move(dt * vel * dirAr[state][0], dt * vel * dirAr[state][1]);

			// updates the polygon after each movement
			setPoly();

			// if intersection takes place revert the movement and break the loop
			if (any_of(offLimits.begin(), offLimits.end(), [&](auto i) {return poly.intersects(*i); })
			or any_of(offLimits_hard.begin(), offLimits_hard.end(), [&](auto& i) {return poly.intersects(i); })
			or any_of(dontDo.begin(), dontDo.end(), [](auto i) {return i(); })
			)
			{
				float oppVel = -vel;
				for (auto& i : ani)
					i.move(dt * oppVel * dirAr[state][0], dt * oppVel * dirAr[state][1]);
			}
		}
	}
}

void MainChar::drawTo(sf::RenderWindow* app)
{
	ani[state].drawTo(app);
	//poly.draw(app);
}

void MainChar::setPolyInit()
{
	float left = getGlobalBounds().left + charTexOffsetX;
	float right = getGlobalBounds().left + getGlobalBounds().width - charTexOffsetX;
	float top = getGlobalBounds().top + charTexOffsetY;
	float bottom = getGlobalBounds().top + getGlobalBounds().height; 
	// not subtracting from bottom because the bottom part of texture has no gap

	poly.setPoints({
		{left, top},
		{left, bottom},
		{right, bottom},
		{right, top},
	});
}
void MainChar::setPoly()
{
	float left = getGlobalBounds().left + charTexOffsetX;
	float right = getGlobalBounds().left + getGlobalBounds().width - charTexOffsetX;
	float top = getGlobalBounds().top + charTexOffsetY;
	float bottom = getGlobalBounds().top + getGlobalBounds().height;
	// not subtracting from bottom because the bottom part of texture has no gap
	
	poly.vertex[0] = Point(left, top);
	poly.vertex[1] = Point(left, bottom);
	poly.vertex[2] = Point(right, bottom);
	poly.vertex[3] = Point(right, top);
	poly.setCentre();
	poly.sideSet();
}
