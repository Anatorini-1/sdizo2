#include "AdjacencyList.h"
#include <iostream>
using namespace std;
AdjacencyList::AdjacencyList(int nodes)
{
    vertices = new ListOfLists(nodes);
    weights = new ListOfLists(nodes);
    size = nodes;
}

void AdjacencyList::addEdge(int from, int to, int weight)
{
    vertices->addToList(from, to);
    weights->addToList(from, weight);
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
        cout << "(" << i << ") : [ ";
        DoubleLinkedList* v = vertices->getList(i);
        DoubleLinkedList* w = weights->getList(i);
        for (int j = 0; j < v->getSize(); j++) {
            cout << v->get(j) << "/" << w->get(j) << " ";
        }
        cout << "]\n";
    }
}
