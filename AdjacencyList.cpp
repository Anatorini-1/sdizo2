#include "AdjacencyList.h"
#include <iostream>
#include <iomanip>
using namespace std;
AdjacencyList::AdjacencyList(int nodes,bool directional)
{
    vertices = new ListOfLists(nodes);
    weights = new ListOfLists(nodes);
    size = nodes;
    edges = 0;
    this->directional = directional;
}

AdjacencyList::~AdjacencyList()
{
    delete vertices;
    delete weights;
}

bool AdjacencyList::addEdge(int from, int to, int weight)
{
    if (from == to) {
        cout << "Cant add and edge from " << from << " to " << to << endl;
        return false;
    }
    vertices->addToList(from, to);
    weights->addToList(from, weight);
    edges++;
    if (!directional) {
        vertices->addToList(to, from);
        weights->addToList(to, weight);
    }
    return true;
}

int AdjacencyList::getEdge(int from, int to)
{
    int index = vertices->getList(from)->find(to);
    if (index == -1) return -1;
    return weights->getFromList(from, index);
}

void AdjacencyList::print()
{
    for (int i = 0; i < size; i++) {
        cout << "(" <<setw(2)<< i << ") : [ ";
        DoubleLinkedList* v = vertices->getList(i);
        DoubleLinkedList* w = weights->getList(i);
        for (int j = 0; j < v->getSize(); j++) {
            cout << v->get(j) << "/" << w->get(j) << " ";
        }
        cout << "]\n";
    }
}

DoubleLinkedList* AdjacencyList::getVertices()
{
    int s = vertices->getSize();
    DoubleLinkedList* res = new DoubleLinkedList();
    for (int i = 0; i < s; i++) {
        res->addLast(i);
    }
    return res;
}

DoubleLinkedList* AdjacencyList::getAdjecentVertices(int v, bool directional)
{
    DoubleLinkedList* res = new DoubleLinkedList();
    res->copy(vertices->getList(v));
    return res;

}

int AdjacencyList::verticesCount()
{
    return vertices->getSize();
}

int AdjacencyList::edgesCount()
{
    return edges;
}

AdjacencyList::edge* AdjacencyList::getEdges()
{
    edge* edges = new edge[this->edges];
    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) continue;
            if (!this->directional && i > j) continue;
            int weight = getEdge(i, j);
            if (weight > -1) {
                edges[index] = { i,j,weight };
                index++;
            }
        }
    }
    return edges;
}
