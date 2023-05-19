#include "GraphFactory.h"
#include "IncidenceMatrix.h"
#include <cstdlib>
#include <math.h>
#include "Array.h"
#include <iostream>
using namespace std;
IncidenceMatrix* GraphFactory::matrixDirectedGraph(int nodes, int density)
{

    //In a directed graph, the total number of possible 
    //edges is equal to nodes*(nodes-1)
    int maxConnections = nodes * (nodes - 1);
    int connectionsToMake = maxConnections * density / 100;
    if (connectionsToMake < nodes - 1) {
        cout << "The graph of size " << nodes << " and density " << (float)density / 100.0f << "% can not be connected.\n";
        return nullptr;
    }

    IncidenceMatrix* m = new IncidenceMatrix(connectionsToMake, nodes);
    int connection = 0;
    /*
    Steps to generate a random, connected graph with given density:
        1. Create a random spanning tree connecting all nodes
            1.1 Pick a random node A 
            1.2 Mark A as visited
            1.3 while( there are unvisited nodes )
                1.3.1 pick a random node B from unvisited nodes
                1.3.2 connect A to B
                1.3.3 set A = B
                1.3.4 mark B as visited
        2. Randomly add edges untill desired density is reached
            2.1 while ( density < target density )
                2.2.1 Pick a random node A
                2.2.2 Pick a random node B
                2.2.3 If there is no edge A -> B
                    2.2.3.1 Create an edge A -> B with random weight
    */

    //1
    Array* U = new Array();
    for (int i = 0; i < nodes; i++)
        U->addLast(i);
    
    int A = U->get(rand() % nodes);
    int B;
    U->delValue(A);
    while (!U->isEmpty()) {
        B = U->get(rand() % (nodes - connection - 1));
        U->delValue(B);
        m->addEdge(A, B, rand() % 99 + 1);
        connection++;
        A = B;
    }
    //2
    while (connection < connectionsToMake) {
        int A = rand() % nodes;
        int B = rand() % nodes;
        if (m->getEdge(A, B) != -1) continue;
        m->addEdge(A, B, rand() % 99 + 1);
        connection++;
    }
    return m;
}

AdjacencyList* GraphFactory::litsDirectedGraph(int nodes, int density)
{
    int maxConnections = nodes * (nodes - 1);
    int connectionsToMake = maxConnections * density / 100;
    if (connectionsToMake < nodes - 1) {
        cout << "The graph of size " << nodes << " and density " << (float)density / 100.0f << "% can not be connected.\n";
        return nullptr;
    }
    AdjacencyList* l = new AdjacencyList(nodes);
    int connection = 0;
    //1
    Array* U = new Array();
    for (int i = 0; i < nodes; i++)
        U->addLast(i);

    int A = U->get(rand() % nodes);
    int B;
    U->delValue(A);
    while (!U->isEmpty()) {
        B = U->get(rand() % (nodes - connection - 1));
        U->delValue(B);
        cout << "Adding " << A << " -> " << B << "\n";
        l->addEdge(A, B, rand() % 99 + 1);
        connection++;
        A = B;
    }
    //2
    while (connection < connectionsToMake) {
        int A = rand() % nodes;
        int B = rand() % nodes;
        if (l->getEdge(A, B) != -1) continue;
        l->addEdge(A, B, rand() % 99 + 1);
        connection++;
    }
    return l;

    return nullptr;
}
