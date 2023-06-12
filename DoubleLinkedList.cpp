//
// Created by Marcin on 09.04.2023.
//

#include "DoubleLinkedList.h"
#include <iostream>
#include <fstream>
void DoubleLinkedList::addFirst(int elem) {
    if (head == 0) {
        head = new Node;
        head->value = elem;
        head->next = 0;
        head->prev = 0;
        tail = head;
        len = 1;
    }
    else {
        Node* temp = new Node;
        temp->value = elem;
        temp->next = head;
        temp->prev = 0;
        head->prev = temp;
        head = temp;
        len++;
    }
}

void DoubleLinkedList::addLast(int elem) {
  
    if (head == 0) {
        head = new Node;
        head->value = elem;
        head->next = 0;
        head->prev = 0;
        tail = head;
        len = 1;
    }
    else {
        Node* temp = new Node;
        temp->value = elem;
        temp->next = 0;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        len++;
    }
}

void DoubleLinkedList::addAtIndex(int index, int elem) {
    if (index == 0) {
        addFirst(elem);
    }
    else if (index == len) {
        addLast(elem);
    }
    else {
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            if (temp == 0) {
                break;
            }
            temp = temp->next;
        }
        Node* newNode = new Node;
        newNode->value = elem;
        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
        len++;
    }
}

void DoubleLinkedList::delFirst() {
    if (head != 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        len--;
    }

}

void DoubleLinkedList::delLast() {
    if (head != 0) {
        if (head == tail) {
            delete head;
            head = 0;
            tail = 0;
            len = 0;
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        temp->prev->next = 0;
        len--;
        delete temp;
    }

}

void DoubleLinkedList::delIndex(int index) {
    if (head == nullptr || index > len) {
        return;
    }
    if (index == 0) return delFirst();
    if (index == len - 1) return delLast();

    Node* temp = head;
    for (int i = 0; i < index; i++) {
        if (temp == nullptr) {
            return;
        }
        temp = temp->next;
    }


    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    if (temp->next != nullptr) {
         temp->next->prev = temp->prev;
    }
    len--;
    delete temp;
}

void DoubleLinkedList::delValue(int value) {
    int index = find(value);
    if (index != -1) {
        delIndex(index);
    }
}

int DoubleLinkedList::find(int val) {
    int index = 0;
    Node* temp = head;
    while (temp != 0) {
        if (temp->value == val) {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}

int DoubleLinkedList::get(int index)
{
    if (index >= len || index < 0) {
        std::cout << "Attempting to read index [" << index << "] from list of size [" << len << "]. Returning -1.\n";
        return -1;
    };
    Node* tmp = head;
    while (index--) tmp = tmp->next;
    return tmp->value;
}



DoubleLinkedList::DoubleLinkedList() {
    head = 0;
    tail = 0;
    len = 0;
}

DoubleLinkedList::~DoubleLinkedList() {
    while (head != 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void DoubleLinkedList::print() {
    Node* temp = head;
    while (temp != 0) {
        std::cout <<"(" << temp->value << ")";
        if (temp->next != 0) std::cout << "->";
        temp = temp->next;
    }
}

bool DoubleLinkedList::isEmpty()
{
    return len == 0;
}

int DoubleLinkedList::findMin()
{
    Node* temp = head;
    if (temp == 0) return -1;
    int min = INT_MAX;
    while (temp != 0) {
        if (temp->value < min) min = temp->value;
        temp = temp->next;
    }
    return min;
}

int DoubleLinkedList::findMinIndex()
{
    Node* temp = head;
    if (temp == 0) return -1;
    int min = INT_MAX;
    int minIndex = -1;
    int index = 0;
    while (temp != 0) {
        if (temp->value < min) {
            min = temp->value;
            minIndex = index;
        }
        temp = temp->next;
        index++;
    }
    return minIndex;
}

void DoubleLinkedList::forEach(std::function<void(int)>&& lambda)
{
    Node* tmp = head;
    while (tmp != 0) {
        lambda(tmp->value);
        tmp = tmp->next;
    }
}

int DoubleLinkedList::getSize()
{
    return len;
}

void DoubleLinkedList::copy(DoubleLinkedList* from)
{
    Node* tmp = from->head;
    Node* newNode;
    while (tmp != 0) {
        this->addLast(tmp->value);
        tmp = tmp->next;
    }
}

void DoubleLinkedList::loadFromFile(std::string path) {
    std::ifstream file;
    file.open(path);
    if (file.is_open()) {
        int value;
        while (file >> value) {
            addLast(value);
        }
    }
    file.close();

}