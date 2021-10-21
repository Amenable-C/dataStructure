#include <iostream>
using namespace std;

enum Bool{FALSE, TRUE};

template <class Type> class CircList;
template <class Type> class CircListIterator;
template <class Type> class List;

struct Term {
	int coef;
	int exp;
	void EnterTerm() {
		cout << endl << "coef: ";
		cin >> coef;
		cout << endl << "exp: ";
		cin >> exp;
	}
};

ostream& operator<<(ostream& os, Term e) {
	os << e.coef << "X**" << e.exp;
	return os;
}

template <class Type>
class ListNode {
	friend class CircList<Type>;
	friend class CircListIterator<Type>;
private:
	Type data;
	ListNode* link;
	ListNode(Type);
	ListNode() {};
};

template<class Type>
ListNode<Type>::ListNode(Type Default) {
	data = Default;
	link = 0;
}

template <class Type>
class CircList {
	friend class CircListIterator<Type>;
public:
	CircList() {
		first = new ListNode<Type>;
		first->link = first;
		last = first;
	}
	CircList(const CircList&);
	~CircList();
	void Attach(Type);
private:
	ListNode<Type>* first;
	ListNode<Type>* last;
	static ListNode<Type> av; //이거 중요
};

ListNode<Term>* CircList<Term>::av = 0; //static 사용시 초기화 방법

template <class Type>
class CircListIterator {
public:
	CircListIterator(const CircList<Type>& l) : list(l) {
		current = l.first->link; //이러면 두번째 아닌가??????
	}
	Type* Next();
	Type* First();
	Bool NotNull();
	Bool NextNotNull();
private:
	const CircList<Type>& list;
	ListNode<Type>* current;
};

template <class Type>
Type* CircListIterator<Type>::First() {
	if (current != list.first) //??????????????
		return &current->data;
	else
		return 0;
}

template <class Type>
Type* CircListIterator<Type>::Next() {
	current = current->link;
	if (current != list.first) //????????????
		return &current->data;
	else
		return 0;
}

template <class Type>
Bool CircListIterator<Type>::NotNull() {
	if (current != list.first)
		return TRUE;
	else
		return FALSE;
}

template <class Type>
Bool CircListIterator<Type>::NextNotNull() {
	if (current->link != list.first)
		return TRUE:
	else
		return FALSE;
}

template <class Type>
CircList<Type>::CircList(const CircList<Type>& l) {
	if (l.first == 0) {
		first = 0;
		return;
	}
	first = new ListNode<Type>(l.first->data);
	ListNode<Type>* newnode = first;
	for (ListNode<Type>* current = l.first->link; current != l.first; current = current->link) {
		newnode->link = new ListNode<Type>(current->data);
		newnode = newnode->link;
	}
	newnode->link = first;
}

template <class Type>
CircList<Type>::~CircList() {
	if (first) {
		ListNode<Type>* second = first->link;
		first->link = av;
		av = second;
		first = 0; 
	}
}

ostream& operator<<(ostream& os, CircList<Term>& l) {
	CircListIterator<Term> li(l);
	if (!li.NotNull())
		return os;
	os << *li.First();
	while (li.NextNotNull())
		os << " + " << *li.Next();
	os << endl;
	return os;
}

template <class Type>
void CircList<Type>::Attach(Type k) {
	ListNode<Type>* newnode = new ListNode<Type>(k);
	if (first == 0)
		first = last = newnode;
	else {
		newnode->link = last->link;
		last->link = newnode;
		last = newnode;
	}
}

//Polynomial
template <class Type>
class Polynomial {
private:
	CircList<Term> poly;
public:
	template <class Type>
	friend ostream& operator<<(ostream&, Polynomial&);
	/*template<class Type>
	friend istream& operator>>(istream&, Polynomial&);*/
	friend Polynomial operator+(const Polynomial&, const Polynomial&); // polynomial ADD()
	Polynomial();
	void Add(Term e);
	int GetData();
};

template <class Type>
Polynomial<Type>::Polynomial() {
	poly = 0;
}

template <class Type>
int Polynomial<Type>::GetData(){
	int i, degree;
	float coef;
	int expo;
	cout << "Enter Degree of Polynomial: ";
	cin >> degree;
	start = free;
	for (i = degree; i > 0; i--) {
		cout << "Enter coefficient of x^" << i << ":";
		cin >> coef;
		cout << "Enter exponent of x^" << i << ":";
		cin >> expo;
		NewTerm(coef, expo);
	}
	finish = free - 1;
	terms = finish - start + 1;
	return 0;

}