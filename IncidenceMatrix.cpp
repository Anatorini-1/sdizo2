#include "IncidenceMatrix.h"

IncidenceMatrix::IncidenceMatrix(int connections, int nodes):Matrix(connections,nodes)
{
    this->connectionCounter = 0;
}

IncidenceMatrix::~IncidenceMatrix()
{
}

bool IncidenceMatrix::addEdge(int from, int to, int cost)
{
    if (connectionCounter >= this->cols) {
        return false;
    }
    this->put(connectionCounter, from, cost);
    this->put(connectionCounter, to, -1);
    this->connectionCounter++;
    return true;
}

int IncidenceMatrix::getEdge(int from, int to)
{
    for (int i = 0; i < connectionCounter; i++) {
        if (this->get(i, from) > 0 && this->get(i, to) == -1)
            return this->get(i, from);
        return -1;
    }
}

