//#pragma once
//#include <iostream>
//using namespace std;
//
//class List;
//
//class Node {
//	friend class List;
//	friend class ListIterator;
//	friend class CircularList; //이게 추가 된거
//public:
//	Node(int, Node*);
//	~Node();
//private:
//	int num;
//	Node* link;
//};
//
//class List {
//	friend class ListIterator;
//	friend class CircularList;
//public:
//	List();
//	~List();
//	virtual void Add(int&);
//	virtual void Delete(int&);
//	virtual void Show();
//	//int Length();
//	//void Merge(List&, List&);
//private:
//	Node* first;
//};
//
//class ListIterator {
//public:
//	ListIterator(const List& lst);
//	~ListIterator();
//	bool NotNull();
//	bool NextNotNull();
//	int* First();
//	int* Next();
//	int& operator*() const;
//	int* operator->() const;
//	ListIterator& operator++();
//	ListIterator operator ++(int);
//	bool operator != (const ListIterator) const;
//	bool operator == (const ListIterator) const;
//	int* GetCurrent();
//private:
//	Node* current;
//	const List& list;
//};
//
//class CircularList : public List {
//public:
//	CircularList();
//	~CircularList();
//	void Add(int&);
//	void Delete(int&);
//	void Show();
//	void DeleteNum(int& x);
//};
//
//
////#include "listIterator.h"
//Node::Node(int element = 0, Node* next = 0) {
//	num = element;
//	link = next;
//}
//
//Node::~Node() {
//}
//
//List::List() {
//	first = 0;
//}
//
//List::~List(){}
//
//void List::Add(int& x) {
//	if (!first) {
//		first = new Node(x);
//		first->link = 0;
//	}
//	else {
//		Node* n = new Node(x); //x를 일단 Node로 만들어야 함
//		n->link = first;
//		first = n; //아.. 이렇게 해서 맨 앞으로 넣는다 이런거 같은데?
//	}
//}
//
//void List::Delete(int& x) {
//	if (first == NULL)
//		cout << "List is empty" << endl;
//	else {
//		// 추가해야함
//	}
//	return;
//}
//
//void List::Show() {
//	Node* current;
//	current = first;
//	if (first) {
//		while (current) {
//			cout << current->num << " ";
//			current = current->link;
//		}
//	}
//	else
//		cout << "List is empty" << endl;
//}
//
////ListIterator::ListIterator(Node *li){}
//
//ListIterator::ListIterator(const List& lst) : list(lst), current(lst.first) {
//	cout << "List Iterator is constructed" << endl;
//}
//
//bool ListIterator::NotNull() {
//	if (list.first == 0)
//		return false; // 초기값을 0으로 해놔서
//}
//
//bool ListIterator::NextNotNull() {
//	if (current->link != 0)
//		return true;
//	else
//		return false;
//}
//
//int* ListIterator::First() {
//	return &list.first->num;
//}
//
//int* ListIterator::Next() {
//	current = current->link;
//	cout << "current = " << current->num;
//	return &current->num;
//}
//
//int* ListIterator::GetCurrent() {
//	return &current->num;
//}
//
//ListIterator::~ListIterator() {
//}
//
//int& ListIterator::operator*() const {
//	return current->num;
//}
//
//int* ListIterator::operator->() const {
//	return &current->num;
//}
//
//ListIterator& ListIterator::operator++() {
//	current = current->link;
//	return *this;
//}
//
//ListIterator ListIterator::operator ++(int) {
//	ListIterator old = *this;
//	current = current->link;
//	return old;
//}
//
//bool ListIterator:: operator != (const ListIterator right) const {
//	return current != right.current;
//}
//
//bool ListIterator:: operator == (const ListIterator right) const {
//	return current == right.current;
//}
///////////////
//CircularList::CircularList() : List(){}
//CircularList::~CircularList() {}
//
//void CircularList::Add(int& x) {
//	Node* newNode = new Node(x);
//	if (first) {
//		newNode->link = first->link;
//		first->link = newNode; // 이렇게 해야지 circularList
//	}
//	else {
//		first = newNode;
//		newNode->link = newNode;
//	}
//}
//
//void CircularList::Delete(int& x) { // 값들을 reference로 받아야함
//	Node* newNode = new Node(x);
//	if (first) {
//		Node* Temp = first->link;
//		first->link = first->link->link;
//		delete Temp; // 이렇게 하면 건너뛰는거 된다는거 같은데
//	}
//	else {
//		cout << "empty list" << endl;
//	}
//}
//
//void CircularList::DeleteNum(int& x) {
//	//Node *newNode = new Node(x);
//	//first, medium, last uu
//	if (first) {
//		Node* CurrentNode = first;
//		Node* PreNode = first;
//		bool find = false;
//
//		//while(CurrentNode->link != first || CurrentNode == first)
//		while (CurrentNode->link != first) {
//			if (CurrentNode->num == x) {
//				find = true;
//				if (CurrentNode == first) { // first delete case
//					Node* Temp = CurrentNode;
//					while (CurrentNode->link != first) {
//						CurrentNode = CurrentNode->link;
//					}
//					first = first->link;
//					delete Temp;
//					CurrentNode->link = first;
//					break;
//				}
//				else if (CurrentNode->link != first) {
//					PreNode->link = CurrentNode->link;
//					delete CurrentNode;
//					break;
//				}
//			}
//			PreNode = CurrentNode;
//			CurrentNode = CurrentNode->link;
//		}//while end
//		if (find == false) {
//			if (CurrentNode->num == x) { // last Delte Case
//				PreNode->link = first;
//				delete CurrentNode;
//				find = true;
//			}
//		}
//		if (find == false)
//			cout << "can't find" << x << endl;
//	}
//	else {
//		cout << "empty list" << endl;
//	}
//}
//
//void CircularList::Show() {
//	Node* np;
//	np = first;
//	if (np->num > 0) {
//		do {
//			cout << np->num << " ";
//			np = np->link;
//		} while (np != first);
//	}
//	else cout << "List is empty" << endl;
//}