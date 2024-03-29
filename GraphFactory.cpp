#include <string>
#include "GraphFactory.h"
#include "IncidenceMatrix.h"
#include <cstdlib>
#include <math.h>
#include "Array.h"
#include <iostream>
#include <fstream>
using namespace std;
IncidenceMatrix* GraphFactory::matrixGraph(int nodes, int density,bool directional)
{   
    srand(time(0));

    int maxConnections = 0;
    int connectionsToMake = 0;
    if (directional) {
        //In a directed graph, the total number of possible 
        //edges is equal to nodes*(nodes-1)
        maxConnections = nodes * (nodes - 1);
        connectionsToMake = maxConnections * density / 100;
        if (connectionsToMake < nodes - 1) {
            cout << "The graph of size " << nodes << " and density " << (float)density / 100.0f << "% can not be connected.\n";
            return nullptr;
        }
    }

    else {
        //In an undirected graph, the total number of possible edges is
        // nodes*(nodes-1) / 2, alway an integer since either nodes or nodes-1 is divisible by 2, hence so is their product
        maxConnections = nodes * (nodes - 1) / 2;
        connectionsToMake = maxConnections * density / 100;
        if (connectionsToMake < nodes - 1) {
            cout << "The graph of size " << nodes << " and density " << (float)density / 100.0f << "% can not be connected.\n";
            return nullptr;
        }
    
    }

    IncidenceMatrix* m = new IncidenceMatrix(connectionsToMake, nodes,directional);
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
        if (A == B) continue;
        if (m->getEdge(A, B) != -1) continue;
        m->addEdge(A, B, rand() % 99 + 1);
        //cout << "Adding edge " << connection << " " << A << "->" << B << endl;
        connection++;
    }
    return m;
}

AdjacencyList* GraphFactory::listGraph(int nodes, int density, bool directional)
{
    int maxConnections;
    int connectionsToMake;
    if (directional) {
        //In a directed graph, the total number of possible 
        //edges is equal to nodes*(nodes-1)
        maxConnections = nodes * (nodes - 1);
        connectionsToMake = maxConnections * density / 100;
        if (connectionsToMake < nodes - 1) {
            cout << "The graph of size " << nodes << " and density " << (float)density / 100.0f << "% can not be connected.\n";
            return nullptr;
        }
    }

    else {
        //In an undirected graph, the total number of possible edges is
        // nodes*(nodes-1) / 2, alway an integer since either nodes or nodes-1 is divisible by 2, hence so is their product
        maxConnections = nodes * (nodes - 1) / 2;
        connectionsToMake = maxConnections * density / 100;
        if (connectionsToMake < nodes - 1) {
            cout << "The graph of size " << nodes << " and density " << (float)density / 100.0f << "% can not be connected.\n";
            return nullptr;
        }

    }
    
    srand(time(0));
    AdjacencyList* l = new AdjacencyList(nodes,directional);
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
        //cout << "Adding " << A << " -> " << B <<" "<< connection << "\n";
        l->addEdge(A, B, rand() % 99 + 1);
        connection++;
        A = B;
    }
    //2
    while (connection < connectionsToMake) {
        int A = rand() % nodes;
        int B = rand() % nodes;
        if (A == B) continue;
        if (l->getEdge(A, B) != -1) continue;
        l->addEdge(A, B, rand() % 99 + 1);
        connection++;
    }
    return l;

    return nullptr;
}

IncidenceMatrix* GraphFactory::loadMatrixGraphFromFile(std::string filename){
    ifstream file(filename, ifstream::in);
    if (!file.good()) {
        cout << "Failed to open file \"" << filename << "\"\n";
        return nullptr;
    }
    string d;
    cout << "Directional [true/false]: ";
    cin >> d;
    int edges, vertices;
    int from, to, weight;
    file >> edges;
    file >> vertices;
    IncidenceMatrix* m = new IncidenceMatrix(edges, vertices,d == "true");
    while (edges) {
        file >> from >> to >> weight;
        m->addEdge(from, to, weight);
        edges--;
    }
    file.close();
    return m;
}

AdjacencyList* GraphFactory::loadListGraphFromFIle(std::string filename)
{
    ifstream file(filename, ifstream::in);
    if (!file.good()) {
        cout << "Failed to open file \"" << filename << "\"\n";
        return nullptr;
    }
    int edges, vertices;
    int from, to, weight;
    string d;
    cout << "Directional [true/false]: ";
    cin >> d;
    file >> edges;
    file >> vertices;
    AdjacencyList* l = new AdjacencyList(vertices,d=="true");
    while (edges) {
        file >> from >> to >> weight;
        l->addEdge(from, to, weight);
        edges--;
    }
    file.close();
    return l;
}

