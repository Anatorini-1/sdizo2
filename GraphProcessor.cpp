#include "GraphProcessor.h"
#include <queue>
#include "DoubleLinkedList.h"
#include "Graph.h"
#include <iomanip>
#include "Tester.h"
#include "MinHeap.h"
using namespace std;

IncidenceMatrix* GraphProcessor::PrimMST(IncidenceMatrix* graph)
{
	/*
	Steps of the Prim algorithm:
		1. Add all vertices to Q
		2. Pick an arbitrary (first in this case) vertex from Q
		3. Remove the chosen vertex from Q, add it to T
		4. Create a list of all edges from T to Q
		5. Add the edge with the smallest weight to the graph and remove the added node from Q
		6. If Q is not empty, goto 2


	*/
	//1
	DoubleLinkedList* Q = graph->getVertices();
	IncidenceMatrix* res = new IncidenceMatrix(graph->verticesCount() - 1, graph->verticesCount(),false);
	//2
	int Vertex = Q->get(0);
	//3
	DoubleLinkedList* T = new DoubleLinkedList();
	T->addFirst(Vertex);
	Q->delFirst();
	MinHeap* q = new MinHeap(graph->verticesCount()*(graph->verticesCount()-1)/2);
	
	// 4 
	T->forEach([&](int i) {
		DoubleLinkedList* adj = graph->getAdjecentVertices(i, false);
		adj->forEach([&](int j) {
			int weight = graph->getEdge(i, j);
			q->push({ i, j, weight });
			});
		delete adj;
		});
	while (!Q->isEmpty()) {
		int to = q->top().to;
		if (T->find(to) != -1) {
			q->pop();
			continue;
		}
		int cost = q->top().weight;
		int from = q->top().from;
		//cout << "Adding " << from << " to " << to << " cost " << cost << endl;
		Q->delValue(to);
		T->addLast(to);
		res->addEdge(from, to, cost);
		q->pop();
		//cout << vFrom->len << ' ';  vFrom->print(); std::cout << "\n";
		//cout << vTo->len << ' '; vTo->print(); std::cout << "\n";
		//cout << vCost->len << ' '; vCost->print(); std::cout << "\n";
		auto* ll = graph->getAdjecentVertices(to, false);
		ll->forEach([&](int j) {
			if (T->find(j) != -1) return;
			int weight = graph->getEdge(to, j);
			q->push({ to, j, weight });
			});
		delete ll;
	}
	delete q;
	delete Q;
	delete T;
	return res;

}

IncidenceMatrix* GraphProcessor::KruskalMST(IncidenceMatrix* g)
{
	//Assuming the graph is connected, wouldnt work otherwise.
	int v = g->verticesCount();
	IncidenceMatrix* T = new IncidenceMatrix(v - 1, v,false);
	Graph::edge *edges = g->getEdges();
	Graph::edge tmp;
	int e = g->edgesCount();
	MinHeap* q = new MinHeap(e);
	for (int i = 0; i < e; i++) {
		q->push(edges[i]);
		//cout << q->top().from << " " << q->top().to << " " << q->top().weight << endl;
	}
	while (T->edgesCount() < v - 1 && !q->empty()) {
		tmp = q->top();
		if (T->getEdge(tmp.from, tmp.to) == -1) {
			T->addEdge(tmp.from, tmp.to, tmp.weight);
		}
		q->pop();
	}
	delete q;
	return T;
}

