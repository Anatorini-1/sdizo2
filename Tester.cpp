#include "Tester.h"
void Tester::startCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";
    PCFreq = double(li.QuadPart) / 1000.0;
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double Tester::getCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

Tester::Tester() {
    CounterStart = 0;
    PCFreq = 0.0;
    startCounter();
    srand(time(0));

    d = 4;
    densities = new int[d];
    densities[0] = 25;
    densities[1] = 50;
    densities[2] = 75;
    densities[3] = 99;
    

    s = 5;
    sizes = new int[s];
    sizes[0] = 120;
    sizes[1] = 40;
    sizes[2] = 60;
    sizes[3] = 80;
    sizes[4] = 100;
    s = 1;
    file.open("./results.txt", ios::out);
}

Tester::~Tester()
{
    file.close();
    delete[] densities;
    delete[] sizes;
}

void Tester::testDijkstraMatrix()
{
    file << "Dijkstra Matrix" << endl;
    IncidenceMatrix* graph;
    DoubleLinkedList* x;
    srand(time(0));
    const int ITERATIONS = 10;
    file << "size;";
    for (int i = 0; i < d; i++) {
        file << "matrix" << densities[i] << ';';
    }
    file << endl;
    for (int i = 0; i < this->s; i++) {
        int size = sizes[i];
        file << size << ";";
        for (int j = 0; j < d; j++) {
            int dens = densities[j];
            printf("Testing for size %i density %i %c ...", size, dens, '%');
            graph = gf.matrixGraph(size, dens, true);
            double times[ITERATIONS];
            double t;
            int from;
            int to;
            for (int k = 0; k < ITERATIONS; k++) {
                //printf("%i%c\n",(int)((float)k/(float)ITERATIONS)*100,'%');
                do {
                    from = rand() % size;
                    to = rand() % size;
                } while (from == to);
                startCounter();
                x = gp.pathDijkstra(graph, from, to);
                t = getCounter();
                delete x;
                times[k] = t;
            }

            double totalMatrix = 0;
            for (int k = 0; k < ITERATIONS; k++) {
                totalMatrix += times[k];
            }
            totalMatrix /= ITERATIONS;
            file << totalMatrix << ";";
            printf("Done\n");
            delete graph;
        }
        file << endl;
    }
}

void Tester::testKruskalMatrix()
{
    file << "Kruskal Matrix" << endl;
    IncidenceMatrix* graph;
    IncidenceMatrix* x;
    srand(time(0));
    const int ITERATIONS = 100;
    file << "size;";
    for (int i = 0; i < d; i++) {
        file << "matrix" << densities[i] << ';';
    }
    file << endl;
    for (int i = 0; i < this->s; i++) {
        int size = sizes[i];
        file << size << ";";
        for (int j = 0; j < d; j++) {
            int dens = densities[j];
            printf("Testing for size %i density %i %c ...", size, dens, '%');
            graph = gf.matrixGraph(size, dens, false);
            double times[ITERATIONS];
            double t;
            for (int k = 0; k < ITERATIONS; k++) {
                //printf("%i%c\n",(int)((float)k/(float)ITERATIONS)*100,'%');
                startCounter();
                x = gp.KruskalMST(graph);
                t = getCounter();
                delete x;
                times[k] = t;
            }
            double totalMatrix = 0;
            for (int k = 0; k < ITERATIONS; k++) {
                totalMatrix += times[k];
            }
            totalMatrix /= ITERATIONS;
            file << totalMatrix << ";";
            printf("Done\n");
            delete graph;
        }
        file << endl;
    }

}

void Tester::testPrimMatrix()
{
    file << "Prim Matrix" << endl;
    IncidenceMatrix* graph;
    IncidenceMatrix* x;
    srand(time(0));
    const int ITERATIONS = 100;
    file << "size;";
    for (int i = 0; i < d; i++) {
        file << "matrix" << densities[i] << ';';
    }
    file << endl;
    for (int i = 0; i < this->s; i++) {
        int size = sizes[i];
        file << size << ";";
        for (int j = 0; j < d; j++) {
            int dens = densities[j];
            printf("Testing for size %i density %i %c ...", size, dens, '%');
            graph = gf.matrixGraph(size, dens, false);
            double times[ITERATIONS];
            double t;
            for (int k = 0; k < ITERATIONS; k++) {
                //printf("%i%c\n",(int)((float)k/(float)ITERATIONS)*100,'%');
                startCounter();
                x = gp.PrimMST(graph);
                t = getCounter();
                delete x;
                times[k] = t;
            }
            double totalMatrix = 0;
            for (int k = 0; k < ITERATIONS; k++) {
                totalMatrix += times[k];
            }
            totalMatrix /= ITERATIONS;
            file << totalMatrix << ";";
            printf("Done\n");
            delete graph;
        }
        file << endl;
    }
}

void Tester::testBellmanFordMatrix()
{
    file << "BellmanFord Matrix" << endl;
    IncidenceMatrix* graph;
    DoubleLinkedList* x;
    srand(time(0));
    const int ITERATIONS = 100;
    file << "size;";
    for (int i = 0; i < d; i++) {
        file << "matrix" << densities[i] << ';';
    }
    file << endl;
    for (int i = 0; i < this->s; i++) {
        int size = sizes[i];
        file << size << ";";
        for (int j = 0; j < d; j++) {
            int dens = densities[j];
            printf("Testing for size %i density %i %c ...", size, dens, '%');
            graph = gf.matrixGraph(size, dens, true);
            double times[ITERATIONS];
            double t;
            int from;
            int to;
            for (int k = 0; k < ITERATIONS; k++) {
                //printf("%i%c\n",(int)((float)k/(float)ITERATIONS)*100,'%');
                do {
                    from = rand() % size;
                    to = rand() % size;
                } while (from == to);
                startCounter();
                x =  gp.pathBellmanFord(graph, from, to);
                t = getCounter();
                delete x;
                times[k] = t;
            }

            double totalMatrix = 0;
            for (int k = 0; k < ITERATIONS; k++) {
                totalMatrix += times[k];
            }
            totalMatrix /= ITERATIONS;
            file << totalMatrix << ";";
            printf("Done\n");
            delete graph;
        }
        file << endl;
    }
}

