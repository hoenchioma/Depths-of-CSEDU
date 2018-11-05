#pragma once

/*
	Accessory class for Grid to load and store maze structures
*/

typedef std::vector <std::vector <bool>> BoolMatrix;

class Maze
{
public:
	Maze() {}
	Maze(const char* fileName) { loadFromFile(fileName); }
	Maze(const std::vector <std::vector <int>> & arr) { Init(arr); }
	~Maze() {}

	// load maze from file
	// maze is represented as a several lines of strings of characters where each line represents a row
	// "#" means blocked or wall, "." means free
	// WARNING: maze size cannot excede 3000x3000
	void loadFromFile(const char* fileName);

	// initialize the maze with a vector of int vectors
	// 1 means blocked or wall, 0 means free
	void Init(const std::vector <std::vector <int>> & arr);

	// not yet implemented :'(
	void generate();

	// overload the operators for direct acesss
	inline std::vector <bool>& operator[] (const size_t index) { return arr[index]; }

private:
	// using vector <bool> for space efficiency (each bool takes 1 bit only)
	BoolMatrix arr;
};

