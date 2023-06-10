#include "ListOfLists.h"
#include <iostream>
ListOfLists::ListOfLists(int numOfLists)
{
    lists = (DoubleLinkedList**)malloc(sizeof (DoubleLinkedList*) * numOfLists);
    for (int i = 0; i < numOfLists; i++) {
        lists[i] = new DoubleLinkedList();
    }
    size = numOfLists;
}

ListOfLists::~ListOfLists()
{
    delete[] lists;
}

void ListOfLists::addToList(int list, int val)
{
    
    if (list >= size) {
        std::cout << "List index out of range.\n";
        return;
    }
    //std::cout << "Adding " << val << " to " << list << " of size " << lists[list]->getSize() << "\n";
    lists[list]->addLast(val);
    //std::cout << "New size: " << lists[list]->getSize() << "\n";
}

int ListOfLists::getFromList(int list, int index)
{
    if (list >= size) return -1;
    return lists[list]->get(index);

}

DoubleLinkedList* ListOfLists::getList(int list)
{
    return lists[list];
}

void ListOfLists::print()
{
    for (int i = 0; i < size; i++) {
        lists[i]->print();
        std::cout << std::endl;
    }
}

int ListOfLists::getSize()
{
    return size;
}
