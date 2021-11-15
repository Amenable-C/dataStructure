#include <iostream>
#include <algorithm>
#include <time.h>
template <class Type>
bool compare(Type a, Type b) {
	return a > b; // 내림차순 // max-heap 고려
}

using namespace std;
const int HeapSize = 10000000;
enum Boolean { FALSE, TRUE };

template <class Type>
class Element {
public:
	Type key;

	Element() {}
	Element(Type key) : key(key) {}
};

template <class Type>
class MaxPQ {
public:
	virtual void Insert(const Element<Type>&) = 0;
	virtual Element<Type>* DeleteMax(Element<Type>) = 0;
};

template <class Type>
class MaxHeap : public MaxPQ<Type> {
	//friend class Element;
public:
	MaxHeap(int sz = HeapSize) {
		MaxSize = sz;
		n = 0;
		heap = new Element<Type>[MaxSize + 1]; // Don't want to use heap[0]
	}
	void display();
	void Insert(const Element<Type>& x);
	void orderedInsert(const Element<Type>& x);
	Element<Type>* DeleteMax(Element<Type>&);
	Element<Type>* orderedDeleteMax(Element<Type>&);
	void sort();
private:
	Element<Type>* heap;
	int n; // current size of MaxHeap
	int MaxSize; //Maximum allowable size of MaxHeap

	void HeapEmpty() {
		cout << "Heap Empty" << "\n";
	}
	void HeapFull() {
		cout << "Heap Full";
	}
};

template <class Type>
void MaxHeap<Type>::display() {
	int i;
	cout << "MaxHeap:: (i, heap[i].key): ";
	for (i = 0; i <= n; i++)
		cout << "(" << i << ", " << heap[i].key << ")";
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
	for (i = n; 1;) {
		if (i == 1)
			break; // at root
		if (x.key <= heap[i / 2].key)
			break; // move freom parent to i
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
}

template <class Type>
void MaxHeap<Type>::orderedInsert(const Element<Type>& x) {
	int i;
	if (n == MaxSize) {
		HeapFull();
		return;
	}
	n++;
	for (i = n; i > 0; i--) {
		if (i == 1)
			break;
		if (x.key <= heap[i-1].key)
			break;
		heap[i] = heap[i-1];
	}
	heap[i] = x;
}

template<class Type>
Element<Type>* MaxHeap<Type>::DeleteMax(Element<Type>& x) {
	int i, j;
	if (!n) {
		HeapEmpty();
		return 0;
	}
	x = heap[1];
	Element<Type> k = heap[n];
	n--;

	for (i = 1, j = 2; j <= n;) {
		if (j < n)
			if (heap[j].key < heap[j + 1].key)
				j++; // j points to the larger child
		if (k.key >= heap[j].key)
			break;
		heap[i] = heap[j];
		i = j;
		j *= 2;
	}
	heap[i] = k;
	return &x;
}

template<class Type>
Element<Type>* MaxHeap<Type>::orderedDeleteMax(Element<Type>& x) {
	int i, j;
	if (!n) {
		HeapEmpty();
		return 0;
	}
	x = heap[1];
	n--;

	for (int k = 1; k <= n; k++) {
		heap[i] = heap[i + 1];
	}
	return &x;
}
int temp;

template<class Type>
void MaxHeap<Type>::sort() {
	for (int i = 1; i <= num - 1; i++) {
		for (int j = 2; j <= num - i + 1; j++) { // 여기 다시 체크
			if (heap[j - 1].key < heap[j].key) {
				temp = heap[j].key;
				heap[j].key = heap[j - 1].key;
				heap[j - 1].key = temp;
			}
		}
	}
}

int main() {
	int select = 0;
	int data = 0;

	MaxHeap<int> heapUnordered(20);
	MaxHeap<int> heapOrdered(20);
	Element<int> ele;

	Element<int>* deletedEle = nullptr;

	// 난수를 이용하여 heap 생성
	int num = 5000000;
	for(int t = 0; t < num; t++) {
		data = rand() % num;
		heapUnordered.Insert(Element<int>(data));
		heapOrdered.Insert(Element<int>(data)); // 일단 여기에 넣어두고 나중에 정렬
	}

	heapOrdered.sort(); // 내림차순 정렬
	cout << "ordered test" << endl;
	heapOrdered.display();
	
	time_t start, end;
	double result;
	
	cout << "input value for inserting: ";
	cin >> data;
	start = time(NULL);
	heapUnordered.Insert(Element<int>(data));
	end = time(NULL);
	result = (double)(end - start);
	cout << "Time for unordered insert: " << result;

	start = time(NULL);
	heapOrdered.Insert(Element<int>(data));
	end = time(NULL);
	result - (double)(end - start);
	cout << "Time for ordered insert: " << result;







	


	system("pause");
	return 0;
}