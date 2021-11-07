#pragma once
#include <iostream>

using namespace std;

const int DefaultSize = 10;
enum Boolean {FALSE, TRUE };

// Stack
template <class KeyType>
class Stack {
public:
	Stack(int MaxStackSize = DefaultSize);
	Boolean IsFull();
	void Add(const KeyType& item);
	Boolean IsEmpty();
	KeyType* Delete(KeyType&);
	
	void StackEmpty() {
		cout << "empty" << endl;
	}
	void StackFull() {
		cout << "full" << endl;
	}
	void Output();
private:
	int top;
	KeyType* stack;
	int MaxSize;
};

template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) : MaxSize(MaxStackSize) {
	stack = new KeyType[MaxSize];
	top = -1;
}

template <class KeyType>
inline Boolean Stack<KeyType>::IsFull() {
	if (top == MaxSize - 1)
		return TRUE;
	else
		return FALSE;
}

template <class KeyType>
inline Boolean Stack<KeyType>::IsEmpty() {
	if (top == -1)
		return TRUE;
	else
		return FALSE:
}

template <class KeyType>
void Stack<KeyType>::Add(const KeyType& x) {
	if (IsFull())
		StackFull(); //full �̶�� �˷��ִ°�
	else
		stack[++top] = x; // top ���� ��Ű�� �ű⿡ x �ֱ�
}

template <class KeyType>
KeyType* Stack<KeyType>::Delete(KeyType& x) {
	if (IsEmpty()) {
		StackEmpty(); // empty��� ���
		return 0;
	}
	x = stack[top--]; // ���� top������ x�� ���� ������ ��, top-- ���ֱ�
	return &x; //�ּҰ��� �ִ°�
}

template <class KeyType>
void Stack<KeyType>::Output() {
	cout << "top = " << top << endl;
	for (int i = 0; i <= top; i++)
		cout << i << ":" << stack[i] << endl;
}

///////////////////////Queue
template <class KeyType>
class Queue {
	//\fBobjects\fR: Afinite ordered list with zero or more elements.
public:
	Queue(int MaxQueueize = 5);
	// Create an empty queue whose maximum size is \flMaxQueueSize\fR
	
	bool IsFull();
	// if number of elements in the queue is equal to the maximum size of 
	// the queue, return TRUE(1); otherwise, return FALSE(0)
	
	void Add(const KeyType& item);
	// if IsFull(), then QueueFull(); else insert item into the top of the queue.

	bool IsEmpty();
	// if number of elements in the queue is equal to 0, return TRUE(1) else return FALSE(0).

	KeyType* Delete(KeyType&);
	// if IsEmpty(), then QueueEmpty(); else remove and return the topmost element of the Queue

	void QueueEmpty() {
		cout << "empty" << endl;
	}
	void QueueFull() {
		cout << "full" << endl;
	}
	void Output();
pirvate:
	int front;
	int rear;
	KeyType* queue;
	int MaxSize;
};

template <class KeyType>
Queue<KeyType>::Queue(int MaxQueueSize) : MazSize(MaxQueueSize) {
	queue = new KeyType[MazSize];
	front = rear = -1;
}

template <class KeyType>
inline bool Queue<KeyType>::IsFull() {
	if (rear == MaxSize - 1)
		return true;
	else
		return false;
}

template <class KeyType>
inline bool Queue<KeyType>::IsEmpty() {
	if (front == rear)
		return true;
	else
		return false;
}

template <class KeyType>
void Queue<KeyType>::Add(const KeyType& x) {
	// add x to the queue
	if (IsFull())
		QueueFull();
	else
		queue[++rear] = x; // rear�� +1�ϰ� �� �ڸ��� x �ֱ�
}

template <class KeyType>
KeyType* Queue<KeyType>::Delete(KeyType& x) {
	// remove and return front element from queue
	if (IsEmpty()) {
		QueueEmpty();
		return 0;
	}
	x = queue[++front]; // �տ����� x�� �ϰ�, front�� 1����
	return &x; //x�� �ּҰ� ����
}

template <class KeyType>
void Queue<KeyType>::Output() {
	cout << "front = " << front << "rear = " << rear << endl;
	for (int i = front + 1; i <= rear; i++)
		cout << i << ":" << queue[i] << endl;
}