template<class T> class Chain; //forward declaration
template<class T> class ChainNode {
	friend class Chain<T>;
public:
	ChainNode(T element = 0);
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
	void Add(const T& element); //add a new node after first
	void Invert();
	void Concatenate(Chain<T> b);
	template <class T>
	friend ostream& operator<<(ostream&, Chain<T>); // template<class T>포함해야 comiler가 처리
	//int Minimum();
private:
	ChainNode<T>* first;
};

template<class T>
void Chain<T>::Delete() {//delete the first element after first
	ChainNode<T>* current, * next;
	if (first != nullptr) { //non-empty list
		next = first->link;
		ChainNode<T>* temp = first;
		first = next;
		delete temp; //원래 first 삭제
	}
	else
		cout << "Error - Empty List, not deleted" << endl;
}

template<class T>
void Chain<T>::Add(const T& element) { //add a new node after first
	ChainNode<T>* newnode = new ChainNode<T>(element);
	if (!first) {//insert into empty list
		first = newnode;
		return;
	}
	//insert a new node after first
	newnode->link = first;
	first = newnode;
}