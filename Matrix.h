#pragma once

#include "Array.h"
class Matrix
{
public:
	Matrix(int cols,int rows);
	void put(int col, int row, int val);
	int get(int col, int row);
	~Matrix();
	void print();
protected:
	Array* arr;
	int cols, rows;
};