void Tester::testDijkstraList()
{
    file << "Dijkstra List" << endl;
    AdjacencyList* graph;
    DoubleLinkedList* x;
    srand(time(0));
    const int ITERATIONS = 100;
    file << "size;";
    for (int i = 0; i < d; i++) {
        file << "list" << densities[i] << ';';
    }
    file << endl;
    for (int i = 0; i < this->s; i++) {
        int size = sizes[i];
        file << size << ";";
        for (int j = 0; j < d; j++) {
            int dens = densities[j];
            printf("Testing for size %i density %i %c ...", size, dens, '%');
            graph = gf.listGraph(size, dens, true);
            double times[ITERATIONS];
            double t;
            int from;
            int to;
            for (int k = 0; k < ITERATIONS; k++) {
                //printf("%i%c\n",(int)((float)k/(float)ITERATIONS)*100,'%');
                do {
                    from = rand() % size;
                    to = rand() % size;
                } while (from == to);
                startCounter();
                x = gp.pathDijkstra(graph, from, to);
                t = getCounter();
                delete x;
                times[k] = t;
            }

            double totalMatrix = 0;
            double totalList = 0;
            for (int k = 0; k < ITERATIONS; k++) {
                totalMatrix += times[k];
            }
            totalMatrix /= ITERATIONS;
            file << totalMatrix << ";";
            printf("Done\n");
            delete graph;
        }
        file << endl;
    }
}

void Tester::testKruskalList()
{
    file << "Kruskal List" << endl;
    AdjacencyList* graph;
    AdjacencyList* x;
    srand(time(0));
    const int ITERATIONS = 100;
    file << "size;";
    for (int i = 0; i < d; i++) {
        file << "list" << densities[i] << ';';
    }
    file << endl;
    for (int i = 0; i < this->s; i++) {
        int size = sizes[i];
        file << size << ";";
        for (int j = 0; j < d; j++) {
            int dens = densities[j];
            printf("Testing for size %i density %i %c ...", size, dens, '%');
            graph = gf.listGraph(size, dens, false);
            double times[ITERATIONS];
            double t;
            for (int k = 0; k < ITERATIONS; k++) {
                //printf("%i%c\n",(int)((float)k/(float)ITERATIONS)*100,'%');
                startCounter();
                x = gp.KruskalMST(graph);
                t = getCounter();
                delete x;
                times[k] = t;
            }
            double totalMatrix = 0;
            for (int k = 0; k < ITERATIONS; k++) {
                totalMatrix += times[k];
            }
            totalMatrix /= ITERATIONS;
            file << totalMatrix << ";";
            printf("Done\n");
            delete graph;
        }
        file << endl;
    }
}

void Tester::testPrimList()
{
    file << "Prim List" << endl;
    AdjacencyList* graph;
    AdjacencyList* x;
    srand(time(0));
    const int ITERATIONS = 100;
    file << "size;";
    for (int i = 0; i < d; i++) {
        file << "list" << densities[i] << ';';
    }
    file << endl;
    for (int i = 0; i < this->s; i++) {
        int size = sizes[i];
        file << size << ";";
        for (int j = 0; j < d; j++) {
            int dens = densities[j];
            printf("Testing for size %i density %i %c ...", size, dens, '%');
            graph = gf.listGraph(size, dens, false);
            double times[ITERATIONS];
            double t;
            for (int k = 0; k < ITERATIONS; k++) {
                //printf("%i%c\n",(int)((float)k/(float)ITERATIONS)*100,'%');
                startCounter();
                x = gp.PrimMST(graph);
                t = getCounter();
                delete x;
                times[k] = t;
            }
            double totalMatrix = 0;
            for (int k = 0; k < ITERATIONS; k++) {
                totalMatrix += times[k];
            }
            totalMatrix /= ITERATIONS;
            file << totalMatrix << ";";
            printf("Done\n");
            delete graph;
        }
        file << endl;
    }
}

void Tester::testBellmanFordList()
{
    file << "BellmanFord List" << endl;
    AdjacencyList* graph;
    DoubleLinkedList* x;
    srand(time(0));
    const int ITERATIONS = 100;
    file << "size;";
    for (int i = 0; i < d; i++) {
        file << "list" << densities[i] << ';';
    }
    file << endl;
    for (int i = 0; i < this->s; i++) {
        int size = sizes[i];
        file << size << ";";
        for (int j = 0; j < d; j++) {
            int dens = densities[j];
            printf("Testing for size %i density %i %c ...", size, dens, '%');
            graph = gf.listGraph(size, dens, true);
            double times[ITERATIONS];
            double t;
            int from;
            int to;
            for (int k = 0; k < ITERATIONS; k++) {
                //printf("%i%c\n",(int)((float)k/(float)ITERATIONS)*100,'%');
                do {
                    from = rand() % size;
                    to = rand() % size;
                } while (from == to);
                startCounter();
                x = gp.pathBellmanFord(graph, from, to);
                t = getCounter();
                delete x;
                times[k] = t;
            }

            double totalMatrix = 0;
            for (int k = 0; k < ITERATIONS; k++) {
                totalMatrix += times[k];
            }
            totalMatrix /= ITERATIONS;
            file << totalMatrix << ";";
            printf("Done\n");
            delete graph;
        }
        file << endl;
    }
}
