#include <iostream>
#include "Array.h"
#include "Matrix.h"
#include "GraphFactory.h"
#include "ListOfLists.h"
#include "GraphProcessor.h"
#include <cstdio>
using namespace std;

void tmp(DoubleLinkedList::Node* t) {
	cout << t->value;
}

int main()
{
	
	GraphFactory gf;
	GraphProcessor gp;
	string filename = "graph.txt";
	auto* g = gf.litsGraph(5, 100,true);
	g->print();
	gp.pathBellmanFord(g, 2, 3)->print();


}

