#pragma once
#include "ListOfLists.h"

class AdjacencyList
{

public:
	AdjacencyList(int nodes);
	void addEdge(int from, int to, int weight);
	int getEdge(int from, int to);
	void print();
private:
	int size;
	ListOfLists* vertices;
	ListOfLists* weights;
};

