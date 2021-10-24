//#include <iostream>
//#include <memory>
//using namespace std;
//#define MaxSize 100
//template <class T>
//// private 데이터 멤버인 array의 타입을 매개변수를 사용하여 code를 instantiation(매개변수 대신에 int로 바꾼 코드를 생성하는 것을 말한다.) 한다.
//
//
//class Bag {
//public:
//	Bag(int bagCapacity = 10);
//	~Bag();
//	bool IsFull();
//	int Size() const; // HowMany() 에 해당됨
//	bool IsEmpty() const;
//	virtual T& Pop() const;
//	virtual void Push(const T&);
//private:
//	T* array;
//	int capacity;
//	int top;
//};
//template <class T>
//Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity) {
//	if (capacity < 1)
//		throw "Capacity must be > 0";
//	array = new T[capacity];
//	top = -1;
//}
//
//template <class T>
//Bag<T>::~Bag() {
//	delete[] array;
//}
//
//template <class T>
//void ChangeSizeID(T*& a, const int oldSize, const int newSize) {
//	if (newSize < 0)
//		throw "New length must be >= 0";
//	T* temp = new T[newSize];
//	int number = oldSize;
//	if (oldSize > newSize)
//		number = newSize;
//	//copy(a, a + number, temp);
//	memcpy(temp, a, number);
//	delete[] a;
//	a = temp;
//}
//
//template <class T>
//int Bag<T>::Size() const {
//	return top + 1;
//}
//
//template <class T>
//bool Bag<T>::IsEmpty() const {
//	return top < 0;
//}
//
//template <class T>
//void Bag<T>::Push(const T& x) {
//	if (top == capacity - 1) {
//		// 현재 버전은 ordering 상태에서 push한다. non-ordering 되게 push가 가능하게 수정
//		ChangeSizeID(array, capacity, 2 * capacity);
//		capacity *= 2;
//	}
//	array[++top] = x;
//}
//
//template <class T>
//T& Bag<T>::Pop() const {
//	T retValue;
//	if (IsEmpty())
//		throw "Bag is empty, cannot delete";
//	int deletePos = top / 2;
//	retValue = array[deletePos];
//	// 실습 사항 : no ordering 상태에서 pop되게 수정
//	// copy(array + deletePos + 1, array + top + 1, array + deletePos);
//	memcpy(array + deletePos, array + deletePos, top + 1);
//	top--;
//	return retValue;
//}
//
//template <class T>
//inline bool Bag<T>::IsFull() {
//	if (top == MaxSize - 1)
//		return TRUE;
//	else 
//		return FALSE;
//}
//
//int main() {
//	Bag<int> b(4);
//	//Bag<float> fo(10); 에 대하여도 구현할 것
//	//화면에서 임의 숫자를 입력받아 Push() 호출하도록 수정
//	b.Push(3);
//	b.Push(5);
//	b.Push(1);
//	b.Push(6);
//	
//	if (b.IsEmpty()) {
//		cout << "empty" << endl;
//	}
//	else {
//		cout << "not emepty" << endl;
//	}
//
//	while (!b.IsEmpty()) {
//		//cout << b.Element() << endl;
//		b.Pop();
//	}
//	system("pause");
//	return 0;
//}