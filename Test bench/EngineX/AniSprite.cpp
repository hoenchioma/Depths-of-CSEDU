#include "AniSprite.h"

void AniSprite::setSpriteSheet(const sf::Texture & tex)
{
	_obj.setTexture(tex);
}

void AniSprite::addFrame(sf::IntRect rect)
{
	_frames.push_back(rect);

	if (_defaultSet) _obj.setTextureRect(_default); 
	else _obj.setTextureRect(_frames[_currentIndex]);
	//std::cerr << _frames.size() << std::endl;
}

void AniSprite::addSheet(dir direc, int width, int height, int in_x, int in_y)
{
	if (direc == horizontal)
	{
		for (int i = in_x, j = in_y; i <= _obj.getTexture()->getSize().x - width; i += width)
		{
			this->addFrame(sf::IntRect(i, j, width, height));
		}
	}
	else
	{
		for (int i = in_x, j = in_y; j <= _obj.getTexture()->getSize().y - height; j += height)
		{
			this->addFrame(sf::IntRect(i, j, width, height));
		}
	}
	//std::cerr << _frames.size() << std::endl;
}

void AniSprite::setDefault(sf::IntRect rect)
{
	_default = rect;
	_defaultSet = true;
}

sf::Vector2f AniSprite::getSize() const
{
	return sf::Vector2f(_obj.getGlobalBounds().width, _obj.getGlobalBounds().height);
}

sf::FloatRect AniSprite::getGlobalBounds() const
{
	return _obj.getGlobalBounds();
}

sf::IntRect AniSprite::getTextureRect() const
{
	return _obj.getTextureRect();
}

void AniSprite::drawTo(sf::RenderWindow * app)
{
	if (play)
	{
		if (_clock.getElapsedTime().asSeconds() >= _delay)
		{
			_currentIndex = (_currentIndex + 1) % _frames.size();
			_obj.setTextureRect(_frames[_currentIndex]);
			_clock.restart();
		}
	}
	else if (_defaultSet) _obj.setTextureRect(_default);

	app->draw(_obj);
}
