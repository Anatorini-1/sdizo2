#pragma once
class MinHeap
{

public:
	struct node {
		int key;
		int value;
	};
	void add(int key,int val);
	int get(int key);
	int getRoot();
	void init(int size);

private:
	node** arr;
	int len;
	int parent(int key);
	void swap(int k1, int k2);
	int index = 0;
	void heapify(int i);
};

