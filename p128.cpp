using namespace std;

const int HeapSize = 1000;
enum Boolean {FALSE, TRUE};

template <class Type>
class Element {
public:
	Type key;

	Element() {}
	Element(Type key) : key(key) {}
};

template <class Type>
class MaxPQ {
public:
	virtual void Insert(const Element<Type>&) = 0;
	virtual Element<Type>* DeleteMax(Element<Type>)
};
