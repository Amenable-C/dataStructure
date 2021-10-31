#include <iostream>
using namespace std;

int GetData();

class GenList; // forward declaration

class GenListNode {
	friend class GenList;
	friend int operator==(const GenList&, const GenList&);
	friend int equal(GenListNode*, GenListNode*);
private:
	GenListNode* link;
	bool tag; //0 for data, 1 for dlink, 2 for ref
	union {
		int data;
		GenListNode* dlink;
		int ref;
	};
};

class GenList {
	friend int operator==(const GenList&, const GenList&);
	friend int equal(GenListNode*, GenListNode*);
private:
	GenListNode* first;
	static GenListNode* av;
	GenListNode* Copy(GenListNode*);
	void Visit(GenListNode*); //driver
	int Depth(GenListNode*);
	GenListNode* MakeList(GenListNode*);
	void Delete(GenListNode*);
public:
	void Copy(const GenList&);
	void Visit(const GenList&); //workhorse
	~GenList();
	int Depth();
	void MakeList();
};

GenList::~GenList() {
	//Each head node has a reference count. We assume first != 0
	Delete(first);
	first = 0; // 왜 first를 0으로 주는거지? 그냥 delete만 하면 안되는건가?
}

void GenList::Copy(const GenList& l) {
	first = Copy(l.first); // 그냥 바로 받아버리는거
}

void GenList::Visit(const GenList& l) {
	cout << "(";
	Visit(l.first); // 한번만 되는거 아닌가? 들어가면 재귀로 도는건가?
	cout << ")";
}

//GenList::~GenList() {
//	Delete(first);
//	first = 0;
//}

int operator==(const GenList& l, const GenList& m) {
	return equal(l.first, m.first);
}

//Workhorse - 반환시에 문제 발생함
void GenList::Delete(GenListNode* x) {
	if (x->tag == 2)
		x->ref--;
	if (!x->ref) {
		GenListNode* y = x;
		while (y->link) {
			y = y->link; // 이동
			if (y->tag == 1) // dlink라는거
				Delete(y->dlink);
		}
		y->link = av;
		av = x;
	}
}

int GenList::Depth() {
	return Depth(first);
}

void GenList::MakeList() {
	first = MakeList(first);
}

GenListNode* GenList::MakeList(GenListNode s) {
	GenListNode* p, * q, * r;
	bool tag_head = true;
	q = new GenListNode;
	r = q;
	while (int x = GetData()) {
		//if x == 0, no more entry
		if (x == 1) {
			// make down link
			if (tag_head) {
				q->dlink = MakeList(q);
				q->tag = true;
				q->link = 0;
				tag_head = false;
				continue;
			}
			else {
				p = new GenListNode;
				q->link = p;
				p->tag = true;
				q = p;
				q->dlink = MakeList(q);
			}
		}
		else {
			if (tag_head) {
				q->data = x;
				q->tag = false;
				q->link = 0;
				tag_head = false;
			}
			else {
				p = new GenListNode;
				p->data = x;
				p->tag = false;
				p->link = 0;
				q->link = p;
				q = p;
			}
		}
	}
	return r;
}

GenListNode* GenList::Copy(GenListNode* p) {
	GenListNode* q = 0;
	if (p) {
		q = new GenListNode;
		q->tag = p->tag;
		if (!p->tag)
			q->data = p->data;
		else
			q->dlink = Copy(p->dlink);
		q->link = Copy(p->link);
	}
	return q;
}