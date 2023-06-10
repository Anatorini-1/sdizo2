#pragma once
#include "DoubleLinkedList.h"

class ListOfLists
{
public:
	ListOfLists(int numOfLists);
	~ListOfLists();
	void addToList(int list, int val);
	int getFromList(int list, int index);
	DoubleLinkedList* getList(int list);
	void print();
	int getSize();
private:
	int size;
	DoubleLinkedList** lists;
};

