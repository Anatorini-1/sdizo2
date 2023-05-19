//
// Created by Marcin on 09.04.2023.
//

#ifndef SDIZO1_DOUBLELINKEDLIST_H
#define SDIZO1_DOUBLELINKEDLIST_H
#include <string>

class DoubleLinkedList {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    int len;
public:
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
    int getSize();
};


#endif //SDIZO1_DOUBLELINKEDLIST_H