DoubleLinkedList* GraphProcessor::pathDijkstra(IncidenceMatrix* g, int from, int to)
{
	int v = g->verticesCount();
	int* distance = new int[v];
	int* predecessor = new int[v];
	int* visited = new int[v];
	int tmp = 0;
	for (int i = 0; i < v; i++) {
		distance[i] = INT_MAX / 2;
		predecessor[i] = -1;
		visited[i] = false;
	}
	distance[from] = 0;
	MinHeap* vQueue = new MinHeap(5*v);
	vQueue->push({ from,0,distance[from]});
	int current = -1;
	while (!vQueue->empty()) {
		current = vQueue->top().from;
		if (!visited[current]) {
			//cout << "Current: " << current << endl;
			auto* adj = g->getAdjecentVertices(current, true);
			while (!adj->isEmpty()) {

				if (distance[adj->get(0)] > distance[current] + g->getEdge(current, adj->get(0))) {
					distance[adj->get(0)] = distance[current] + g->getEdge(current, adj->get(0));
					predecessor[adj->get(0)] = current;
					vQueue->push({ adj->get(0), 0, distance[adj->get(0)] });
				}
				adj->delFirst();
			}
			visited[current] = true;
		}
		
		vQueue->pop();

	}
	
	DoubleLinkedList* res = new DoubleLinkedList();
	int node = to;
	while (node != -1) {
		if (distance[node] !=INT_MAX / 2) {
			res->addFirst(node);
			node = predecessor[node];
			//cout << node << endl;
		}
		else node = -1;
	}
	return res;


	/*int v = g->verticesCount();
	int* costs = new int[v];
	int* predecessors = new int[v];
	bool* visited = new bool[v];
	int visitedCount = 0;
	int currentNode = from;
	for (int i = 0; i < v; i++) {
		costs[i] = INT_MAX/2;
		predecessors[i] = -1;
		visited[i] = false;
	}
	costs[from] = 0;
	/*for (int k = 0; k < v; k++) {
		printf("%10i", k);
	}
	
	while (visitedCount < v) {
		/*cout << endl;
		for (int k = 0; k < v; k++) {
			printf("%5i/%-5i ", costs[k], predecessors[k]);
		}
		for (int i = 0; i < v; i++) {
			if (visited[i]) continue;
			if (currentNode == -1 || costs[i] < costs[currentNode]) {
				currentNode = i;
			}
		}
		if (currentNode == -1) break;
		//cout << "Current node: " << currentNode << endl;
		visited[currentNode] = true;
		for (int i = 0; i < v; i++) {
			if (i == currentNode || i == from) continue;
			int cost = g->getEdge(currentNode, i) + costs[currentNode];
			if ( cost != (costs[currentNode]-1) && costs[i] > cost) {
				costs[i] = cost;
				predecessors[i] = currentNode;
			}
		}
		currentNode = -1;
		visitedCount++;
	}

	DoubleLinkedList* res = new DoubleLinkedList();
	if (costs[to] == INT_MAX/2) {
		res->addLast(-1);
		return res;
	}
	int node = to;
	while (node > 0) {
		res->addFirst(node);
		if (node < v) {
			node = predecessors[node];
		}
		else node = -1;
	}

	delete[] costs;
	delete[] predecessors;
	delete[] visited;
	return res;
	*/
}

DoubleLinkedList* GraphProcessor::pathBellmanFord(IncidenceMatrix* g, int from, int to)
{
	
	//INIT
	int V = g->verticesCount();
	int* costs = new int[V];
	int* predecessors = new int[V];
	for (int i = 0; i < V; i++) {
		costs[i] = INT_MAX/2;
		predecessors[i] = -1;
	}
	costs[from] = 0;
	Graph::edge* edges = g->getEdges();
	int E = g->edgesCount();
	Graph::edge* edge;
	//Relax edges V-1 times
	
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < E; j++) {
			edge = edges + j;
			if (costs[edge->from] + edge->weight < costs[edge->to]) {
				costs[edge->to] = costs[edge->from] + edge->weight;
				predecessors[edge->to] = edge->from;
			}
		}
	}
	

	//Check for negative cycles
	//As the problem description states there will be
	// no edges of negative weights, this can be skipped

	/*
	for (int v = 0; v < V; v++) {
		int u = predecessors[v];
		if (u != -1 && costs[u] + g->getEdge(u, v) < costs[v]) {
			//Negative cycle exists
			cout << "GRAPH CONTAINS A NEGATIVE CYCLE!" << endl;
			break;
		}
	}
	
	t = t1->getCounter() - t;
	cout << "Stupid loop: " << t << endl;
	*/

	DoubleLinkedList* res = new DoubleLinkedList();
	if (costs[to] == INT_MAX/2) {
		res->addLast(-1);
		return res;
	}
	int node = to;
	int tmp = 0;
	while (node != -1) {
		res->addFirst(node);
		node = predecessors[node];
	}
	delete[] costs;
	delete[] predecessors;
	return res;
}

IncidenceMatrix* GraphProcessor::maxFlowFordFulkerson(IncidenceMatrix* g)
{
	return nullptr;
}

AdjacencyList* GraphProcessor::PrimMST(AdjacencyList* graph)
{
	DoubleLinkedList* Q = graph->getVertices();
	AdjacencyList* res = new AdjacencyList(graph->verticesCount(),false);
	//2
	int Vertex = Q->get(0);
	//3
	DoubleLinkedList* T = new DoubleLinkedList();
	T->addFirst(Vertex);
	Q->delFirst();
	MinHeap* q = new MinHeap(graph->verticesCount() * (graph->verticesCount() - 1) / 2);
	//The max amount of verticies adjecent to a single vertex is v-1
	// 4 
	T->forEach([&](int i) {
		DoubleLinkedList* adj = graph->getAdjecentVertices(i, false);
		adj->forEach([&](int j) {
			int weight = graph->getEdge(i, j);
			q->push({ i, j, weight });
			});
		});
	while (!Q->isEmpty()) {
		int to = q->top().to;
		if (T->find(to) != -1) {
			q->pop();
			continue;
		}
		int cost = q->top().weight;
		int from = q->top().from;
		//cout << "Adding " << from << " to " << to << " cost " << cost << endl;
		Q->delValue(to);
		T->addLast(to);
		res->addEdge(from, to, cost);
		q->pop();
		//cout << vFrom->len << ' ';  vFrom->print(); std::cout << "\n";
		//cout << vTo->len << ' '; vTo->print(); std::cout << "\n";
		//cout << vCost->len << ' '; vCost->print(); std::cout << "\n";
		auto* ll = graph->getAdjecentVertices(to, false);
		ll->forEach([&](int j) {
			if (T->find(j) != -1) return;
			int weight = graph->getEdge(to, j);
			q->push({ to, j, weight });
			});
		delete ll;
	}
	delete q;
	delete T;
	delete Q;
	return res;
}

