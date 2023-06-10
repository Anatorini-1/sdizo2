#pragma once
#include "DoubleLinkedList.h"


using namespace std;

class Graph
{
public:
	struct edge {
		int from;
		int to;
		int weight;
		bool operator> (edge b) {
			return weight > b.weight;
		}
	};

	virtual bool addEdge(int from, int to, int weight) = 0;
	virtual int getEdge(int from, int to) = 0;
	virtual void print() = 0;
	virtual DoubleLinkedList* getVertices() = 0;
	virtual int verticesCount() = 0;
	virtual DoubleLinkedList* getAdjecentVertices(int v, bool directional=true) = 0;
	virtual edge* getEdges() = 0;
};

