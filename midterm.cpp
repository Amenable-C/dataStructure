#include <iostream>
using namespace std;

template<class T> class Chain; //forward ����
template<class T> class ChainIterator; 

template<class T> class ChainNode {
	friend class Chain<T>; // Chain�� public �Լ����� ��带 �߰� �Ǵ� �����ϱ� ���ؼ�
	friend class ChainIterator<T>;
public:
	ChainNode(T element = 0);
private:
	T data;
	ChainNode<T>* link;
};

template<class T> class Chain {
	friend class ChainIterator<T>;
public:
	//list operations
	Chain() { first = 0; }
	void Delete(); //first�� ����Ű�� ��带 �����ϰ� data�� return
	int Length();
	void Add(const T& element); // add a new node after first // ������ ����&
	void invert();
	void Concatenate(Chain<T> b);
	template <class T>
	friend ostream& operator << (ostream&, Chain<T>); // template <class T>�����ؾ� compier�� ó��
	//int Minimum();
private:
	ChainNode* first; // ù��° ��带 ����Ŵ
};

template<class T>
class ChainIterator {
public:
	ChainIterator(const Chain<T>& l) : list(l), current(l.first) {};
	//dereferencing operators
	T& operator *() const {
		return current->data; // �����ε�
	}
	T* operator ->() const {
		return &current->data;
	}
	//increment
	ChainIterator<T>& operator ++(); //preincrement
	ChainIterator<T> operator ++(int); //post increment
	bool NotNull(); //check the current element in list is non-null
	bool NextNotNull(); //check the next element in list is non-null

	T* First(); //check a pointer to the first element of list
	T* Next(); //return a pointer to the next element of list
private:
	const Chain<T>& list; //refers to an existing list // ���۷����� �ϱ⶧��
	ChainNode<T>* current; //points to a node in list
};

template<class T>
void Chain<T>::Delete() {//delete the first element after first
	ChainNode<T>* current, * next; //ChainNode�� data�� ����
	if (first != nullptr) { //non-empty list
		next = first->link; //�ι�°
		ChainNode<T>* temp = first; // ù��°��
		first = next; // �ι�°�� �� next�� �������ν�, first�� �ι�°���� ����
		delete temp; // ���� first ����
	}
	else
		cout << "Error - Empty List. not deleted" << endl;
}

template<class T>
void Chain<T>::Add(const T& element) { //������ reference�� ����ϰڴٴ� ��
	ChainNode<T>* newnode = new ChainNode<T>(element); // element�� �ϴ� node�� ����� �׸��� newnode�� �װŸ� ����Ų�ٴ°�
	if (!first) { //insert into empty list // first�� ���ٴ°Ŵ� ����ִٴ°�
		first = newnode;
		return;
	}
	newnode->link = first; //newnode�� link�� first�� ����Ű���� �ϴ°�
	first = newnode; //�̰� �߿�
}

template<class T>
void Chain<T>::invert() {
	ChainNode<T>* p = first, * q = 0; // q���� p�� ���°ɷ� invert��Ű�ڴٴ� ��
	while (p) {
		ChainNode<T>* r = q; // r�߰�
		q = p; // q�� p�� ���� �̵�
		p = p->link; // �������� �̵�
		q->link = r; // q�� link�� ���� q�� ����Ŵ
	}
	first = q; // �ᱹ ������ �������, �װ��� first�� // first�� �Ǹ鼭, q�� ���� ��ũ�� �Ű澲�°�
}

template<class T>
void Chain<T>::Concatenate(Chain<T> b) {
	ChainNode<T>* p;
	if (!first) { // ���� ���� ������
		first = b.first; // �׳� b��
		return;
	}
	if (b.first) { //b�� �����Ѵٸ�
		for (p = first; p->link; p = p->link); // ���� ����� ���������� ����
		p->link = b.first; // ������ ��带 b.first�� ����Ű���� �ϴ°�
	}
}

//pre-increment


template <class T>
int Show(const Chain<T>& l) {
	ChainIterator<T> li(l); // li is associated with list l
	if (!li.NotNull())
		return 0; // empty list, return 0;
	T retvalue = *li.First(); //get first element 
	while (li.NextNotNull()) { //make sure that next element exists // �ڿ� ��� ����������
		retvalue = *li.Next(); //iterator�� ���ؼ� �������� �Ѿ�°�
		cout << " <- " << retvalue;
	}
	return retvalue;
}