#pragma once
#include "Matrix.h"
#include <iostream>
#include "Graph.h"
#include <string>
class IncidenceMatrix : 
    public Matrix, public Graph
{
public:
    IncidenceMatrix(int connections, int nodes,bool directional = true);
    ~IncidenceMatrix();
    bool addEdge(int from, int to, int cost) override;
    int getEdge(int from, int to) override;
    void print() override;
    DoubleLinkedList* getVertices() override;
    DoubleLinkedList* getAdjecentVertices(int v, bool directional) override;
    int verticesCount();
    int edgesCount();
    edge* getEdges();
private:
    int connectionCounter;
    bool directional = true;
};

