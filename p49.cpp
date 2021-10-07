template<class T>
class ChainIterator {
public:
	ChainIterator(const Chain<T>& I) : list(I), current(I, first) {};
	//dereferencing operators
	T& operator *() const {
		return current->data;
	}
	T* operator-> const{
		return &current->data;
	}
	//increment
	ChainIterator<T>& operator ++(); //preincrement
	ChainIterator<T> operator ++(int); //post increment
	bool NotNull(); //check the current element in list is non-null
	bool NextNotNull(); // check the next element in list in non-null

	T* First(); //return a pointer to the first element of list
	T* Next(); //return a pointer to the next element of list
private:
	const Chain<T>& list; // refers to an existing list
	ChainNode<T>* current; //points to a node in list
};