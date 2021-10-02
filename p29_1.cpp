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
//Visual Studio 2019에서 bag.h, bag.cpp로 분리하지 않아야 함
template <class T>
Bag<T>::Bag(int bagCapcity) : capacity(bagCapacity) {
	if (capacity < 1)
		throw "Capacity must be > 0";
	array = new T[capacity]; // 메모리 할당
	top = -1;
}

template <class T>
Bag<T>::~Bag() {
	delete[] array; // 제거
}

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize) { //length 바꾸는거 // a 는 array
	if (newSize < 0)
		throw "New length must be >= 0";
	T* temp = new T[newSize]; // 
	int number = oldSize;
	if (oldSize < newSize)
		number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, number); //복사 받을, 복사 할, 복사할 데이터의 길이
	delete[] a; // 새로운 a의 메모리를 할당하기 위해서 일단 지우기
	a = temp; // 새로운 a의 메모리를 할당. // memcpy로 복사를 해놓아서 안에 내용은 삭제 안되는 듯
}

template <class T>
int Bag<T>::Size() const { // 크기를 보여주는거
	return top + 1;
}

template <class T>
bool Bag<T>::IsEmpty() const { // 크기인 (top+1)을 이용하여 존재 유무 나타냄.
	return top < 0;
}

template <class T>
void Bag<T>::Push(const T& x) {
	if (top == capacity - 1) {
		ChangeSizeID(array, capacity, 2 * capacity); // 크기가 작으면 capacity 2배로 해주기
		capacity *= 2; // private 고치는거 가능?
	}
	array[++top] = x; // 뒤에 넣어주기
}

template<class T>
T& Bag<T>::Pop() const { // 그냥 값 하나 나오게 하고, 그 다음 다시 T를 줘야함 // 인수가 없어도 되나?....
	T retValue;
	if (IsEmpty())
		throw "Bag is empty, cannot delete";
	int deletePos = top / 2; // 크기를 반으로 줄이기?? 왜???
	retValue = array[deletePos]; // 왜??
	// 실습 사항 : no ordering상태로 pop되게 수정
	// copy(array + deletePos + 1, array + top + 1; array + deletePos);
	memcpy(array + deletePos, array + deletePos, top + 1); // 메모리를 1 더 할당?
	top--; // 크기 1 줄이기
	return retValue; 
}

template <class T>
inline bool Bag<T>::IsFull() { // 우리가 설정한 최대값인지 아닌지
	if (top == MaxSize - 1)
		return TRUE;
	else
		return FALSE:
}