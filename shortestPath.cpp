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

};