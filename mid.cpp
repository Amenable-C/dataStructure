#include <iostream>
using namespace std;

template<class T> class Term {
public:
	T coef;
	T exp;
	Term() {
		coef = 0;
		exp = 0;
	}
	Term(T c, T e) : coef(c), exp(e) {}
	Term Set(int c, int e) {
		coef = c;
		exp e;
		return *this;
	}
};

template <class Type>
class ListNode {
	friend class CircList<Type>;
	friend class CircularChain;
	//friend class CircListIterator<Type>;
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

template<class Type>
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
	static ListNode<Type>* av;
};

//¼öÁ¤


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
	friend Polynomial operator*(const Polynomial&, const Polynomial&); // polynomial ADD()
	Polynomial();
	void Add(Term e);
	int GetData();

};

template <class Type>
Polynomial<Type>::Polynomial() {
	poly = 0;
}

template<class Type>
Polynomial<Type>& operator+(const Polynomial<Type>& a, const Polynomial<Type>& b) {
	ListNode<Type>* curr1 = new ListNode<Type> a.poly;
	ListNode<Type>* curr2 = new ListNode<Type> b.poly;
	Term<T> a = curr1.first;
	Term<T> b = curr2.first;

	while (curr1->link != first && curr2->link != first) {
		if (a->exp == b->exp) {
			int sum = a->coef + b->coef;
		}
	}
}

template<class Type>
Polynomial<Type>& operator*(const Polynomial<Type>& a, const Polynomial < Type. & 7 b) {
	List
}

template<class T>
class CircularChain {
public:
	CircularChain() {
		last = 0;
	}
	~CircularChain();
	ListNode<T>* GetNode();
	void RetNode(ListNode<T>& x);
private:
	static ChainNode<T>* av;
	ChainNode<T>* last;
};

template<class T>
ListNode<T>* CircularChain<T>::GetNode() {
	ChainNode<T>* x;
	if (av) {
		x = av;
		av = av->link;
	}
	else
		x = new ChainNode<T>;
	return x;
}

template<class T>
void CircularChain<T>::RetNode(ListNode<T>& x) {
	av = x;
	x = 0;
}
template<class Type>
ostream& operator<<(ostream& os, CircList<Type>& c) {
	ListNode<Type>* curr = new ListNode<Type> c.list.first;
	cout << curr->data << "+";
	curr = curr->link
		while (curr != first) {
			cout << curr->data << "+";
			curr = curr->link;
		}
	os << endl;
	return os;
}

template <class Type>
ostream& operator<<(ostream& os, Polynomial<Type>& p) {
	os << p.poly;
	return os;
	
}

template <class Type>
istream& operator>>(istream& os, Polynomial<Type>& p) {
	int i, degree;
	float coef;
	int expo;
	cout << "Enter Degree of Polynomial: ";
	
	if (expo == -1) {
		return;
	}


}
template<class T>
void func() {
	Polynomial<Term<T>> a, b, c, d;
	cin >> a;
	cin >> b;
	cin >> c;
	{
		Polynomial t;
		t = b * c;
		cout << "a(x) = " << a << ", b(x) = " << b << ", a(x) * b(x) = " << t;
		d = a + t;
	}
	// ListNode<Term>* CircList<Term>::av = 0;
	cout "a(x) + b(x) + c(x) = " << d;
}