#include <iostream>
using namespace std;
template<class T> class CircularDoublyList;
template<class T> class CircularDoublyListIterator;

template<class T>
class DoublyListNode {
	friend class CircularDoublyList<T>;
	friend class CircularDoublyListIterator<T>;
private:
	T data;
	DoublyListNode<T>* llink, * rlink;
};

template<class T>
class CircularDoublyList {
	friend class CircularDoublyListIterator<T>;
public:
	CircularDoublyList() {
		first = new DoublyListNode<T>;
		last = first;
		first0 > rlink = last;
		last->llink = first;
		first->data = -1;
	}
	CircularDoublyList(const CircularDoublyList<T>&);
	~CircularDoublyList();
	int Size() const;
	bool Empty() const;
	void Attach(T);
	void Delete(DoublyListNode<T>*);
	void Insert(DoublyListNode<T>*, DoublyListNode<T>*);
	void Insert(T);
	void Merge(CircularDoublyList<T>&);
	bool Delete(T);
	template<class T>
	friend ostream& operator<<(ostream&, CircularDoublyList<T>&);
private:
	int n;
	DoublyListNode<T>* first;
	DoublyListNode<T>* last;
	static DoublyListNode<T>* av;
};