#include <iostream>
#include <stdlib.h>
using namespace std;
const int nmax = 100;
const int MAX_WEIGHT = 9999999;

class Graph {
private:
	int length[nmax][nmax]; // connection matrix
	int a[nmax][nmax];
	int dist[nmax]; // distance from v to u
	bool s[nmax];
	int newdist[nmax];

	const int n;
public:
	void ShortestPath(const int);
	void ShortestPath_display(const int);
	void BellmanFord(const int);
	void BellmanFord2(const int);
	void AllLengths();
	int choose();
	void Out(int startNode, int n);
	void OutA(int);

	Graph(int nodeSize) : n(nodeSize) {
		for (int i = 0; i < nmax; i++) {
			for (int k = 0; k < nmax; k++) {
				length[i][k] = MAX_WEIGHT;
			}
		}
	}

	void insertEdge(int start, int end, int weight);
	void displayConnectionMatrix();
	bool isNonNegativeEdgeCost() {
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < n; k++) {
				if (length[i][k] < 0)
					return false;
			}
		}
		return true;
	}

private:
	void displayS() {
		cout << "[";
		for (int i = 0; i < n; i++) {
			if (s[i])
				cout << i << ",";
			else
				cout << " ";
		}
		cout << "]; ";
	}
};

void Graph::displayConnectionMatrix() {
	for(int i = 0; i < n; i++) {
		bool exists = false;
		for (int k = 0; k < n; k++) {
			if (length[i][k] == MAX_WEIGHT)
				continue;
			exists = true;
			cout << i << " -> " << k << "(weight=" << length[i][k] << "), ";
		}
		if (exists)
			cout << endl;
	}
}

void Graph::insertEdge(int start, int end, int weight) {
	if (start >= n || end >= n || start < 0 || end < 0) {
		cout << "the input node is out of boiund, the biggest node is " << (n - 1) << endl;
		return;
	}
	length[start][end] = weight;
}

void Graph::Out(int startNode, int n) {
	// cout << endl;
	for (int i = 0; i < n; i++) {
		if (i == startNode) {
			cout << "0" << ", ";
		}
		else if (dist[i] == MAX_WEIGHT)
			cout << "infinite" << ", ";
		else
			cout << dist[i] << ", ";
	}
	cout << endl;
}

void Graph::OutA(int n) {
	// cout << endl;
	for (int i = 0; i < n; i++) {
		cout << "startNode = " << i << ": ";
		for (int j = 0; j < n; j++) {
			if (i == j) {
				cout << "0 " << " ";
			}
			else if (a[i][j] > MAX_WEIGHT - 100000) // 100000 is one a big enought number
				cout << "infinite" << " ";
			else
				cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

void Graph::ShortestPath(const int v) {
	for (int i = 0; i < n; i++) { // intialize
		s[i] = false;
		dist[i] = length[v][i];
	}
	s[v] = true;
	dist[v] = 0;

	//Out(n);
	for (int i = 0; i < n - 2; i++) {// determine n - 1 paths from vertex v
		Out(i, n);
		int u = choose(); // choose returns a value u;

		// dist[u] = minimum dist[w], where s[w] = false
		s[u] = true;
		for (int w = 0; w < n; w++)
			if (!s[w])
				if (dist[u] + length[u][w] < dist[w])
					dist[w] = dist[u] + length[u][w];
	}
	Out(v, n);
}

void Graph::ShortestPath_display(const int v) {
	for (int i = 0; i < n; i++) { // initialize
		s[i] = false;
		dist[i] = length[v][i];
	}

	//>>>>>>>>>>display
	cout << 1 << "; ";
	displayS();
	cout << "vertex selected: " << v << "; ";
	Out(v, n);
	//<<<<<<<<<<

	s[v] = true;
	dist[v] = 0;

	//Out(n);
	int i = 0;
	for (; i < n - 2; i++) { // determine n-1 paths from vertex v
		int u = choose(); // choose returns a value u;
		//dist[u] = minimum dist[w], where s[w] = false
		cout << i + 2 << "; ";
		displayS();

		s[u] = true;

		cout << "vertex selected: " << u << "; ";
		Out(v, n);
		for (int w = 0; w < n; w++)
			if (!s[w])
				if (dist[u] + length[u][w] < dist[w])
					dist[w] = dist[u] + length[u][w];
	}
	cout << i + 2 << ", ";
	displayS();
	cout << ":                   " << ", ";
	Out(v, n);
}

int Graph::choose() {
	int prevmax = -1;
	int index = -1;
	for (int i = 0; i < n; i++) {
		if ((!s[i]) && ((prevmax == -1) || (dist[i] < prevmax))) {
			prevmax = dist[i];
			index = i;
		}
	}
	return index;
}

void Graph::BellmanFord(const int v) {
	for (int i = 0; i < n; i++) {
		dist[i] = length[v][i];
	}

	cout << endl;
	int k = 0;
	for (k = 1; k <= n - 1; k++) {
		cout << "k = " << k << ", ";
		Out(v, n);
		for (int u = 0; u < n; u++) {
			if (u != v) {
				for (int i = 0; i < n; i++) {
					if ((u != i) && (length[i][u] < MAX_WEIGHT)) {
						if (dist[u] > dist[i] + length[i][u]) {
							dist[u] = dist[i] + length[i][u];
						}
					}
				}
			}
		}
	}
	//cout << "k = " << k << ", ";
	//Out(n);
}
