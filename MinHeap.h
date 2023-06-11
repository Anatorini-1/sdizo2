#pragma once
#include "Graph.h"

using namespace std;
class MinHeap
{

public:
	MinHeap(int maxSize);
	~MinHeap();
	void push(Graph::edge e);
	Graph::edge top();
	Graph::edge pop();
	void print();
	bool empty();
private:
	int* keys;
	Graph::edge* values;
	void minHeapifyUp(int start);
	void minHeapifyDown(int start);
	int maxLength;
	int length;
	void swap(int k1, int k2);
	int parent(int x) {
		return (x-1) / 2;
	}
	int leftChild(int x) {
		if ((2 * x + 1) >= length) return -1;
		return 2 * x+1;
	}
	int rightChild(int x) {
		if ((2 * x + 2) >= length) return -1;
		return 2 * x + 2;
	}
};

