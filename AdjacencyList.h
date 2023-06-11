#pragma once
#include "ListOfLists.h"
#include "Graph.h"
#include <string>
#include "DoubleLinkedList.h"
#include "Array.h"
class AdjacencyList: public Graph
{

public:
	AdjacencyList(int nodes,bool directional=true);
	~AdjacencyList();
	bool addEdge(int from, int to, int weight) override;
	int getEdge(int from, int to) override;
	void print() override;
	DoubleLinkedList* getVertices() override;
	DoubleLinkedList* getAdjecentVertices(int v, bool directional) override;
	int verticesCount();

	int edgesCount();
	edge* getEdges();
private:
	int size;
	ListOfLists* vertices;
	ListOfLists* weights;
	int edges;
	bool directional;
};

