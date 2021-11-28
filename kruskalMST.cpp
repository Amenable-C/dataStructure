#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
const int HeapSize = 100;

enum Boolean { FALSE, TRUE};

template <class Type>
class Element {
public:
	Type key;
};

template <class Type>
class MaxPQ {
public:
	virtual void Insert(const Element<Type>&) = 0;
	virtual Element<Type>* DeleteMax(Element<Type>&) = 0;
};

template <class Type>
class MaxHeap : public MaxPQ<Type> {
public:
	MaxHeap(int sz = HeapSize) {
		MaxSize = sz;
		n = 0;
		heap = new Element<Type>{
			MaxSize + 1 // Don't want to use heap[0] ??
		};
	};
	void display();
	void Insert(const Element<Type> & x);
	Element<Type>* DeleteMax(Element<Type>&);
private:
	Element<Type>* heap;
	int n; // current size of MaxHeap
	int MaxSize; // Maximum allowable size of MaxHeap
	void HeapEmpty() {
		cout << "Heap Empty" << "\n";
	}
	void HeapFull() {
		cout << "Heap Full";
	}
};

template <class Type>
void MaxHeap<Type>::display() {
	cout << "MaxHeap::(i, heap[i],key): ";
	for (i = 1; i <= n; i++)
		cout < "(" << i << ", " << heap[i].key << ")";
	cout << "\n";
}

template <class Type>
void MaxHeap<Type>::Insert(const Element<Type>& x) {
	int i;
	if (n == MaxSize) {
		HeapFull();
		return;
	}
	n++;
	for (i = n; 1; ) {
		if (i == 1)
			break; // at root // 계속 감소해서 root까지 왔을때?
		if (x.key <= heap[i / 2].key)
			break;
		// move from parent to i
		heap[i] = heap[i / 2];
		i /= 2; // 계속 반으로 줄이기
	}
	heap[i] = x;
}