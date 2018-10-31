#pragma once

template <class T>
class Array2d
{
public:
	Array2d() {};
	Array2d(size_t y, size_t x);
	Array2d(size_t y, size_t x, T val);
	~Array2d();

	void Init(size_t y, size_t x);
	void Init(size_t y, size_t x, T val);
	T* operator[] (size_t index);
	void fill(T val);

	inline size_t sizeX() { return size_x; }
	inline size_t sizeY() { return size_y; }

private:
	T* arr; // linear array that holds all the values
	T** ptr; // pointer array for indexing each row

	size_t size_x = 0;
	size_t size_y = 0;

	bool initialized = false;
};
