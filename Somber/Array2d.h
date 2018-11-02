#pragma once

/*
	A custom implementation of a dynamic 2d array
*/

#include <cassert>

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
	if (initialized)
	{
		delete[] ptr;
		delete[] arr;
	}
}

template<class T>
void Array2d<T>::Init(size_t y, size_t x)
{
	size_y = y;
	size_x = x;
	arr = new T[y * x];
	ptr = new T*[y];
	for (size_t i = 0, j = 0; i < y*x; i += x, j++)
		ptr[j] = &arr[i];

	initialized = true;
}

template<class T>
void Array2d<T>::Init(size_t y, size_t x, T val)
{
	Init(y, x);
	fill(val);
}

template<class T>
T* Array2d<T>::operator[](size_t index)
{
	if (!initialized) assert(false); // array not initialized
	if (index < 0 or index > size_y) assert(false); // index out of bounds
	return ptr[index];
}

template<class T>
void Array2d<T>::fill(T val)
{
	for (size_t i = 0; i < size_x * size_y; i++)
		arr[i] = val;
}

