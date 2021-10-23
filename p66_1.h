//using namespace std;
//#include <iostream>
//#include <string>
//#include <assert.h>
//
//template<class T> class Term {
//public:
//	T coef;
//	T exp;
//	Term() {
//		coef = 0;
//		exp = 0;
//	}
//	Term(T c, T e) : coef(c), exp(e) {}
//	Term Set(int c, int e) {
//		coef = c;
//		exp - e;
//		return *this;
//	}
//};
//
//template<class T> class Chain;
//template<class T> class ChainIterator;
//
//template<class T>
//class ChainNode {
//friend class Chain<T>;
//friend class ChainIterator<T>;
//public:
//	ChainNode() {}
//	ChainNode(const T&); //Term<int>를 주는거 같은데? // int는 임의의 형식임
//private:
//	T data; // 이것도 아직 Term<int>
//	ChainNode<T>* link;
//};
//
//template<class T>
//class Chain {
//public:
//	Chain(){
//		first = 0;
//	};
//	void Delete();
//	int Length();
//	void Add(const T& element); // 여기서도 Term<int>
//	void Invert();
//	void Concatenate(Chain<T> b); // Term<int>
//	void InsertBack(const T& element); // Term<int>
//	void displayAll();
//
//	ChainIterator<T> begin() const {
//		return ChainIterator<T>(first);
//	}
//	ChainIterator<T> end() const {
//		return ChainIterator<T>(nullptr); // 왜 nullptr인지 아직 모르겠음
//	}
//private:
//	ChainNode<T>* first; // 첫 노드를 가르킴
//};
//
//template<class T>
//class ChainIterator {
//private:
//	//const Chain<T>* list; //이거는 현재 존재하는 list를 나타냄. 아마 2개이상 이면 이거 사용해야 할듯
//	ChainNode<T>* current;
//public:
//	//ChainIterator<T>(const Chain<T> &l) : Chain(l), current(l.first) {}; //이것도 두개이상이면
//	ChainIterator() {}
//	ChainIterator(ChainNode<T>* node) : current(node) {} // 노드를 하나 준다면, 그것이 current
//	//deferencing operators
//	T& operator *() const {
//		return current->data; //왜???
//	}
//	T* operator->() const {
//		return &current->data; // 함수 앞에 것이 객체가 되므로 이해됨.
//	}
//	bool operator && (ChainIterator<T> iter) const {
//		return current != NULL && iter.current != NULL; // current는 객체이고, iter.current는 인자의 current
//	}
//	bool isEmpty() const {
//		return current == NULL;
//	}
//	// increment
//	ChainIterator& operator ++(); //preincrement
//	ChainIterator<T> operator ++(int); //post increment
//	bool NotNull();
//	bool NextNotNull();
//	//T* First() { //return a pointer to the first element of list
//	//	if (list->first)
//	//		return &list->data;
//	//	else
//	//		return 0;
//	//}
//	T* Next(); //포인터로 줘야 함
//};
//
//// class Polynomial
//template<class T>
//class Polynomial {
//public:
//	Polynomial() {}
//	Polynomial(Chain<Term<T>>* terms) : poly(terms) {}
//	Polynomial<T> operator+(const Polynomial<T>& b) const;
//	void add(T coef, T exponent);
//	void addAll(Polynomial<T>* poly); //전체를 한번에 받을 수 없으므로 포인터로 받음.
//	void display();
//
//	//T Evaluate(T&) const;
//	//Polynomial<T> Multiply(Polynomial<T>&); 
//	//Polynomial(const Polynomial& p);
//	//friend istream& operator>>(istream&, Polynomial&);
//	//friend ostream& operator<<(ostream&, Polynomial&); 
//	//const Polynomial& operator=(const Polynomial&) const;
//	//~Polynomial();
//	//Polynomial operator~(const Polynomial&) const;
//private:
//	Chain<Term<T>> poly;
//};
//
//template <typename valType>
//inline ostream& operator<<(ostream& os, const Term<valType>& term) {
//	os << term.coef << "^" << term.exp;
//	return os;
//}
//
//template<class T>
//ChainNode<T>::ChainNode (const T& element){
//	data = element;
//	link = 0;
//}
//
//template<class T>
//void Chain<T>::Delete() {
//	ChainNode<T>* current, * next;
//	next = first->link;
//	if (first != nullptr) {
//		ChainNode<T> temp = first;
//		first = next;
//		delete temp; // 맨 앞에 꺼를 없애는거
//	}
//	else cout << "Empth List: Not deleted" << endl;
//}
//
//template<class T>
//void Chain<T>::Add(const T& element) {
//	ChainNode<T>* newnode = new ChainNode<T>(element);
//	if (!first) {
//		first = newnode;
//		return;
//	}
//	newnode->link = first;
//	first = newnode; // 맨 앞에 add 하는거
//}
//
//template<class T>
//void Chain<T>::Invert() {
//	ChainNode<T>* p = first, * q = 0;
//	while (p) {
//		ChainNode<T>* r = q;
//		q = p;
//		p = p->link;
//		q->link = r;
//	}
//	first = q; // 그냥 외우기
//}
//
//template<class T>
//void Chain<T>::Concatenate(Chain<T> b) {
//	if (!first) {
//		first = b.first;
//		return;
//	}
//	if (b.first) {
//		for (ChainNode<T>* p = first; p->link; p = p->link) { // 이렇게해서 iterator없이 가능할거 같은데????
//			p->link = b.first;
//		}
//	}
//}
//
//template<class T>
//void Chain<T>::InsertBack(const T& element) {
//	ChainNode<T>* newnode = new ChainNode<T>(element);
//	if (!first) {
//		first = newnode;
//		return;
//	}
//	ChainNode<T>* curr = first;
//	while (curr->link != NULL) {
//		curr = curr->link;
//	}
//	curr->link = newnode;
//}
//
//template<class T>
//void Chain<T>::displayAll() {
//	if (!first) return;
//	ChainNode<T>* curr = first;
//	while (curr != NULL) {
//		cout << curr->data << " + ";
//		curr = curr->link;
//	}
//	cout << endl;
//}
//
//template<class T>
//ChainIterator<T>& ChainIterator<T>::operator ++() {
//	current = current->link;
//	return *this;
//}
//
//template<class T>
//ChainIterator<T> ChainIterator<T>::operator ++(int) {
//	ChainIterator<T> old = *this;
//	current = current->link;
//	return old;
//}
//
//template<class T>
//bool ChainIterator<T>::NotNull() {
//	if (current)
//		return 1;
//	else
//		return 0;
//}
//
//template<class T>
//bool ChainIterator<T>::NextNotNull() {
//	if (current && current->link)
//		return 1;
//	else
//		return 0;
//}
//
//template<class T>
//T* ChainIterator<T>::Next() {
//	if (current) {
//		current = current->link;
//		return &current->data;
//	}
//	else
//		return 0;
//}
//
//template<class T>
//void Polynomial<T>::add(T coef, T exponent) {
//	Term<T>* newTerm = new Term<T>(coef, exponent);
//	this->poly.Add(*newTerm); // 더하고 난 것을 this로 가르킴
//}
//
//template<class T> void Polynomial<T>::addAll(Polynomial<T>* b) {
//	ChainIterator<Term<int>> iterB = b->poly.begin();
//	while (iterB.NotNull()) {
//		Term<T> dataB = *iterB;
//		add(dataB.coef, dataB.exp);
//		iterB.Next(); // 그냥 노드 포인터 만들어서 그것이 first 가르키게 하고 nullptr까지 돌려도 이거 할수 있을듯
//	}
//}
//
//template<class T>
//void Polynomial<T>::display() {
//	poly.displayAll();
//}
//
//template<class T>
//Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& b) const {
//	Term<T> temp;
//	ChainIterator<Term<T>> ai = poly.begin(), bi = b.poly.begin();
//	Polynomial<T> c;
//
//	while (ai && bi) {
//		if (ai->exp == bi->exp) {
//			int sum = ai->coef + bi->coef;
//			if (sum)
//				c.poly.InsertBack(temp.Set(sum, ai->exp)); //이렇게 하면 새로운 Set이 계속 만들어진다는 거 같은데
//			ai++, bi++;
//		}
//		else if (ai->exp < bi->exp) {
//			c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
//			bi++;
//		}
//	}
//	while (!ai.isEmpty()) {
//		c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
//		ai++;
//	}
//	while (!bi.isEmpty()) {
//		c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
//		bi++;
//	}
//	return c;
//}
//
