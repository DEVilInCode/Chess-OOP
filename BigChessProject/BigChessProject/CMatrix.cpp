#include <iostream>
#include "CMatrix.h"

template<typename T>
Matrix<T>::Matrix(int row, int col):rows(row), cols(col)
{
	data = new T * [row];
	for (size_t i = 0; i < row; i++)
	{
		data[i] = new T[col];
	}
}

template<typename T>
Matrix<T>::~Matrix()
{
	delete[] data;
}

template<typename T>
T* Matrix<T>::operator[](int index)
{
	return &(data[index * rows]);
}