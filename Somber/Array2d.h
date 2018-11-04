#pragma once

/*
	A custom implementation of a dynamic 2d array
*/
#include "GridPoint.h"

#include <cassert>
#include <algorithm>

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

	//T* operator[] (size_t index);
	void fill(T val);

	inline T& at(int y, int x);
	inline T& at(GridPoint a) { return at(a.y, a.x); }

	inline size_t sizeX() { return size_x; }
	inline size_t sizeY() { return size_y; }

private:
	T* arr;

	size_t size_x;
	size_t size_y;

	size_t size;
};


template<class T>
Array2d<T>::Array2d(size_t y, size_t x)
{
	Init(y, x);
}

template<class T>
Array2d<T>::Array2d(size_t y, size_t x, T val)
{
	Init(y, x, val);
}

template<class T>
Array2d<T>::~Array2d()
{
	delete[] arr;
}

template<class T>
void Array2d<T>::Init(size_t y, size_t x)
{
	size_y = y;
	size_x = x;

	size = y * x;
	
	arr = new T[y * x];
}

template<class T>
void Array2d<T>::Init(size_t y, size_t x, T val)
{
	Init(y, x);
	fill(val);
}

template<class T>
void Array2d<T>::fill(T val)
{
	std::fill(arr, arr + size, val);
}

template<class T>
inline T & Array2d<T>::at(int y, int x)
{
	if (!(y >= 0 && y < size_y && x >= 0 && x < size_x))
		throw std::out_of_range("Array index out of range");
	return arr[y * size_x + x];
}


