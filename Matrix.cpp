#include "Array.h"
#include <iostream>
#include <iomanip>
#include "Matrix.h"
using namespace std;
Matrix::Matrix(int connections, int nodes)
{
    this->arr = new Array();
    this->arr->fill(connections * nodes, 0);
    this->cols = connections;
    this->rows = nodes;

}

void Matrix::put(int col, int row, int val)
{
    //cout << "Setting [" << col << "," << row << "] to " << val << endl;
    this->arr->set(this->rows * col + row, val);
}



int Matrix::get(int col, int row)
{
    return this->arr->get(this->rows * col + row);
}

Matrix::~Matrix()
{
}

void Matrix::print()
{
    
    for (int i = 0; i < this->rows; i++) {
        cout << "[ ";
        for (int j = 0; j < this->cols; j++) {
            //cout << "'" << rows * j + i << "': ";
            cout.width(4);
           cout << right << arr->get(rows * j + i) << " ";
        }
        cout << "]\n";
    }
}
