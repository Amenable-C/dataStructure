#include <iostream>
#include <memory>

using namespace std;

template <class T>
class Stack {
public:
	Stack(int stackCapacity = 10);
	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& item);
	void Pop();
private:
	T* stack;
	int top;
	int capacity;
};

template <class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity) {
	if (capacity < 1)
		throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize) {
	if (newSize < 0)
		throw "New length must be >= 0";
	T* temp = new T[new Size];
	int number = oldSize;
	if (oldSize > newSize)
		number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, number);
	delete[] a;
	a = temp;
}

template <class T>
inline bool Stack<T>::IsEmpty() const {
	return top == -1;
}

template <class T>
inline T& Stack<T>::Top() const {
	if (IsEmpty())
		throw "Stack is empty";
	return stack[top];
}

template <class T>
void Stack<T>::Push(const T& x) {
	if (top == capacity - 1) {
		ChangeSizeID(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}

template <class T>
void Stack<T>::Pop() {
	if (IsEmpty())
		throw "Stack is empty. Cannot delete.";
	stack[top--].~T(); //?
}

int main() {
	Stack<int> s(4);
	//Stack<float> fo(10); 실수에 대하여도 구현
	//화면에서 입력받아 동작하도록 구현
	//stack이 full일 때 처리 기능을 구현
	s.Push(3);
	s.Push(6);
	s.Push(1);
	s.Push(2);

	cout << "is empty:	";
	if (s.IsEmpty()) {
		cout << " yes" << endl;
	}
	else {
		cout << " no" << endl;
	}
	cout << "print all elements: " << endl;
	while (!s.IsEmpty()) {
		cout << s.Top() << " ";
		s.Pop();
	}
	cout << endl;
	system("pause");
	return 0;
}
