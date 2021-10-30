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
	CircularDoublyList() { //초기 설정
		first = new DoublyListNode<T>;
		last = first;
		first->rlink = last;
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

template<class T>
class CircularDoublyListIterator {
public:
	CircularDoublyListIterator(const CircularDoublyList<T>& l) : list(l) {
		current = l.first->rlink;
	}
	T* Next();
	T* First();
	bool NotNull();
	bool NextNotNull();
private:
	const CircularDoublyList<T>& list;
	DoublyListNode<T>* current;
};

template<class T>
DoublyListNode<T>* CircularDoublyList<T>::av = 0;

template<class T>
void CircularDoublyList<T>::Delete(DoublyListNode<T>* x) {
	if (x == first)
		cerr << "Deletion of head node not permitted" << endl;
	else {
		x->llink->rlink = x->rlink; //x를 지우는거라서 x의 llink가 x의 rlink를 가르키도록
		x->rlink->llink = x->llink;
		delete x; // 포인터에 할당된것을 바로 그냥 delete로 지우기
	}
}

template<class T>
void CircularDoublyList<T>::Insert(DoublyListNode<T>* p, DoublyListNode<T>* x) {
	//노드 p를 노드 x 오른쪽에 넣기
	p->llink = x; //기본
	p->rlink = x->rlink; // 원래 x가 가르키던거를 p가 받아야 함
	x->rlink->llink = p; // x의 오른쪽이 이제는 p를 가르키도록
	x->rlink = p; //기본
	// 각각 가르키는거 2개, x의 오른쪽에서 2개
}

template<class T>
void CircularDoublyList<T>::Insert(T x) {
	DoublyListNode<T>* p, * temp = new DoublyListNode<T>; //x를 새로운 노드로 만들기
	temp->data = x; //노드의 데이터가 x
	p = first; // 원래 있던 first를 포인터로 가르킨다?

	while (true) {
		if (x < p->rlink->data) { // 크면 p 오른쪽에 넣기
			temp->llink = p;
			temp->rlink = p->rlink;
			p->rlink->llink = temp;
			p->rlink = temp;
			break;
		}
		else if (p->rlink->data != -1) { // p 혼자만 있다는거 같은데?
			p = p->rlink; // 자기 자신을 가르키기?? // 이미 있는거 아닌가?
		}
		else {
			temp->llink = p;
			temp->rlink = p->rlink;
			p->rlink->llink = temp;
			p->rlink = temp;
			break;
		}
	}
	// increae the number of nodes
	n++; // 이거는 머지?
}

template<class T>
void CircularDoublyList<T>::Merge(CircularDoublyList<T>& b) {//리스트끼리 합병
	auto current = b.first->rlink;
	while (current != b.first) { // 이러면 첫번째꺼는 어떻게 하지???
		this->Insert(current->data);
		current = current->rlink; //이동

		if (current->llink != b.first)
			b.Delete(current->llink); // 지우기
	}
}

template<class T>
bool CircularDoublyList<T>::Delete(T _data) {
	for (auto current = first; first != last; first++) {
		if (current->data == _data) { //_data가 노드가 아니라서 이렇게 비교하고 삭제
			Delete(current);
			return true;
		}
	}//이까지 하면 마지막거는 안되는거 같은데??
	return false;
}


template<class T>
int CircularDoublyList<T>::Size() const {
	return(first->data == -1) ? 0 : n); //n이 개수 같은데, 초반에 설정해야 하는거 같은데?
}

template<class T>
bool CircularDoublyList<T>::Empty() const {
	return(first->data == -1) ? 1 : 0);
}

template<class T>
T* CircularDoublyListIterator<T>::First() {
	if (current != list.first)
		return &current->data; //처음이 아니면 값을 출력
	else
		return 0; // 처음이 맞으면 0을 출력
}

template<class T>
T* CircularDoublyListIterator<T>::Next() {
	current = current->rlink;
	if (current != list.first) // 왜 계속 first에서 나누는거지?? circular가 안된다는건가??
		return &current->data;
	else
		return 0;
}

template<class T>
bool CircularDoublyListIterator<T>::NotNull() {
	if (current != list.first)
		return true;
	else
		return false;
}

template<class T>
bool CircularDoublyListIterator<T>::NextNotNull() {
	if (current->rlink != list.first)
		return true;
	else
		return false;
}

template<class T>
CircularDoublyList<T>::CircularDoublyList(const CircularDoublyList<T>& l) {
	//왜 이미 CircularDoublyList<T>를 받는다는 거지?
	if (l.first == 0) {
		first = 0;
		return;
	}
	first = new DoublyListNode<T>(l.first->data);
	DoublyListNode<T>* newnode = first;
	for (DoublyListNode<T>* current = l.first->link; current != l.first; current = current->link) {
		newnode->link = new DoublyListNode<T>(current->data);
		newnode = newnode->link;
	}
	newnode->link = first;
	//그냥 link를 설정안했는데, 이거는 그냥 r,l없이 그냥 link로 하는거 같은데?
}

template<class T>
CircularDoublyList<T>::~CircularDoublyList() {
	if (first) {
		DoublyListNode<T>* second = first->rlink;
		first->rlink = av;
		av = second;
		first = 0;
		// delete하는거 아닌가?
		// 왜 first = 0으로 하는거지?
	}
}

template<class T>
ostream& operator<<(ostream& os, CircularDoublyList<T>& l){
	CircularDoublyListIterator<T> li(l);
	if (!li.NotNull())
		return os;
	os << *li.First();
	while (li.NextNotNull())
		os << " + " << *li.Next();
	os << endl;
	return os;
	//여기 다시 체크
}

template<class T>
void CircularDoublyList<T>::Attach(T k) {
	DoublyListNode<T>* newnode = new DoublyListNode<T>(k);
	if (first == 0)
		first = last = newnode;
	else {
		newnode->link = last->link;
		last->link = newnode;
		last = newnode;
	}
}