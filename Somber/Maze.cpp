#include "pch.h"
#include "Maze.h"

#include <fstream>

using namespace std;
using namespace sf;

// Maximum size of row in maze
#define MAX_BUFF 3000

void Maze::loadFromFile(const char* fileName)
{
	ifstream file;
	char str[MAX_BUFF];
	file.open(fileName, ios::in);
	this->arr.clear();
	while (file.getline(str, MAX_BUFF))
	{
		vector <bool> temp;
		for (int i = 0; str[i]; i++)
		{
			if (str[i] == '#') temp.emplace_back(true);
			else if (str[i] == '.') temp.emplace_back(false);
		}
		arr.emplace_back(temp);
	}
	file.close();
}

void Maze::Init(const std::vector<std::vector<int>>& arr)
{
	this->arr.clear();
	for (const auto& i : arr)
	{
		vector <bool> temp;
		for (const auto& j : i) temp.emplace_back(j);
		this->arr.emplace_back(temp);
	}
}

void Maze::generate()
{
}
