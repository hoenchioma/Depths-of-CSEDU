#pragma once

#include <map>

class Inventory
{
public:
	Inventory();
	~Inventory();

	std::map <std::string, int> intVal;
	std::map <std::string, double> doubleVal;

	void saveToFile(const char* fileName);
	bool loadFromFile(const char* fileName);
};
