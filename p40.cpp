// 3.5 a mazing problem
#include <iostream>
#include <fstream>

//#include "stackTemplate.h" //?
using namespace std;

const int DefaultSize = 100;

struct items {
	int x, y, dir;
};

ostream& operator<<(ostream& os, items& item) {
	return os << item.x << "," << item.y << "," << item.dir;
}

struct offsets {
	int a, b;
};

enum directinos {N, NE, E, SE, S, SW, W, NW};
offsets moves[8];
int maze[100][100];
int mark[100][100];

void path(int m, int p) {
	//Output a path(if any) in the maze : rows is m, cols is p;
	mark[1][1] = 1;
	Stack<items> stack(m * p);
	items temp;
	temp.x = 1; temp.y = 1; temp.dir = E;
	stack.Push(temp);

	while (!stack.IsEmpty()) {
		temp = stack.Pop();
		int i = temp.x;
		int j = temp.y;
		int d = temp.dir;
		while (d < 8) {
			//moves forward
			//outFile << i << " " << j << " " << d << endl;
			int g = i + moves[d].a;
			int h = j + moves[d].b;
			if ((g == m) && (h == p)) {
				//reached exit
				//output path
				cout << stack;
				cout << "the term near the exit : " << i << " " << j << endl;
				cout << "exit: " << m << " " << p << endl;
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h])) {
				//new position
				mark[g][h] = 1;
				//push the old temp to the stack, but the direction changes.
				//Because the neighbor in the direction of d has been checked.
				temp.x = i;
				temp.y = j;
				temp.dir = d + 1;
				stack.Push(temp);
				i = g;
				j = h;
				d = N;
				//move to (g, h)
			}
			else
				d++;
		}
	}
	cout << "no path in maze" << endl;

}