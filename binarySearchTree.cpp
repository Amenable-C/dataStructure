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
	int LeftSize; // LeftChild가 몇개 달려있는지 나타내는 것
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
	bool Delete(const Element& x); // const 붙여야 하나?
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
	// 이렇게 하면 recursive로 하게 되고, 끝까지 다 출력함
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
		if (i == t->data.key) { // split at t // data.key가 머지???
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
} //이거 다시 확인하기. // 잘 모르겠음

void BstNode::treeprint(int l) {
	if (this) {
		(this->RightChild)->treeprint(l + 1);
		for (int i = 1; i <= l; i++)
			cout << "    ";
		// cout << this->data.key << "\n"; // 이게 맞는거 
		cout << this->data.key << "[" << this->LeftSize << "]" << "\n"; // leftsize 잘 맞는지 확인
		(this->LeftChild)->treeprint(l + 1); // 여기서 "l-1" 해야하는거 아닌가?
	}// 이것도 this가 있는지 확인하고, 거기서 recursive돌리는거
}

BstNode* BST::Search(BstNode* b, const Element& x) { // 여기서 노드를 왜 주는거지? // root부터 찾을려고 주는건가?
	if (!b)
		return 0;
	if (x.key == b->data.key)
		return b;
	if (x.key < b->data.key) // 왼쪽으로 가는거
		return Search(b->LeftChild, x);
	return Search(b->RightChild, x); // 오른쪽으로 가는거
	//recursive임
}

BstNode* BST::Search(const Element& x) {
	return Search(root, x);
}

BstNode* BST::IterSearch(const Element& x) {
	for (BstNode* t = root; t;) {
		if (x.key == t->data.key)
			return t;
		if (x.key < t->data.key) // 왼쪽으로 가는거
			t = t->LeftChild;
		else // 오른쪽으로 가는거
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
	//BstNode* changingPoint = 0; // root라고 안해도 될거 같은데
	//int toChecktheChangingPoint = 0;
	while (p) {
		q = p;
		if (x.key == p->data.key)
			return false; // x.key is already in t
		if (x.key < p->data.key) {
			p->LeftSize = p->LeftSize + 1;
			p = p->LeftChild; // 왼쪽으로 가는거
		}
		else {
			p = p->RightChild; // 오른쪽으로 가는거
		}
	} // 여기까지는 위치를 찾는거
	p = new BstNode; // 해당위치에 연결시키는 입력 및 과정
	p->LeftChild = p->RightChild = 0; // 초기화
	p->LeftSize = 1;
	p->data = x; // 입력
	if (!root) { //root가 없으면 root에 위치
		root = p;
	}
	else if (x.key < q->data.key){
		q->LeftChild = p; // 이렇게 해야지 노드끼리 연결 // 작을 경우
	}
	else{
		q->RightChild = p; // 노드끼리 연결 // 클 경우
	}
	return true;
}

bool BST::Delete(const Element& x) {
	BstNode* p = root; // 이거를 deletedNode로 하는거
	BstNode* q = 0;
	BstNode* childNodeForQ = 0;
	BstNode* forLink = 0;
	int rightLeft = 0; // q를 기준으로 p가 RightChild인지 LeftChild인지 확인하기 위한 용도 // R = 1, L = 0

	while(p->data.key != x.key) { // 일단 값이 있는지 먼저 확인
		q = p;
		if (p->data.key > x.key) {
			p = p->LeftChild;
		}
		else { // p->data.key < x.key 인 경우
			p = p->RightChild;
		}
		if (p == 0) {
			cout << "There is no delete value" << endl;
			return true;
		}
	}

	p = root;
	q = 0;
	while (p->data.key != x.key) { // 이렇게 key로 해야지 찾을려고 하는 값들을 비교하는 건가?
		q = p;
		if (p->data.key > x.key) {
			p->LeftSize = p->LeftSize - 1;
			p = p->LeftChild;
			rightLeft = 0;
		}
		else { // p->data.key < x.key 인 경우
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
		forLink = p; // 지워야 하는 p
		p = p->RightChild;
		while (p->LeftChild) {
			p = p->LeftChild;
		}
		p->LeftChild = forLink->LeftChild; // 원래 p를 parent로 공유하는걸 하나로 연결
		childNodeForQ = forLink->RightChild; // 결국 이렇게 줘서 위에 q랑 연결하고자 하는거
	}
	else if (p->RightChild) { // RightChild만 있는거 // LeftSize 추가적으로 고려X
		childNodeForQ = p->RightChild;
	}
	else if(p->LeftChild) { // LeftChild만 있는거 // LeftSize 추가적으로 고려X 
		childNodeForQ = p->LeftChild;
	}
	else { // 둘다 없는거 // LeftSize 추가적으로 고려 X
		q->LeftChild = 0;
		q->RightChild = 0;
		delete p; // 이렇게만 해놓고 없애도 되는건가?
		return true;
	}
	
	// q랑 childNodeForQ 연결해주기
	// 현재 p가 q의 RightChild인지 LeftChild인지 모르므로 확인해서 연결해주기
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
	if (!root->RightChild) { // the tree does not have right sub-tree // 오른쪽이 없기때문에, root가 가장 큰거
		deletedNode = root; // 제일 큰거인 root를 삭제하고
		root = root->LeftChild; // 왼쪽 밑에꺼가 root 가 되는거
	}
	else {
		BstNode* parentNode = root, * currNode = root;
		while (currNode->RightChild) { // 제일 큰거를 찾기 때문에 계속 오른쪽으로 가면 됨
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
} // A는 왼쪽, B는 오른쪽으로 해서 합친거

BST* BST::TwoWayJoin(BST* A, BST* B) {
	if (!A)
		return B;
	if (!B)
		return A;
	// 없으면 하나만 출력 한다는거
	Element midEle;
	A->DeleteLargestElement(midEle); // root를 만들기 위해서 일단 지우는거

	// x= largest element of A or smallest element of B
	return ThreeWayJoin(A, &midEle, B);  // 여기서 위에서 지운것을 기준으로 좌우 맞추기
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