AdjacencyList* GraphProcessor::KruskalMST(AdjacencyList* g)
{
	//Assuming the graph is connected, wouldnt work otherwise.
	MinHeap* q = new MinHeap(g->edgesCount());
	int v = g->verticesCount();
	AdjacencyList* T = new AdjacencyList(v,false);
	Graph::edge* edges = g->getEdges();
	int e = g->edgesCount();
	Graph::edge tmp;
	for (int i = 0; i < e; i++) {
		q->push(edges[i]);
	}
	while (T->edgesCount() < v - 1 && !q->empty()) {
		tmp = q->top();
		if (T->getEdge(tmp.from, tmp.to) == -1) {
			T->addEdge(tmp.from, tmp.to, tmp.weight);
		}
		q->pop();
	}
	return T;
}

DoubleLinkedList* GraphProcessor::pathDijkstra(AdjacencyList* g, int from, int to)
{
	int v = g->verticesCount();
	int* distance = new int[v];
	int* predecessor = new int[v];
	int* visited = new int[v];
	int tmp = 0;
	for (int i = 0; i < v; i++) {
		distance[i] = INT_MAX / 2;
		predecessor[i] = -1;
		visited[i] = false;
	}
	distance[from] = 0;
	MinHeap* vQueue = new MinHeap(5 * v);
	vQueue->push({ from,0,distance[from] });
	int current = -1;
	while (!vQueue->empty()) {

		current = vQueue->top().from;
		if (!visited[current]) {
			//cout << "Current: " << current << endl;
			auto* adj = g->getAdjecentVertices(current, true);
			while (!adj->isEmpty()) {

				if (distance[adj->get(0)] > distance[current] + g->getEdge(current, adj->get(0))) {
					distance[adj->get(0)] = distance[current] + g->getEdge(current, adj->get(0));
					predecessor[adj->get(0)] = current;
					vQueue->push({ adj->get(0), 0, distance[adj->get(0)] });
				}
				adj->delFirst();
			}
			visited[current] = true;
		}

		vQueue->pop();

	}

	DoubleLinkedList* res = new DoubleLinkedList();
	int node = to;
	while (node != -1) {
		if (distance[node] != INT_MAX / 2) {
			res->addFirst(node);
			node = predecessor[node];
			//cout << node << endl;
		}
		else node = -1;
	}
	delete[] distance;
	delete[] predecessor;
	delete[] visited;
	delete vQueue;
	return res;

}

DoubleLinkedList* GraphProcessor::pathBellmanFord(AdjacencyList* g, int from, int to)
{
	//INIT
	int V = g->verticesCount();
	int* costs = new int[V];
	int* predecessors = new int[V];
	for (int i = 0; i < V; i++) {
		costs[i] = INT_MAX / 2;
		predecessors[i] = -1;
	}
	costs[from] = 0;
	Graph::edge* edges = g->getEdges();
	int E = g->edgesCount();
	for (int i = 0; i < E; i++) {
		//cout << edges[i].from << "->" << edges[i].to << ":" << edges[i].weight << endl;
	}
	Graph::edge* edge;
	//Relax edges V-1 times
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < E; j++) {
			edge = edges + j;
			if (costs[edge->from] + edge->weight < costs[edge->to]) {
				costs[edge->to] = costs[edge->from] + edge->weight;
				predecessors[edge->to] = edge->from;
			}
		}
	}

	//Check for negative cycles
	for (int v = 0; v < V; v++) {
		int u = predecessors[v];
		if (u != -1 && costs[u] + g->getEdge(u, v) < costs[v]) {
			//Negative cycle exists
			cout << "GRAPH CONTAINS A NEGATIVE CYCLE!" << endl;
			break;
		}
	}

	DoubleLinkedList* res = new DoubleLinkedList();
	if (costs[to] == 1000) {
		res->addLast(-1);
		return res;
	}
	int node = to;

	while (node != -1) {
		res->addFirst(node);
		node = predecessors[node];
	}

	delete[] costs;
	delete[] predecessors;
	return res;
}

AdjacencyList* GraphProcessor::maxFlowFordFulkerson(AdjacencyList* g)
{
	return nullptr;
}
