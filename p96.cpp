#include <iostream>
#include <string>
#include <cctype>
using namespace std;

enum boolean{FALSE, TRUE};
struct Data {
	int id; // id = 0, 1, 2, if the node contains char, int ,float
	union {
		int i;
		char c;
		float f;
	};
	bool operator==(Data const d);
};

/*
class CombinedNode {
	//use union to merge different node types into one class definition
	friend class List;
	friend class ListIterator;
private:
	Data data;
	CombinedNode* link;
};

class List {
	friend class listIterator;
public:
private:
	CombinedNode* first;
};
*/

class Node { //���� �׳� ��尡 �ְ�, combinednode�� �ξ �پ��� Ÿ���� ����Ѵ� �̰ǰ�?
	friend class List;
	friend class ListIterator;
protected:
	Node* link;
	virtual Data GetData() = 0;
};

template<class Type>
class DerivedNode : public Node {
	friend class List;
	friend class ListIterator;
public:
	DerivedNode(Type item) : data(item) {
		link = 0;
	}
private:
	Type data;
	Data GetData();
};

class List {
	friend class ListIterator;
public:
	List() {
		first = 0;
	}
	~List() {};
	void Add();
	void Delete();
	Node* Search(Data);
	int Equal(const List&);
	void Copy(const List&);
private:
	Node* first;
	Node* Copy(Node*);
};

class ListIterator {
public:
	ListIterator(const List& l) : list(l), current(l.first) {};
	ListIterator& operator ++();
	ListIterator operator ++(int);
	Data* First();
	Node* Next();
	bool NotNull();
	bool NextNotNull();
	Data GetCurrent();
	Node* CurrentPointer();

private:
	const List& list;
	Node* current;
	Data temp;
};

bool Data::operator==(Data const d) {
	switch (d.id) {
	case 0:
		if (this->c == d.c)
			return TRUE;
		break;
	case 1:
		if (this->i == d.i)
			return TRUE;
		break;
	case 2:
		if (this->f == d.f)
			return TRUE;
		break;
	}
	return FALSE;
}

Data DerivedNode<char>::GetData() {
	Data t;
	t.id = 0;
	t.c = data;
	return t;
}

Data DerivedNode<int>::GetData() {
	Data t;
	t.id = 1;
	t.i = data;
	return t;
}

Data DerivedNode<float>::GetData() {
	Data t;
	t.id = 2;
	t.f = data;
	return t;
}

void List::Add() {
	int value;
	float num;
	char c;
	cout << "Please input data type. 0 = char, 1 = int, 2 = float" << endl;
	cin >> value;
	if(!first)
		switch (value) {
		case 0:
			cin >> c;
			first = new DerivedNode<char>(c);
			break;
		case 1:
			cin >> value;
			first = new DerivedNode<int>(value);
			break;
		case 2:
			cin >> num;
			first = new DerivedNode<float>(num);
			break;
		default:
			break;
		}
	else {
		switch (value) {
		case 0:{
			cin >> c;
			Node* n = new DerivedNode<char>(c);
			n->link = first;
			first = n;
			break;
		}
		case 1:{
			cin >> value;
			Node* na = new DerivedNode<int>(value);
			na->link = first;
			first = na;
			break;
		}
		case 2:{
			cin >> num;
			Node* nb = new DerivedNode<float>(num);
			nb->link = first;
			first = nb;
			break;
		}
		default:
			break;
		}
	}
}

void List::Delete() {
	int value;
	char c;
	float num;
	Data tmp;

	if (first == NULL) cout << " List is empty " << endl;
	else {
		cout << "Please input data type. 0 = char, 1 = int, 2 = float" << endl;
		cin >> value;
		cin.clear(); // ���λ����÷��׸� �ʱ�ȭ ���� cin�� �ùٸ� ������ �̾������ �Ѵ�?
		switch (value) {
		case 0:
			cin >> c;
			tmp.c = c;
			tmp.id = 0;
			break;
		case 1:
			cin >> value;
			tmp.i = value;
			tmp.id = 1;
			break;
		case 2:
			cin >> num;
			tmp.f = num;
			tmp.id = 2;
			break;
		default:
			break;
		}
		// ��������� �ϴ� ���� ������ �⺻�����ϴ°�
		Node* s = Search(tmp); // Search�ϸ� ��� ������ ���� ��ȯ
		if (s == first && !(s->link->GetData() == tmp)) {
			Node* tmp;
			tmp = s;
			s = s->link;
			first = s;
			delete tmp;
		}
		else if (s) {
			Node* tmp;
			tmp = s->link; // ã�� ���� link�� �޵���
			s->link = s->link->link; // �������� �Ѿ
			delete tmp; // ��.. s�� link�� �����ϴ°� �´°ǰ�? s�� �����ؾ��ϴ°� �ƴ�? s->link�� s �����ƴ�?
		}
	}
}

