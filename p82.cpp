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
	CircularDoublyList() { //�ʱ� ����
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
		x->llink->rlink = x->rlink; //x�� ����°Ŷ� x�� llink�� x�� rlink�� ����Ű����
		x->rlink->llink = x->llink;
		delete x; // �����Ϳ� �Ҵ�Ȱ��� �ٷ� �׳� delete�� �����
	}
}

template<class T>
void CircularDoublyList<T>::Insert(DoublyListNode<T>* p, DoublyListNode<T>* x) {
	//��� p�� ��� x �����ʿ� �ֱ�
	p->llink = x; //�⺻
	p->rlink = x->rlink; // ���� x�� ����Ű���Ÿ� p�� �޾ƾ� ��
	x->rlink->llink = p; // x�� �������� ������ p�� ����Ű����
	x->rlink = p; //�⺻
	// ���� ����Ű�°� 2��, x�� �����ʿ��� 2��
}

template<class T>
void CircularDoublyList<T>::Insert(T x) {
	DoublyListNode<T>* p, * temp = new DoublyListNode<T>; //x�� ���ο� ���� �����
	temp->data = x; //����� �����Ͱ� x
	p = first; // ���� �ִ� first�� �����ͷ� ����Ų��?

	while (true) {
		if (x < p->rlink->data) { // ũ�� p �����ʿ� �ֱ�
			temp->llink = p;
			temp->rlink = p->rlink;
			p->rlink->llink = temp;
			p->rlink = temp;
			break;
		}
		else if (p->rlink->data != -1) { // p ȥ�ڸ� �ִٴ°� ������?
			p = p->rlink; // �ڱ� �ڽ��� ����Ű��?? // �̹� �ִ°� �ƴѰ�?
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
	n++; // �̰Ŵ� ����?
}

template<class T>
void CircularDoublyList<T>::Merge(CircularDoublyList<T>& b) {//����Ʈ���� �պ�
	auto current = b.first->rlink;
	while (current != b.first) { // �̷��� ù��°���� ��� ����???
		this->Insert(current->data);
		current = current->rlink; //�̵�

		if (current->llink != b.first)
			b.Delete(current->llink); // �����
	}
}

template<class T>
bool CircularDoublyList<T>::Delete(T _data) {
	for (auto current = first; first != last; first++) {
		if (current->data == _data) { //_data�� ��尡 �ƴ϶� �̷��� ���ϰ� ����
			Delete(current);
			return true;
		}
	}//�̱��� �ϸ� �������Ŵ� �ȵǴ°� ������??
	return false;
}


template<class T>
int CircularDoublyList<T>::Size() const {
	return(first->data == -1) ? 0 : n); //n�� ���� ������, �ʹݿ� �����ؾ� �ϴ°� ������?
}

template<class T>
bool CircularDoublyList<T>::Empty() const {
	return(first->data == -1) ? 1 : 0);
}

template<class T>
T* CircularDoublyListIterator<T>::First() {
	if (current != list.first)
		return &current->data; //ó���� �ƴϸ� ���� ���
	else
		return 0; // ó���� ������ 0�� ���
}

template<class T>
T* CircularDoublyListIterator<T>::Next() {
	current = current->rlink;
	if (current != list.first) // �� ��� first���� �����°���?? circular�� �ȵȴٴ°ǰ�??
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
	//�� �̹� CircularDoublyList<T>�� �޴´ٴ� ����?
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
	//�׳� link�� �������ߴµ�, �̰Ŵ� �׳� r,l���� �׳� link�� �ϴ°� ������?
}

template<class T>
CircularDoublyList<T>::~CircularDoublyList() {
	if (first) {
		DoublyListNode<T>* second = first->rlink;
		first->rlink = av;
		av = second;
		first = 0;
		// delete�ϴ°� �ƴѰ�?
		// �� first = 0���� �ϴ°���?
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
	//���� �ٽ� üũ
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