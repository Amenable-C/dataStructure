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
	int LeftSize; // �ڽ� + LeftChild�� � �޷��ִ��� ��Ÿ���� ��
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
	bool Delete(const Element& x); 
	//bool Delete(const Element&);
	BstNode* Search(const Element&);
	BstNode* IterSearch(const Element&);
	BstNode* Search(int k);

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
		if (i == t->data.key) { 
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
} 

void BstNode::treeprint(int l) {
	if (this) {
		(this->RightChild)->treeprint(l + 1);
		for (int i = 1; i <= l; i++)
			cout << "    ";
		// cout << this->data.key << "\n"; // origin
		cout << this->data.key << "[" << this->LeftSize << "]" << "\n"; // leftsize�� �Բ� ��Ÿ���� ���� �뵵
		(this->LeftChild)->treeprint(l + 1); 
	}
}

BstNode* BST::Search(BstNode* b, const Element& x) { 
	if (!b)
		return 0;
	if (x.key == b->data.key)
		return b;
	if (x.key < b->data.key) 
		return Search(b->LeftChild, x);
	return Search(b->RightChild, x); 
	//recursive��
}

BstNode* BST::Search(const Element& x) {
	return Search(root, x);
}

BstNode* BST::IterSearch(const Element& x) {
	for (BstNode* t = root; t;) {
		if (x.key == t->data.key)
			return t;
		if (x.key < t->data.key) 
			t = t->LeftChild;
		else 
			t = t->RightChild;
	}
	return 0;
}

BstNode* BST::Search(int k) { //Search by rank;
	BstNode* p = root;
	BstNode* q = 0;
	int kRank = 0;

	while (p) {
		q = p;
		if (k == p->LeftSize) {
			cout << k << "��° : " << p->data.key << endl;
			return 0; 
		}
		if (k < p->LeftSize) {
			p = p->LeftChild; 
		}
		else {
			kRank = kRank + p->LeftSize;
			p = p->RightChild; 
			break;
		}
	}

	while (p) {
		if (k == kRank + p->LeftSize) {
			cout << k << "��° : " << p->data.key << endl;
			return 0; 
		}

		if (k > kRank + p->LeftSize) {
			kRank = kRank + p->LeftSize;
			p = p->RightChild;
		}
		else { 
			p = p->LeftChild;
		}
	}
	cout << "K is wrong" << endl;
	return 0;
}

bool BST::Insert(const Element& x) {
	BstNode* p = root;
	BstNode* q = 0;
	while (p) {
		q = p;
		if (x.key == p->data.key){
			cout << "Insert value already exists" << endl;
			return false; // x.key is already in t
		}
		if (x.key < p->data.key) {
			p = p->LeftChild; 
		}
		else {
			p = p->RightChild;
		}
	}
	p = root;
	q = 0;
	while (p) {
		q = p;
		if (x.key == p->data.key)
			return false; // x.key is already in t
		if (x.key < p->data.key) {
			p->LeftSize = p->LeftSize + 1;
			p = p->LeftChild; 
		}
		else {
			p = p->RightChild;
		}
	} // ��������� ��ġ�� ã�°�
	p = new BstNode; // �ش���ġ�� �����Ű�� �Է� �� ����
	p->LeftChild = p->RightChild = 0; // �ʱ�ȭ
	p->LeftSize = 1;
	p->data = x; // �Է�
	if (!root) { //root�� ������ root�� ��ġ
		root = p;
	}
	else if (x.key < q->data.key){
		q->LeftChild = p; // �̷��� �ؾ��� ��峢�� ���� // ���� ���
	}
	else{
		q->RightChild = p; // ��峢�� ���� // Ŭ ���
	}
	return true;
}

