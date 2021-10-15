#include <iostream>
using namespace std;

template<class T> class Chain; //forward 선언
template<class T> class ChainIterator; 

template<class T> class ChainNode {
	friend class Chain<T>; // Chain의 public 함수에서 노드를 추가 또는 삭제하기 위해서
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
	void Delete(); //first가 가리키는 노드를 삭제하고 data를 return
	int Length();
	void Add(const T& element); // add a new node after first // 참조형 변수&
	void invert();
	void Concatenate(Chain<T> b);
	template <class T>
	friend ostream& operator << (ostream&, Chain<T>); // template <class T>포함해야 compier가 처리
	//int Minimum();
private:
	ChainNode* first; // 첫번째 노드를 가르킴
};

template<class T>
class ChainIterator {
public:
	ChainIterator(const Chain<T>& l) : list(l), current(l.first) {};
	//dereferencing operators
	T& operator *() const {
		return current->data; // 오버로딩
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
	const Chain<T>& list; //refers to an existing list // 레퍼런스로 하기때문
	ChainNode<T>* current; //points to a node in list
};

template<class T>
void Chain<T>::Delete() {//delete the first element after first
	ChainNode<T>* current, * next; //ChainNode의 data를 설정
	if (first != nullptr) { //non-empty list
		next = first->link; //두번째
		ChainNode<T>* temp = first; // 첫번째꺼
		first = next; // 두번째가 된 next를 가짐으로써, first가 두번째부터 시작
		delete temp; // 예전 first 삭제
	}
	else
		cout << "Error - Empty List. not deleted" << endl;
}

template<class T>
void Chain<T>::Add(const T& element) { //변수를 reference로 사용하겠다는 거
	ChainNode<T>* newnode = new ChainNode<T>(element); // element를 일단 node로 만들고 그리고 newnode가 그거를 가르킨다는거
	if (!first) { //insert into empty list // first가 없다는거는 비어있다는거
		first = newnode;
		return;
	}
	newnode->link = first; //newnode의 link가 first를 가르키도록 하는거
	first = newnode; //이거 중요
}

template<class T>
void Chain<T>::invert() {
	ChainNode<T>* p = first, * q = 0; // q에서 p로 가는걸로 invert시키겠다는 것
	while (p) {
		ChainNode<T>* r = q; // r추가
		q = p; // q는 p를 따라서 이동
		p = p->link; // 다음으로 이동
		q->link = r; // q의 link는 이전 q를 가르킴
	}
	first = q; // 결국 끝까지 따라오고, 그것이 first임 // first가 되면서, q의 노드와 링크만 신경쓰는거
}

template<class T>
void Chain<T>::Concatenate(Chain<T> b) {
	ChainNode<T>* p;
	if (!first) { // 원래 값이 없으면
		first = b.first; // 그냥 b만
		return;
	}
	if (b.first) { //b가 존재한다면
		for (p = first; p->link; p = p->link); // 기존 노드의 마지막까지 진입
		p->link = b.first; // 마지막 노드를 b.first를 가르키도록 하는거
	}
}

//pre-increment


template <class T>
int Show(const Chain<T>& l) {
	ChainIterator<T> li(l); // li is associated with list l
	if (!li.NotNull())
		return 0; // empty list, return 0;
	T retvalue = *li.First(); //get first element 
	while (li.NextNotNull()) { //make sure that next element exists // 뒤에 계속 있을때까지
		retvalue = *li.Next(); //iterator를 통해서 다음으로 넘어가는거
		cout << " <- " << retvalue;
	}
	return retvalue;
}