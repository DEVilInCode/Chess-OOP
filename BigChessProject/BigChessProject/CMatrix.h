#pragma once
#include <vector>

template<typename T>
class Matrix
{
public:
	Matrix(int row, int col);
	virtual ~Matrix();

	void print();
	T* operator[](int index);
private:
	int rows, cols;
	T** data;
};
