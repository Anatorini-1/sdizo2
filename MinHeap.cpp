#include "MinHeap.h"
#include <iostream>

MinHeap::MinHeap(int maxSize)
{
	keys = new int[maxSize];
	values = new Graph::edge[maxSize];
	length = 0;
	maxLength = maxSize;
}

MinHeap::~MinHeap()
{
	delete[] values;
	delete[] keys;
}

void MinHeap::push(Graph::edge e)
{
	if (length == maxLength) {
		cout << "Heap at max capacity" << endl;
		return;
	}
	keys[length] = e.weight;
	values[length] = e;
	minHeapifyUp(length);
	length++;
}

Graph::edge MinHeap::top()
{
	return values[0];
}

Graph::edge MinHeap::pop()
{
	swap(0, length - 1);
	length--;
	minHeapifyDown(0);
	return values[length];
}

void MinHeap::print()
{
	cout << top().from << " -> " << top().to << ":"<<top().weight << endl;
	pop();
}

bool MinHeap::empty()
{
	return length == 0;
}

void MinHeap::minHeapifyUp(int start)
{
	if (start < 0) return;
	if (keys[start] < keys[parent(start)]) {
		swap(start, parent(start));
		minHeapifyUp(parent(start));
	}
}

void MinHeap::minHeapifyDown(int start)
{
	
	int l = leftChild(start);
	int r = rightChild(start);
	if (l == -1) {
		if (r == -1)
			return;
		if (keys[l] < keys[start]) {
			swap(start, rightChild(start));
			minHeapifyDown(rightChild(start));
		}
		}
		
	else {
		if (r == -1) {
			if (keys[l] < keys[start]){
			swap(start, leftChild(start));
			minHeapifyDown(leftChild(start));
		}
		}
		else {
			if (keys[l] < keys[r]) {
				if (keys[l] < keys[start]) {
					swap(start, leftChild(start));
					minHeapifyDown(leftChild(start));
				}
				
			}
			else {
				if (keys[r] < keys[start]) {
					swap(start, rightChild(start));
					minHeapifyDown(rightChild(start));
				}
				
			}
		}
	}

}

void MinHeap::swap(int k1, int k2)
{
	Graph::edge tmp = values[k1];
	int tmp2 = keys[k1];
	values[k1] = values[k2];
	keys[k1] = keys[k2];

	values[k2] = tmp;
	keys[k2] = tmp2;
}
