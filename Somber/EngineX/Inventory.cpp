#include "Inventory.h"

#include <iostream>
#include <fstream>

using namespace std;

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

void Inventory::saveToFile(const char * fileName)
{
	ofstream file;
	file.open(fileName, ios::out);
	file << intVal.size() << " " << doubleVal.size() << "\n";
	for (const auto& i : intVal) file << i.first << " " << i.second << "\n";
	for (const auto& i : doubleVal) file << i.first << " " << i.second << "\n";
	file.close();
}

bool Inventory::loadFromFile(const char * fileName)
{
	ifstream file;
	file.open(fileName, ios::in);

	intVal.clear();
	doubleVal.clear();

	int intValSize, doubleValSize;
	std::string temp;
	if (file >> intValSize >> doubleValSize) return false;

	for (int i = 0; i < intValSize; i++)
	{
		int val;
		if (file >> temp >> val) return false;
		intVal.insert({ temp, val });
	}
	for (int i = 0; i < doubleValSize; i++)
	{
		double val;
		if (file >> temp >> val) return false;
		doubleVal.insert({ temp, val });
	}

	file.close();
	return true;
}
