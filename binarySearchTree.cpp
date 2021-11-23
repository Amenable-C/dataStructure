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
	bool Delete(const Element& x); // const �ٿ��� �ϳ�?
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
			cout << "    ";
		// cout << this->data.key << "\n"; // �̰� �´°� 
		cout << this->data.key << "[" << this->LeftSize << "]" << "\n"; // leftsize �� �´��� Ȯ��
		(this->LeftChild)->treeprint(l + 1); // ���⼭ "l-1" �ؾ��ϴ°� �ƴѰ�?
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
	//BstNode* changingPoint = 0; // root��� ���ص� �ɰ� ������
	//int toChecktheChangingPoint = 0;
	while (p) {
		q = p;
		if (x.key == p->data.key)
			return false; // x.key is already in t
		if (x.key < p->data.key) {
			p->LeftSize = p->LeftSize + 1;
			p = p->LeftChild; // �������� ���°�
		}
		else {
			p = p->RightChild; // ���������� ���°�
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
	while (p->data.key != x.key) { // �̷��� key�� �ؾ��� ã������ �ϴ� ������ ���ϴ� �ǰ�?
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
		if (p == 0) {
			cout << "There is no delete value" << endl;
			return true;
		}
	}

	if (p == root) { 
		delete p;
		return true;
	}
	
	if (p->LeftChild && p->RightChild) {
		forLink = p; // ������ �ϴ� p
		p = p->RightChild;
		while (p->LeftChild) {
			p = p->LeftChild;
		}
		p->LeftChild = forLink->LeftChild; // ���� p�� parent�� �����ϴ°� �ϳ��� ����
		childNodeForQ = forLink->RightChild; // �ᱹ �̷��� �༭ ���� q�� �����ϰ��� �ϴ°�
	}
	else if (p->RightChild) { // RightChild�� �ִ°� // LeftSize �߰������� ���X
		childNodeForQ = p->RightChild;
	}
	else if(p->LeftChild) { // LeftChild�� �ִ°� // LeftSize �߰������� ���X 
		childNodeForQ = p->LeftChild;
	}
	else { // �Ѵ� ���°� // LeftSize �߰������� ��� X
		q->LeftChild = 0;
		q->RightChild = 0;
		delete p; // �̷��Ը� �س��� ���ֵ� �Ǵ°ǰ�?
		return true;
	}
	
	// q�� childNodeForQ �������ֱ�
	// ���� p�� q�� RightChild���� LeftChild���� �𸣹Ƿ� Ȯ���ؼ� �������ֱ�
	if (p == 0) {
		q->LeftChild = p;
	}
	else {
		q->RightChild = p;
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
} // A�� ����, B�� ���������� �ؼ� ��ģ��

BST* BST::TwoWayJoin(BST* A, BST* B) {
	if (!A)
		return B;
	if (!B)
		return A;
	// ������ �ϳ��� ��� �Ѵٴ°�
	Element midEle;
	A->DeleteLargestElement(midEle); // root�� ����� ���ؼ� �ϴ� ����°�

	// x= largest element of A or smallest element of B
	return ThreeWayJoin(A, &midEle, B);  // ���⼭ ������ ������� �������� �¿� ���߱�
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
		cout << "binary search tree. Select : 1 insert, 2 delete, 3 display, 4 split and join, >= 5 exit" << endl;
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
		case 5:
			exit(1);
			break;
		}
	} while (select < 5);
	return 0;
}