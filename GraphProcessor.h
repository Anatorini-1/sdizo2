#pragma once
#include "AdjacencyList.h"
#include "IncidenceMatrix.h"
#include "DoubleLinkedList.h"

class GraphProcessor
{
public:
	static IncidenceMatrix* PrimMST(IncidenceMatrix* g); // DONE
	static IncidenceMatrix* KruskalMST(IncidenceMatrix* g); //DONE
	static DoubleLinkedList* pathDijkstra(IncidenceMatrix* g, int from, int to); //DONE
	static DoubleLinkedList* pathBellmanFord(IncidenceMatrix* g, int from, int to);
	static IncidenceMatrix* maxFlowFordFulkerson(IncidenceMatrix* g);


	static AdjacencyList* PrimMST(AdjacencyList* g); //DONE
	static AdjacencyList* KruskalMST(AdjacencyList* g); //DONE
	static DoubleLinkedList* pathDijkstra(AdjacencyList* g, int from, int to); //DONE
	static DoubleLinkedList* pathBellmanFord(AdjacencyList* g, int from, int to);
	static AdjacencyList* maxFlowFordFulkerson(AdjacencyList* g);




};

