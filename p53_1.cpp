#include <iostream>
#include "polynomialListIterator.h"


using namespace std;
template <class T>
int Show(const Chain<T>& l) {
	ChainIterator<T> li(l);
	if (!li.NotNull())
		return 0;
	T retvalue = *li.First();
	cout << retvalue;
	while (!li.NextNotNull()) {
		retvalue = *li.Next();
		cout << " <- " << retvalue;
	}
	return retvalue;
}

template<class T>
int sum(const Chain<T>& l) {
	ChainIterator < T.li(l);
	if (!li.NotNull())
		return 0;
	T retvalue = *li.First();
	while (li.NextNotNull())
		retvalue += *li.Next();
	return retvalue;
}
