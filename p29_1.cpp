#pragma once
#include <iostream>
#include <memory>
using namespace std;
#define MaxSize 100

template <class T>
class Bag {
public:
	Bag(int bagCapacity = 10);
	~Bag();
	bool IsFull();
	int Size() const;
	bool IsEmpty() const;
	virtual T& Pop() const;
	virtual void Push(const T&);
private:
	T* array;
	int capacity;
	int top;
};
//Visual Studio 2019���� bag.h, bag.cpp�� �и����� �ʾƾ� ��
template <class T>
Bag<T>::Bag(int bagCapcity) : capacity(bagCapacity) {
	if (capacity < 1)
		throw "Capacity must be > 0";
	array = new T[capacity]; // �޸� �Ҵ�
	top = -1;
}

template <class T>
Bag<T>::~Bag() {
	delete[] array; // ����
}

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize) { //length �ٲٴ°� // a �� array
	if (newSize < 0)
		throw "New length must be >= 0";
	T* temp = new T[newSize]; // 
	int number = oldSize;
	if (oldSize < newSize)
		number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, number); //���� ����, ���� ��, ������ �������� ����
	delete[] a; // ���ο� a�� �޸𸮸� �Ҵ��ϱ� ���ؼ� �ϴ� �����
	a = temp; // ���ο� a�� �޸𸮸� �Ҵ�. // memcpy�� ���縦 �س��Ƽ� �ȿ� ������ ���� �ȵǴ� ��
}

template <class T>
int Bag<T>::Size() const { // ũ�⸦ �����ִ°�
	return top + 1;
}

template <class T>
bool Bag<T>::IsEmpty() const { // ũ���� (top+1)�� �̿��Ͽ� ���� ���� ��Ÿ��.
	return top < 0;
}

template <class T>
void Bag<T>::Push(const T& x) {
	if (top == capacity - 1) {
		ChangeSizeID(array, capacity, 2 * capacity); // ũ�Ⱑ ������ capacity 2��� ���ֱ�
		capacity *= 2; // private ��ġ�°� ����?
	}
	array[++top] = x; // �ڿ� �־��ֱ�
}

template<class T>
T& Bag<T>::Pop() const { // �׳� �� �ϳ� ������ �ϰ�, �� ���� �ٽ� T�� ����� // �μ��� ��� �ǳ�?....
	T retValue;
	if (IsEmpty())
		throw "Bag is empty, cannot delete";
	int deletePos = top / 2; // ũ�⸦ ������ ���̱�?? ��???
	retValue = array[deletePos]; // ��??
	// �ǽ� ���� : no ordering���·� pop�ǰ� ����
	// copy(array + deletePos + 1, array + top + 1; array + deletePos);
	memcpy(array + deletePos, array + deletePos, top + 1); // �޸𸮸� 1 �� �Ҵ�?
	top--; // ũ�� 1 ���̱�
	return retValue; 
}

template <class T>
inline bool Bag<T>::IsFull() { // �츮�� ������ �ִ밪���� �ƴ���
	if (top == MaxSize - 1)
		return TRUE;
	else
		return FALSE:
}