bool BST::Delete(const Element& x) {
	BstNode* p = root; // �̰Ÿ� deletedNode�� �ϴ°�
	BstNode* q = 0;
	BstNode* childNodeForQ = 0;
	BstNode* forLink = 0;
	int rightLeft = 0; // q�� �������� p�� RightChild���� LeftChild���� Ȯ���ϱ� ���� �뵵 // R = 1, L = 0

	while(p->data.key != x.key) { // �ϴ� ���� �ִ��� ���� Ȯ��
		q = p;
		if (p->data.key > x.key) {
			p = p->LeftChild;
		}
		else { // p->data.key < x.key �� ���
			p = p->RightChild;
		}
		if (p == 0) {
			cout << "There is no delete value" << endl;
			return true;
		}
	}

	p = root;
	q = 0;
	while (p->data.key != x.key) { 
		q = p;
		if (p->data.key > x.key) {
			p->LeftSize = p->LeftSize - 1;
			p = p->LeftChild;
			rightLeft = 0;
		}
		else { // p->data.key < x.key �� ���
			p = p->RightChild;
			rightLeft = 1;
		}
	}

	if (p == root) { 
		delete p;
		return true;
	}
	
	if (p->LeftChild && p->RightChild) { // �� �� ���� ��� ������� ��
		forLink = p; // ������ �ϴ� p
		p = p->RightChild; 
		BstNode* qq = 0;
		while (p->LeftChild) { // delete�Ǵ� ��带 �������� rightchild�� ���� ���� ��带 leftchild�� ����
			qq = p;
			p = p->LeftChild;
		}
		qq->LeftChild = forLink->LeftChild; // ����
		childNodeForQ = forLink->RightChild; // �ᱹ �̷��� �༭ ���� q�� �����ϰ��� �ϴ°�
	}
	else if (p->RightChild) { // RightChild�� �ִ°� 
		childNodeForQ = p->RightChild;
	}
	else if(p->LeftChild) { // LeftChild�� �ִ°� 
		childNodeForQ = p->LeftChild;
	}
	else { // �Ѵ� ���°� 
		if (rightLeft == 0) {
			q->LeftChild = 0;
		}
		else {
			q->RightChild = 0;
		}
		delete p; 
		return true;
	}
	delete p;
	// q�� childNodeForQ �������ֱ�
	// ���� p�� q�� RightChild���� LeftChild���� �𸣹Ƿ� Ȯ���ؼ� �������ֱ�
	if (rightLeft == 0) {
		q->LeftChild = childNodeForQ;
	}
	else {
		q->RightChild = childNodeForQ;
	}



	
}

bool BST::DeleteLargestElement(Element& outElement) {
	BstNode* deletedNode = nullptr;
	if (!root)
		return false;
	if (!root->RightChild) { // the tree does not have right sub-tree // �������� ���⶧����, root�� ���� ū��
		deletedNode = root; // ���� ū���� root�� �����ϰ�
		root = root->LeftChild; // ���� �ؿ����� root �� �Ǵ°�
	}
	else {
		BstNode* parentNode = root, * currNode = root;
		while (currNode->RightChild) { // ���� ū�Ÿ� ã�� ������ ��� ���������� ���� ��
			parentNode = currNode;
			currNode = currNode->RightChild;
		}
	}
	outElement = deletedNode->data;
	delete deletedNode;
	deletedNode = nullptr;
	return true;
}

BST* BST::ThreeWayJoin(BST* A, Element* x, BST* B) {
	// To be implemented
	BstNode* newNode = new BstNode;
	newNode->data = *x;
	newNode->LeftChild = A->root;
	newNode->RightChild = B->root;

	BST* newTree = new BST;
	newTree->root = newNode;
	return newTree;
} 

BST* BST::TwoWayJoin(BST* A, BST* B) {
	if (!A)
		return B;
	if (!B)
		return A;
	
	Element midEle;
	A->DeleteLargestElement(midEle); 

	// x= largest element of A or smallest element of B
	return ThreeWayJoin(A, &midEle, B);  
}

int main() {
	int select = 0;
	int data = 0;
	BST tree;
	BST splitTree1;
	BST splitTree2;
	BST* joinTree = nullptr;
	Element ele;

	Element* tempEle;

	do {
		cout << "binary search tree. Select : 1 insert, 2 delete, 3 display, 4 Search(k) 5 split and join, >= 6 exit" << endl;
		cin >> select;
		switch (select) {
		case 1:
			cout << "input value: ";
			cin >> data;
			tree.Insert(Element(data));
			tree.treeprint();
			break;
		case 2:
			cout << "delete value: ";
			cin >> data;
			tree.Delete(Element(data));
			tree.treeprint();
			break;
		case 3:
			tree.display();
			break;
		case 4:
			cout << "put the Kth rank" << endl;
			int k;
			cin >> k;
			tree.Search(k);
			break;
		case 5:
			cout << "input splited tree note: ";
			cin >> data;
			tempEle = tree.Split(data, splitTree1, splitTree2, ele);
			if (tempEle != 0) {
				cout << "----------------ThreeWayJoinTree----------------" << endl;
				cout << "mid element = " << data << endl;
				cout << "splited tree 1: " << endl;
				splitTree2.treeprint();
				cout << "splited tree 2: " << endl;
				splitTree2.treeprint();
				cout << "join the splited trees: " << endl;
				joinTree = tree.ThreeWayJoin(&splitTree1, tempEle, &splitTree2);
				joinTree->treeprint();
				cout << "----------------TwoWayJoinTree----------------" << endl;
				cout << "splited tree 1: " << endl;
				splitTree1.treeprint();
				cout << "splited tree 2: " << endl;
				splitTree2.treeprint();
				cout << "join the splited trees: " << endl;
				joinTree = tree.TwoWayJoin(&splitTree1, &splitTree2);
				joinTree->treeprint();
			}
			break;
		case 6:
			exit(1);
			break;
		}
	} while (select < 6);
	return 0;
}