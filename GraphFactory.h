#pragma once
#include <string>
#include "IncidenceMatrix.h"
#include "AdjacencyList.h"
#include <fstream>

class GraphFactory
{
public:
	static IncidenceMatrix* matrixGraph(int nodes, int density, bool directional);
	static AdjacencyList* listGraph(int nodes, int density,bool directional);
	static IncidenceMatrix* loadMatrixGraphFromFile(std::string filename);
	static AdjacencyList* loadListGraphFromFIle(std::string filename);
};

