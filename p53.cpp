// iterator class를 사용하는 실습
#include<iostream>
//#include "Chain.h"

using namespace std;

template<class T>
int Show(const Chain<T>& l) {
	ChainIterator<T> li(l); //li is associated with list l
	if (!li.NotNull())
		return 0; //empty list, return 0;
	T retvalue = *li.First(); //get first element
	cout << retvalue;
	while (li.NextNotNull()) { //make sure that next element exists
		retvalue = *li.Next();
		cout << " <- " << retvalue;
	}
}