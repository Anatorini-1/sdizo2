#pragma once
#include "IncidenceMatrix.h"
#include "AdjacencyList.h"
#include <fstream>


class GraphFactory
{
public:
	static IncidenceMatrix* matrixDirectedGraph(int nodes, int density);
	static AdjacencyList* litsDirectedGraph(int nodes, int density);
};
