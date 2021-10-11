using namespace std;
#include <iostream>
#include <string>
#include <assert.h>

template<class T> class Term {
public:
	//A|| members of Term are public by default
	T coef; // coefficient
	T exp; // exponent
	Term() {
		coef = 0;
		exp = 0;
	}
	Term(T c, T e) : coef(c), exp(e) {}
	Term Set(int c, int e) {
		coef = c;
		exp = e;
		return *this;
	}
};

template<class T> class Chain; //forward delcaration
template<class T> class ChainIterator;

template<class T>
class ChainNode {
	friend class Chain<T>;
	friend class ChainIterator<T>;
public:
	ChainNode() {}
	ChainNode(const T&);
private:
	T data;
	ChainNode<T>* link;
};

template<class T> class Chain {
public:
	Chain() {
		first = 0;
	}
	void Delete(); //delete the first element after first
	int Length();
	void Add(const T& element); //add a nwe node after first
	void Invert();
	void Concatenate(Chain<T> b);
	void InsertBack(const T& element);
	void displayAll();

	ChainIterator<T> begin() const {
		return ChainIterator<T>(first);
	}
	ChainIterator<T> end() const {
		return ChainIterator<T>(nullptr);
	}
private:
	ChainNode<T>* first;
};

template<class T> class ChainIterator {
private:
	//const Chain<T>* list; // refers to an existing list
	ChainNode<T>* current; //points to a node in list
public:
	//ChainIterator<T>(const Chain<T> &l): Chain(l), current(l.first){};
	ChainIterator(){}
	ChainIterator(ChainNode<T>* node) : current(node) {}
	//dereferencing operators
	T& operator *() const {
		return current->data;
	}
	T* operator ->() const {
		return &current->data;
	}
	bool operator && (ChainIterator<T> iter) const {
		return current != NULL && iter.current != NULL;
	}
	bool isEmpty() const {
		return current == NULL:
	}
	//increment
	ChainIterator& operator ++(); //preincrement
	ChainIterator<T> operator ++(int); // post increment
	bool NotNull(); // check the current element in list is non-null
	bool NextNotNull(); // check the next element in list is non-null
	//T* First() {//return a pointer to the first element of list
	//	if (list->first) {
	//		return &list->first->data;
	//	else return 0;
	//	}
	//}
	T* Next(); // return a pointer to the next element of list
};

/*
class Polynomial
*/
template<class T>class Polynomial {
public:
	Polynomial() {}
	Polynomial(Chain<Term<T>> * terms):poly(terms){}
	Polynomial<T> operator+(const Polynomial<T> b) const;
	void add(T coef, T exponent);
	void addAll(Polynomial<T>* poly);
	void display();
	/*
	T Evaluate(T&) const; // f(x)에 대하여 x에 대한 값을 구한다

	*/
};