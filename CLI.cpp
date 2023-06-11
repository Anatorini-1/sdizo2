#include "CLI.h"
#include <iostream>

using namespace std;

CLI::CLI()
{

}



void CLI::run()
{
	int action = menu();
	system("cls");
	cout << "\n-----------------------\n";
	while (action != 9) {
		switch (action) {
		case 0: //Print graph
			if (graph == nullptr) {
				cout << "No graph stored\n";
			}
			else {
				graph->print();
			}
			break;
		case 1: //Load matrix;
			if (graph != nullptr) {
				delete graph;
			}
			cout << "filename: ";
			cin >> str;
			graph = gf.loadMatrixGraphFromFile(str);
			cout << "\nMatrix Loaded\n";
			graphType = MATRIX;
			break;
		case 2: // Load list
			if (graph != nullptr) {
				delete graph;
			}
			cout << "filename: ";
			cin >> str;
			graph = gf.loadListGraphFromFIle(str);
			cout << "\nList Loaded\n";
			graphType = LIST;
			break;
		case 3: //random matrix
			if (graph != nullptr) {
				delete graph;
			}
			cout << "Verticies: ";
			cin >> v;
			cout << "\n Density: ";
			cin >> d;
			cout << "Directed: [true/false]: ";
			cin >> str;

			graph = gf.matrixGraph(v, d, str == "true");
			cout << "\nMatrix Generated\n";
			graphType = MATRIX;
			break;
		case 4: //random list
			if (graph != nullptr) {
				delete graph;
			}
			cout << "Verticies: ";
			cin >> v;
			cout << "\n Density: ";
			cin >> d;
			cout << "Directed: [true/false]: ";
			cin >> str;
			graph = gf.listGraph(v, d, str == "true");
			cout << "\nMatrix Generated\n";
			graphType = LIST;
			break;
		case 5: //Prim
			if (graph == nullptr) {
				cout << "No graph stored\n";
			}
			else {
				if (graphType == MATRIX) {
					gp.PrimMST((IncidenceMatrix*)graph)->print();
				}
				else{
					gp.PrimMST((AdjacencyList*)graph)->print();
				}
			}
			
			break;
		case 6: //Kruskal
			if (graph == nullptr) {
				cout << "No graph stored\n";
			}
			else {
				if (graphType == MATRIX) {
					gp.KruskalMST((IncidenceMatrix*)graph)->print();
				}
				else {
					gp.KruskalMST((AdjacencyList*)graph)->print();
				}
			}
			break;
		case 7: //Dijkstra
			if (graph == nullptr) {
				cout << "No graph stored\n";
				break;
			}
			cout << "From: ";
			cin >> from;
			cout << "\nTo: ";
			cin >> to;
			cout << endl;
			if (graphType == MATRIX) {
				gp.pathDijkstra((IncidenceMatrix*)graph, from, to)->print();
			}
			else {
				gp.pathDijkstra((AdjacencyList*)graph, from, to)->print();
			}
			break;
		case 8: //BF
			if (graph == nullptr) {
				cout << "No graph stored\n";
				break;
			}
			cout << "From: ";
			cin >> from;
			cout << "\nTo: ";
			cin >> to;
			cout << endl;
			if (graphType == MATRIX) {
				gp.pathBellmanFord((IncidenceMatrix*)graph, from, to)->print();
			}
			else {
				gp.pathBellmanFord((AdjacencyList*)graph, from, to)->print();
			}
			break;
		}
	cout << "\n-----------------------\n";
	action = menu();
	}
	
}

int CLI::menu() {
	cout << "\nWhat should I do?:\n";
	cout << "Actions:\n";
	cout << "\t0. Print stored graph\n";
	cout << "\t1. Load Matrix from file\n";
	cout << "\t2. Load List from file\n";
	cout << "\t3. Generate random Matrix\n";
	cout << "\t4. Generate random List\n";
	cout << "Problems\n";
	cout << "\t5. MST\n";
	cout << "\t6. Shortest Path\n";
	cout << "9. EXIT\n";
	int x;
	cin >> x;
	if (x == 5 || x == 6) {
		return submenu(x);
	}
	
	if (x <= 9) return x;
	return 9;
	
}

int CLI::submenu(int x) {
	cout << "Which algorithm?: \n";
	if (x == 5) {
		cout << "0. Prim\n";
		cout << "1. Kruskall\n";
	}
	else {
		cout << "0. Dijkstra\n";
		cout << "1. Bellman-Ford\n";
		x++;
	}
	int i;
	cin >> i;
	return i + x;
}
