#include "Walls.h"

// wallMap according to texture walltex.png
// mapping between different wall configurations to their recpective textures
static const std::map <const std::vector<bool>, int> wallMap =
{
	// order is right, left, up, down
		{{0, 0, 0, 0}, 10},
		{{0, 0, 0, 1}, 11},
		{{0, 0, 1, 0}, 0},
		{{0, 0, 1, 1}, 2},
		{{0, 1, 0, 0}, 13},
		{{0, 1, 0, 1}, 7},
		{{0, 1, 1, 0}, 9},
		{{0, 1, 1, 1}, 15},
		{{1, 0, 0, 0}, 12},
		{{1, 0, 0, 1}, 6},
		{{1, 0, 1, 0}, 8},
		{{1, 0, 1, 1}, 14},
		{{1, 1, 0, 0}, 1},
		{{1, 1, 0, 1}, 3},
		{{1, 1, 1, 0}, 4},
		{{1, 1, 1, 1}, 5}
};


void Walls::Init(Grid* grid, sf::Color color)
{
	if (!rects.empty()) rects.clear();
	if (!sprites.empty()) sprites.clear();

	this->grid = grid;

	sf::RectangleShape tempBox(sf::Vector2f(grid->BIT, grid->BIT));
	tempBox.setOrigin(grid->BIT / 2.0, grid->BIT / 2.0);
	tempBox.setFillColor(color);

	for (int j = 0; j < grid->sizeY; j++)
	{
		for (int i = 0; i < grid->sizeX; i++)
		{
			if (grid->at({ i, j }))
			{
				tempBox.setPosition(grid->toPoint({ i, j }));
				rects.push_back(tempBox);
			}
		}
	}
}

void Walls::Init(Grid * grid, sf::Texture& tex)
{
	if (!sprites.empty()) sprites.clear();
	if (!rects.empty()) rects.clear();

	this->grid = grid;

	sf::Sprite tempSp;
	tempSp.setTexture(tex);
	tempSp.setScale(0.5f, 0.5f);

	int eachSize = tex.getSize().x / 16;

	for (int j = 0; j < grid->sizeY; j++)
	{
		for (int i = 0; i < grid->sizeX; i++)
		{
			if (grid->at({ i, j }))
			{
				bool left = grid->isInside({ i - 1, j }) and grid->at({ i - 1, j });
				bool right = grid->isInside({ i + 1, j }) and grid->at({ i + 1, j });
				bool up = grid->isInside({ i, j - 1 }) and grid->at({ i, j - 1 });
				bool down = grid->isInside({ i, j + 1 }) and grid->at({ i, j + 1 });

				tempSp.setTextureRect(sf::IntRect(eachSize * wallMap.at({ right, left, up, down }), 0, eachSize, eachSize));
				tempSp.setOrigin(eachSize / 2.0, eachSize / 2.0);

				tempSp.setPosition(grid->toPoint({ i, j }));
				sprites.push_back(tempSp);
			}
		}
	}
}

void Walls::drawTo1(sf::RenderWindow * app, sf::Vector2f pos)
{
	secondDrawStart = 0;
	if (!rects.empty())
	{
		for (int i = 0; i < rects.size(); i++)
		{
			if (rects[i].getPosition().y > pos.y)
			{
				secondDrawStart = i;
				break;
			}
			app->draw(rects[i]);
		}
	}
	else if (!sprites.empty())
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites[i].getPosition().y > pos.y)
			{
				secondDrawStart = i;
				break;
			}
			app->draw(sprites[i]);
		}
	}
}

void Walls::drawTo2(sf::RenderWindow * app)
{
	if (!rects.empty())
	{
		for (int i = secondDrawStart; i < rects.size(); i++)
		{
			app->draw(rects[i]);
		}
	}
	else if (!sprites.empty())
	{
		for (int i = secondDrawStart; i < sprites.size(); i++)
		{
			app->draw(sprites[i]);
		}
	}
}