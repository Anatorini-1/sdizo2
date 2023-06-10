#include <iostream>
#include "Array.h"
#include "Matrix.h"
#include "GraphFactory.h"
#include "ListOfLists.h"
#include "GraphProcessor.h"

using namespace std;

void tmp(DoubleLinkedList::Node* t) {
	cout << t->value;
}

int main()
{
	
	GraphFactory gf;
	GraphProcessor gp;
	string filename = "graph.txt";
	AdjacencyList* g = gf.litsDirectedGraph(20, 50);
	//IncidenceMatrix* g2 = gf.loadMatrixGraphFromFile(filename);
	IncidenceMatrix* g2 = gf.matrixDirectedGraph(20, 50);
	//g2->print();
	//gp.pathDijkstra(g, 0, 2)->print();
	cout <<"\nDijkstra:\n";
	gp.pathDijkstra(g2, 0, 2)->print();
	cout << "\nBellman-ford:\n";
	//gp.pathBellmanFord(g, 0, 2)->print();
	gp.pathBellmanFord(g2, 0, 2)->print();
	cout << endl;
	

}

