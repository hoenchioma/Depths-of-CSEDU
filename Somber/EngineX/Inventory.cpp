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
	for (const auto& i : intVal) file << i.first.c_str() << " " << i.second << "\n";
	for (const auto& i : doubleVal) file << i.first.c_str() << " " << i.second << "\n";
	file.close();
}

bool Inventory::loadFromFile(const char * fileName)
{
	ifstream file;
	file.open(fileName, ios::in);

	intVal.clear();
	doubleVal.clear();

	char sstr[100];

	int intValSize, doubleValSize;
	//std::string temp;
	if (!(file >> intValSize >> doubleValSize)) return false;

	cout << "mew" << endl;

	for (int i = 0; i < intValSize; i++)
	{
		int val;
		if (!(file >> sstr >> val)) return false;
		intVal.insert({ std::string(sstr), val });
	}
	for (int i = 0; i < doubleValSize; i++)
	{
		double val;
		if (!(file >> sstr >> val)) return false;
		doubleVal.insert({ std::string(sstr), val });
	}

	file.close();

	/*FILE* file;
	fopen_s(&file, fileName, "r");

	intVal.clear();
	doubleVal.clear();

	char str[100];

	int m, n;
	fscanf_s(file, "%d %d ", &m, &n);
	for (int i = 0; i < m; i++)
	{
		int temp;
		fscanf_s(file, "%s %d ", str, &temp);
		intVal.insert({ std::string(str), temp });
	}
	for (int i = 0; i < n; i++)
	{
		double temp;
		fscanf_s(file, "%s %lf ", str, &temp);
		doubleVal.insert({ std::string(str), temp });
	}
	fclose(file);*/

	return true;
}
