#include "Array2d.h"

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
