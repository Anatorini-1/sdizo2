//
// Created by Marcin on 09.04.2023.
//

#ifndef SDIZO1_DOUBLELINKEDLIST_H
#define SDIZO1_DOUBLELINKEDLIST_H
#include <string>
#include <functional>
class DoubleLinkedList {

public:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };
private:
    Node* head;
    Node* tail;
    
public:
    int len;
    void addFirst(int elem);
    void addLast(int elem);
    void addAtIndex(int index, int elem);
    void delFirst();
    void delLast();
    void delIndex(int index);
    void delValue(int value);
    int find(int val);
    int get(int index);
    void loadFromFile(std::string path);
    DoubleLinkedList();
    ~DoubleLinkedList();
    void print();
    bool isEmpty();
    int findMin();
    int findMinIndex();
    void forEach(std::function<void(int)>&& lambda);
    int getSize();
    void copy(DoubleLinkedList* from);
};


#endif //SDIZO1_DOUBLELINKEDLIST_H