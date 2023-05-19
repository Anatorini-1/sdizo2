//
// Created by Marcin on 09.04.2023.
//

#include "Array.h"
#include <iostream>
#include <fstream>
void Array::addFirst(int elem) {
    int* newData = new int[len + 1];
    newData[0] = elem;
    for (int i = 0; i < len; i++) {
        newData[i + 1] = data[i];
    }
    delete[] data;
    data = newData;
    len++;

}

void Array::addLast(int elem) {
    int* newData = new int[len + 1];
    for (int i = 0; i < len; i++) {
        newData[i] = data[i];
    }
    newData[len] = elem;
    delete[] data;
    data = newData;
    len++;
}

void Array::addAtIndex(int index, int elem) {
    int* newData = new int[len + 1];
    for (int i = 0; i < index; i++) {
        newData[i] = data[i];
    }
    newData[index] = elem;
    for (int i = index; i < len; i++) {
        newData[i + 1] = data[i];
    }
    delete[] data;
    data = newData;
    len++;
}

void Array::delFirst() {
    if (len == 0) {
        return;
    }
    int* newData = new int[len - 1];
    for (int i = 0; i < len - 1; i++) {
        newData[i] = data[i + 1];
    }
    delete[] data;
    data = newData;
    len--;

}

void Array::delLast() {
    if (len == 0) {
        return;
    }
    int* newData = new int[len - 1];
    for (int i = 0; i < len - 1; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    len--;

}

void Array::delIndex(int index) {
    if (len == 0 || index >= len) {
        return;
    }
    int* newData = new int[len - 1];
    for (int i = 0; i < index; i++) {
        newData[i] = data[i];
    }
    for (int i = index; i < len - 1; i++) {
        newData[i] = data[i + 1];
    }
    delete[] data;
    data = newData;
    len--;
}

void Array::delValue(int value) {
    int index = find(value);
    if (index != -1) {
        delIndex(index);
    }
}

int Array::find(int val) {
    for (int i = 0; i < len; i++) {
        if (data[i] == val) {
            return i;
        }
    }
    return -1;
}

int Array::operator[](int index) {
    return data[index];
}

Array::Array() {
    data = new int[0];
    len = 0;
}

Array::~Array() {
    delete[] data;
}

void Array::print() {
    std::cout << '[';
    for (int i = 0; i < len; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << ']' << std::endl;
}

void Array::fill(int size, int val) {
    delete[] data;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = val;
    }
    len = size;

}

int Array::get(int index)
{
    if (index >= len) return INT_MIN;
    return data[index];
}

void Array::set(int index, int val)
{
    if (index >= len) return;
    data[index] = val;
}

void Array::loadFromFile(std::string path) {
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

bool Array::isEmpty()
{
    return len == 0;
}