Node* List::Search(Data tmp) {
	ListIterator li(*this);
	while (li.NotNull()) {
		if (li.GetCurrent() == tmp)
			return li.CurrentPointer();
		else if (li.Next()->GetData() == tmp) // ??
			return li.CurrentPointer();
		++li;
	}
	return NULL;
}

Data* ListIterator::First() {
	if (list.first) {
		temp = list.first->GetData();
		return &temp;
	}
	return 0;
}

Data ListIterator::GetCurrent(){
	return current->GetData();
}

Node* ListIterator::Next() {
	return current->link;
}

Node* ListIterator::CurrentPointer() {
	return current;
}

ListIterator& ListIterator:: operator++() {
	current = current->link;
	return *this;
}

ListIterator ListIterator::operator++(int) {
	ListIterator old = *this;
	current = current->link;
	return old;
}

bool ListIterator::NotNull() {
	if (current)
		return TRUE;
	else
		return FALSE;
}

bool ListIterator::NextNotNull() {
	if (current->link)
		return TRUE;
	else
		return FALSE;
}

ostream& operator<<(ostream& os, Data& retvalue) {
	switch(retvalue.id) {
	case 0:
		cout << retvalue.c;
		break;
	case 1:
		cout << retvalue.i;
		break;
	case 2:
		cout << retvalue.f;
		break;
	default:
		break;
	}
	return os;
}

void PrintAll(const List& l) {
	ListIterator li(l);
	if (!li.NotNull())
		return;
	Data retvalue = *li.First();
	cout << retvalue;
	if (li.NextNotNull())
		cout << " + ";
	while(li.NextNotNull() == true) {
		++li; //current�� ������Ŵ
		//retvalue = retvalue + *li.Next(); // �������� ���ϴ°� ������?
		retvalue = li.GetCurrent(); // ���� current�� ����Ű�� node�� ���� ������
		cout << retvalue;
		if (li.NextNotNull()) // ������ ��� �����ٴ� ��
			cout << " + ";
	}
}
//float sum(l); // sum of all floating points

int List::Equal(const List& l) {
	// �ϴ� ���� ���� ���ϰ� �� �ϱ�
	ListIterator liOrigin(*this);
	ListIterator liCompare(l);
	Data originValue = *liOrigin.First();
	Data compareValue = *liCompare.First();
	while (originValue == compareValue) {
		if (originValue.id != compareValue.id) {
			return 1;
		}
		if (liOrigin.NextNotNull() && liCompare.NextNotNull()) {
			return 0;
		}
		++liOrigin;
		++liCompare;
	}
	return 1;
	
}
void List::Copy(const List& l) {
	first = l.first;
}

//Node* List::Copy(Node* p) {
//	Node* q = 0;
//	Data tmp = p->GetData();
//	//Data tmp = ;
//	if (p) {
//			switch (tmp.id) {
//			case 0:
//				q = new DerivedNode<char>(tmp.c);
//			case 1:
//				q = new DerivedNode<int>(tmp.i);
//			case 2:
//				q = new DerivedNode<float>(tmp.f);
//			}
//			
//			//q->GetData = p->GetData();
//			q->link = Copy(p->link);
//		
//		//tmp = p->link->GetData();
//		//tmp = p->link;
//		q->link = p->link;
//	}
//	return q;
//}

int main(void) {
	List l;
	List m;
	//implement heterogeneous linked stacks and queus
	char select;
	int max = 0, x = 0;
	cout << "Select comman a: add data, d: delete data, p: print all, q: quit, c : copy, e : equal =>";
	cin >> select;
	while (select != 'q') {
		switch (select) {
		case 'a':
			l.Add();
			break;
		case 'd':
			l.Delete();
			break;
		case 'p':
			cout << "print all: ";
			PrintAll(l);
			cout << endl;
			break;
		case 'q':
			cout << "Quit" << endl;
			break;
		case 'c':
			cout << "l : origin, m : copy" << endl;
			m.Copy(l);
			cout << "The m, the copy version, is : ";
			PrintAll(m);
			cout << endl;
			break;
		case 'e':
			cout << "comparing the l and m(= l's copy version)" << endl;
			cout << "equal : 0, ineqaul : 1" << endl;
			cout << l.Equal(m) << endl;
			break;
		default:
			cout << "WRONG INPUT " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
		cout << "Select comman a: add data, d: delete data, p: print all, q: quit, c : copy, e : equal =>";
		cin >> select;
	}
	system("pause");
	return 0;
}