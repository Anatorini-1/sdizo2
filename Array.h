#pragma once
//
// Created by Marcin on 09.04.2023.
//

#include <string>
class Array
{
private:
    int* data;
    int len;

public:
    void addFirst(int elem);
    void addLast(int elem);
    void addAtIndex(int index, int elem);
    void delFirst();
    void delLast();
    void delIndex(int index);
    void delValue(int value);
    void fill(int size, int val);
    int get(int index);
    void set(int index, int val);
    int find(int val);
    int operator[](int index);
    void loadFromFile(std::string path);
    bool isEmpty();
    Array();
    ~Array();
    void print();
};




