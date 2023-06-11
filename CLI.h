#pragma once
#include "Graph.h"
#include "AdjacencyList.h"
#include "IncidenceMatrix.h"
#include "GraphFactory.h"
#include "GraphProcessor.h"
#include <string>
class CLI
{
public:
	CLI();
	void run();
private:
	enum {MATRIX,LIST};
	int menu();
	int submenu(int x);
	Graph* graph = nullptr;
	int graphType;
	GraphFactory gf;
	GraphProcessor gp;
	string str;
	int v;
	int d;
	int from;
	int to;
};

