#include <iostream>
using namespace std;

class Element {
public:
	int key;
	Element() {}
	Element(int key) : key(key) {}
};

class BstNode {
	friend class BST;
public:
	void display(int i);
	void treeprint(int i);
private:
	int LeftSize; // LeftChild�� � �޷��ִ��� ��Ÿ���� ��
	Element data;
	BstNode* LeftChild, * RightChild;
};

class BST {
public:
	BST(BstNode* init = 0) {
		root = init;
	}
	//BST& operator=(const BST&);
	bool Insert(const Element& x);
	//bool Delete(const Element&);
	BstNode* Search(const Element&);
	BstNode* IterSearch(const Element&);

	BST* ThreeWayJoin(BST* A, Element* x, BST* B);
	BST* TwoWayJoin(BST* A, BST* B);

	void treeprint() {
		cout << "\n";
		root->treeprint(1);
	}

	void display() {
		cout << "\n";
		if (root)
			root->display(1);
		else
			cout << "0\n";
	}
	Element* Split(int i, BST& B, BST& C, Element& x);
private:
	BstNode* root;
	BstNode* Search(BstNode*, const Element&);
private:
	bool DeleteLargestElement(Element& outElement);
};

void BstNode::display(int i) {
	cout << "Position " << i << ": data.key " << data.key << "\n";
	if (LeftChild)
		LeftChild->display(2 * i);
	if (RightChild)
		RightChild->display(2 * i + 1);
	// �̷��� �ϸ� recursive�� �ϰ� �ǰ�, ������ �� �����
}

Element* BST::Split(int i, BST& B, BST& C, Element& x) {//Split the binary search tree with respect to key i	
	if (!root) { // empty tree
		B.root = C.root = 0;
		return 0;
	}

	BstNode* Y = new BstNode;
	BstNode* L = Y;
	BstNode* Z = new BstNode;
	BstNode* R = Z;
	BstNode* t = root;
	while (t)
		if (i == t->data.key) { // split at t // data.key�� ����???
			L->RightChild = t->LeftChild;
			R->LeftChild = t->RightChild;
			x = t->data;
			B.root = Y->RightChild;
			delete Y;
			C.root = Z->LeftChild;
			delete Z;
			return &x;
		}
		else if (i < t->data.key) {
			R->LeftChild = t;
			R = t;
			t = t->LeftChild;
		}
		else {
			L->RightChild = t;
			L = t;
			t = t->RightChild;
		}
	L->RightChild = R->LeftChild = 0;
	B.root = Y->RightChild;
	delete Y;
	C.root = Z->LeftChild;
	delete Z;
	return 0;
} //�̰� �ٽ� Ȯ���ϱ�. // �� �𸣰���

void BstNode::treeprint(int l) {
	if (this) {
		(this->RightChild)->treeprint(l + 1);
		for (int i = 1; i <= l; i++)
			cout << "  ";
		cout << this->data.key << "\n";
		(this->LeftChild)->treeprint(l + 1);
	}// �̰͵� this�� �ִ��� Ȯ���ϰ�, �ű⼭ recursive�����°�
}

BstNode* BST::Search(BstNode* b, const Element& x) { // ���⼭ ��带 �� �ִ°���? // root���� ã������ �ִ°ǰ�?
	if (!b)
		return 0;
	if (x.key == b->data.key)
		return b;
	if (x.key < b->data.key) // �������� ���°�
		return Search(b->LeftChild, x);
	return Search(b->RightChild, x); // ���������� ���°�
	//recursive��
}

BstNode* BST::Search(const Element& x) {
	return Search(root, x);
}

BstNode* BST::IterSearch(const Element& x) {
	for (BstNode* t = root; t;) {
		if (x.key == t->data.key)
			return t;
		if (x.key < t->data.key) // �������� ���°�
			t = t->LeftChild;
		else // ���������� ���°�
			t = t->RightChild;
	}
	return 0;
}

//BstNode* BST::Search(int k) { //Search by rank;
//	BstNode* t = root;
//	while (1) {
//		if (k == t->LeftChild)
//			return t;
//		if (k < t->LeftChild)
//			t = t->LeftChild;
//		else {
//			k -= LeftSize;
//			t = t->RightChild;
//		}
//	}
//	return 0;
//}

bool BST::Insert(const Element& x) {
	BstNode* p = root;
	BstNode* q = 0;
	while (p) {
		q = p;
		if (x.key == p->data.key)
			return false; // x.key is already in t
		if (x.key < p->data.key)
			p = p->LeftChild; // �������� ���°�
		else
			p = p->RightChild; // ���������� ���°�
	} // ��������� ��ġ�� ã�°�
	p = new BstNode; // �ش���ġ�� �����Ű�� �Է� �� ����
	p->LeftChild = p->RightChild = 0; // �ʱ�ȭ
	p->data = x; // �Է�
	if (!root) //root�� ������ root�� ��ġ
		root = p;
	else if (x.key < q->data.key)
		q->LeftChild = p; // �̷��� �ؾ��� ��峢�� ���� // ���� ���
	else
		q->RightChild = p; // ��峢�� ���� // Ŭ ���
	return true;
}
