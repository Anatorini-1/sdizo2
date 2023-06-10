#include "AdjacencyList.h"
#include <iostream>
using namespace std;
AdjacencyList::AdjacencyList(int nodes)
{
    vertices = new ListOfLists(nodes);
    weights = new ListOfLists(nodes);
    size = nodes;
    edges = 0;
}

bool AdjacencyList::addEdge(int from, int to, int weight)
{
    vertices->addToList(from, to);
    weights->addToList(from, weight);
    edges++;
    return true;
}

int AdjacencyList::getEdge(int from, int to,bool directional)
{
    int index = vertices->getList(from)->find(to);
    if (!directional) {
        int index2 = vertices->getList(to)->find(from);
        if (index2 == -1) {
            if (index == -1) return -1;
            return weights->getFromList(from, index);;
        }
        int w1 = -1;
        if (index == -1) w1 = -1;
        else w1 = weights->getFromList(from, index);
        int w2 = weights->getFromList(to, index2);
        if (w1 == -1) return w2;
        if (index2 != -1 && w2 < w1) {
            return w2;
        }
        return w1;
    }
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
    if (!directional) {
        for (int i = 0; i < vertices->getSize(); i++) {
            if (i != v) {
                if (vertices->getList(i)->find(v) != -1)
                    res->addLast(i);
            }
        }
    }
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
    edge* res = new edge[edges];
    int tmp = 0;
    int weight = -1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) continue;
            weight = getEdge(i, j);
            if (weight != -1) {
                res[tmp++] = { i,j,weight };
            }
        }
    }
    return res;
}
