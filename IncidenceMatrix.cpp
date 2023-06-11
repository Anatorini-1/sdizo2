#include "IncidenceMatrix.h"
#include "DoubleLinkedList.h"
#include "Graph.h"
IncidenceMatrix::IncidenceMatrix(int connections, int nodes, bool directional) :Matrix(connections, nodes)
{
    this->connectionCounter = 0;
    this->directional = directional;
}

IncidenceMatrix::~IncidenceMatrix()
{
    delete arr;
}

bool IncidenceMatrix::addEdge(int from, int to, int cost)
{
    //Different behavior for directed and undirected graphs

    //Directed:
        if (this->directional) {
            if (connectionCounter >= this->cols) {
                return false;
            }
            this->put(connectionCounter, from, cost);
            this->put(connectionCounter, to, -1);
            this->connectionCounter++;
            return true;
        }

     //Undirected
        else {
            if (connectionCounter >= this->cols) {
                return false;
            }
            this->put(connectionCounter, from, cost);
            this->put(connectionCounter, to, cost);
            this->connectionCounter++;
            return true;
        }

    
}

int IncidenceMatrix::getEdge(int from, int to){
    

    //Different behavior for directed and undirected graphs

    //Directed:
        if (this->directional) {
        for (int i = 0; i < connectionCounter; i++) {
            if (this->get(i, from) > 0 && this->get(i, to) == -1) {
                return this->get(i, from);
            }
        }
        return -1;
    }
    //Undirected
        else {
            for (int i = 0; i < connectionCounter; i++) {
                if (get(i, from) > 0 && get(i, to) > 0) {
                    return get(i, from);
                }
            }
            return -1;
        }
}

void IncidenceMatrix::print()
{
    Matrix::print();
}

DoubleLinkedList* IncidenceMatrix::getVertices()
{
    DoubleLinkedList* res = new DoubleLinkedList();
    for (int i = 0; i < rows; i++)
        res->addLast(i);
    return res;
}

DoubleLinkedList* IncidenceMatrix::getAdjecentVertices(int v, bool directional)
{
    DoubleLinkedList* res = new DoubleLinkedList();
    for (int i = 0; i < rows; i++) {
        if (getEdge(v, i) != -1)
            res->addLast(i);
    }
    return res;
}

int IncidenceMatrix::verticesCount()
{
    return rows;
}

int IncidenceMatrix::edgesCount()
{
    return connectionCounter;
}

IncidenceMatrix::edge* IncidenceMatrix::getEdges()
{
    /*int x = 0;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (get(i,j) != 0) cout <<x++<<' ' << get(i, j) << ' ';
        }
        cout << endl;
    }*/
    edge* ret = new edge[connectionCounter];
    //cout << connectionCounter << endl;
    int tmp = 0;
    int from = -1;
    int to = -1;
    int weight = -1;
    int tmp2 = -1;
    for (int i = 0; i < cols; i++) {
        from = -1;
        to = -1;
        weight = -1;
        tmp2 = -1;
        for (int j = 0; j < rows; j++) {
            tmp2 = get(i, j);
            if (tmp2 == -1) {
                to = j;
            }
            if (tmp2 > 0){
                if (!directional && from != -1)
                    to = j;
                else
                    from = j;
                weight = tmp2;
            }
            if (from != -1 && to != -1) {
                ret[tmp++] = { from,to,weight };
                break;
            }
        }

    }
    return ret;
}

