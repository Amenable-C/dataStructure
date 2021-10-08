#include <iostream>
using namespace std;

template<class T> class Chain; // forward declaration
template<class T> class ChainIterator;

template<class T> class ChainNode {
	friend class Chain<T>;
	friend class ChainIterator<T>;
public:
	ChainNode (T element = 0);
private:
	T data;
	ChainNode<T> link;
};

template<class T> class Chain {
	friend class ChainIterator<T>;
public:
	Chain() {
		first = 0;
	}
	void Delete(); // delete the first element after first
	int Length();
	void Add(const T& element); //add a new node after first
	void Invert();
	void Concatenate(Chain<T> b);
	template<class T>
	friend ostream& operator<<(ostream&, Chain<T>); // template <class T> 포함해야 compiler가 처리
	//int Minimun();
private:
	ChainNode<T>* first;
};

template<class T>
class ChainIterator {
public:
	ChainIterator(const Chain<T>& l) : list(l), current(l.first) {};
	//dereferencing operators
	T& operator *() const { return current->data; }
	T* operator ->() const { return &current->data; }
	//increment
	ChainIterator<T>& operator ++(); //preincrement
	ChainIterator<T> operator ++(int); //post increment
	bool NotNull(); //check the current element in list is non-null
	bool NextNotNull(); //check the next element in list is non-null

	T* First(); //return a pointer to the first element of list
	T* Next(); //return a pointer to the next element of list
private:
	const Chain<T>& list; //refers to an existing list
	ChainNode<T>* current; // points to a node in list
};

template<class T>
ChainNode<T>::ChainNode(T element) {
	data = element;
	link = 0;
}

template<class T>
void Chain<T>::Delete(void) { //delete the first element after first
	ChainNode<T>* current, * next;
	if (first != nullptr) {//non-empty list
		next = first->link;
		ChainNode<T>* temp = first;
		first = next; // 다음으로 이동하는거
		delete temp;
	}
	else
		cout << "Error - Empty List. not deleted" << endl;
}

template<class T>
void Chain<T>::Add(const T& element) { // add a new node after first
	ChainNode<T>* newnode = new ChainNode<T>(element);
	if (!first) { //insert into empty list
		first = newnode;
		return;
	}
	//insert a new node after first
	newnode->link = first; //새로운것에 first를 연결
	first = newnode; //first를 새로운걸로?
}

template<class T>
void Chain<T> ::Invert() {
	ChainNode<T>* p = first, * 1 = 0; // q trails p
	while (p) {
		ChainNode<T>*r 
	}
}