#pragma once
#include "Matrix.h"
#include <iostream>
class IncidenceMatrix :
    public Matrix
{
public:
    IncidenceMatrix(int connections, int nodes);
    ~IncidenceMatrix();
    bool addEdge(int from, int to, int cost);
    int getEdge(int from, int to);

private:
    int connectionCounter;

};

