#pragma once
#include <ctime>
#include <Windows.h>
#include <iostream>
#include "AdjacencyList.h"
#include "IncidenceMatrix.h"
#include "GraphFactory.h"
#include "GraphProcessor.h"
#include "cstdlib"
#include <fstream>
#include <chrono>
using namespace std;
class Tester
{
public:
	void startCounter();
	double getCounter();
	Tester();
	~Tester();
	void testDijkstraMatrix();
	void testKruskalMatrix();
	void testPrimMatrix();
	void testBellmanFordMatrix();

	void testDijkstraList();
	void testKruskalList();
	void testPrimList();
	void testBellmanFordList();


private:
	__int64  CounterStart;
	double PCFreq;
	int* densities;
	int d;
	int* sizes;
	int s;
	std::chrono::steady_clock::time_point timeStamp;
	GraphFactory gf;
	GraphProcessor gp;
	ofstream file;
};

