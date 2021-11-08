#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "stackqueue.h"

using namespace std;
class Tree;
class TreeNode {
	friend class Tree;
	friend class InorderIterator;
	friend int equal(TreeNode*, TreeNode*);
private:
	TreeNode* LeftChild;
	int data;
	TreeNode* RightChild;

	TreeNode() {
		LeftChild = RightChild = 0;
	}

	TreeNode(int ch, TreeNode* Lefty, TreeNode* Righty) {
		data = ch;
		LeftChild = Lefty;
		RightChild = Righty;
	}
};

class Tree {
	friend int operator==(const Tree&, const Tree&);
	friend class InorderIterator;
private:
	TreeNode* root;
	void inorder(TreeNode*);
	void preorder(TreeNode*);
	void postorder(TreeNode*);
	TreeNode* copy(TreeNode*);
public:
	Tree(const Tree&);
	Tree() {
		root = 0;
	}

	bool Insert(int);
	void inorder();
	void preorder();
	void postorder();
	void NoStackInorder();
	void Nonreclnorder();
	void LevelOrder();
};

//Node* Tree::InorderSucc(Node* current) {
//
//}

// 5
class InorderIterator {
public:
	int* Next();
	InorderIterator(Tree tree) : t(tree) {
		CurrentNode = t.root; // 처음꺼를 CurrentNode로 세팅
	}
private:
	Tree t;
	Stack<TreeNode*> s;
	TreeNode* CurrentNode;
};

// 6
int* InorderIterator::Next() {
	while (CurrentNode) {
		s.Add(CurrentNode);
		CurrentNode = CurrentNode->LeftChild;
	}
	if (!s.IsEmpty()) {
		CurrentNode = *s.Delete(CurrentNode);
		int& temp = CurrentNode->data;
		CurrentNode = CurrentNode->RightChild; // 그냥 계속 inorder는 돌면서, 값을 저장하는거
		return &temp; // 이게 다른 쪽에서 Next()를 부르면 리턴 값
	}
	else return 0;
}

void Tree::inorder() {
	inorder(root);
}

void Tree::preorder() {
	preorder(root);
}

void Tree::postorder() {
	postorder(root);
}

// 1
void Tree::inorder(TreeNode* CurrentNode) {
	// LVR
	if (CurrentNode) {
		inorder(CurrentNode->LeftChild);
		cout << " " << CurrentNode->data;
		inorder(CurrentNode->RightChild);
	}
}

// 2
void Tree::preorder(TreeNode* CurrentNode) {
	// VLR // data가 V인거 같음
	if (CurrentNode) {
		cout << CurrentNode->data << " ";
		preorder(CurrentNode->LeftChild);
		preorder(CurrentNode->RightChild);
	}
}

// 3
void Tree::postorder(TreeNode* CurrentNode) {
	// LRV
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data << " ";
	}
}

Tree::Tree(const Tree& s) {
	root = copy(s.root);
}

// 9
TreeNode* Tree::copy(TreeNode* orignode) {
	if (orignode) {
		TreeNode* temp = new TreeNode;
		temp->data = orignode->data;
		temp->LeftChild = copy(orignode->LeftChild);
		temp->RightChild = copy(orignode->RightChild); // 넘어가면서 각 노드마다 data 복사
		return temp;
	}
	else
		return 0;
}

// Driver
int operator==(const Tree& s, const Tree& t) {
	return equal(s.root, t.root);
}

// Workhorse
int equal(TreeNode* a, TreeNode* b) {
	// This function returns 0 if the subtrees at a and b are not equivalent.
	// Otherwise, it will return 1
	if ((!a) && (!b)) // 둘 다 없을 경우
		return 1; // 둘 다 없는경우는 같다고 생각??????
	if (a && b && (a->data == b->data) && equal(a->LeftChild, b->LeftChild) && equal(a->RightChild, b->RightChild))
		return 1; // a와 b가 존재하고 data, leftchild, rightchild 다 같은경우
	return 0;
}

// 확인하기
bool Tree::Insert(int x) {
	TreeNode* p = root;
	TreeNode* q = 0;
	while (p) {
		q = p;
		if (x == p->data)
			return false;
		if (x < p->data)
			p = p->LeftChild;
		else p = p->RightChild;
	}
	p = new TreeNode;
	p->LeftChild = p->RightChild = 0;
	p->data = x;
	if (!root)
		root = p;
	else if (x < q->data)
		q->LeftChild = p;
	else
		q->RightChild = p;
	return true;
}

// 4
void Tree::Nonreclnorder() {
	// inorder인데 재귀함수가 아닌 Stack을 이용하는 거
	Stack<TreeNode*> s;
	TreeNode* CurrentNode = root;
	while(1){
		while (CurrentNode) {
			s.Add(CurrentNode);
			CurrentNode = CurrentNode->LeftChild;
			// LeftChild가 있으면 stack에 계속 쌓으면서 가는거
		}
		if (!s.IsEmpty()) {
			CurrentNode = *s.Delete(CurrentNode);
			// 위에서 빈 것이 CurrentNode가 되었다가, 다시 마지막껄로 돌아가기
			cout << CurrentNode->data << endl;
			// 출력(= L출력)
			CurrentNode = CurrentNode->RightChild;
			// 여기서 다시 나갔다가 if문으로 와서 s.Delete를 하면 V가 출력
			// 그 다음 RightChild로 가서 R이 출력
			// 그리고 다시 새로운 L이 출력 // 계속 반복~~~~~
		}
		else break;
	}
}

// 7
void Tree::LevelOrder() {
	Queue<TreeNode*> q;
	TreeNode* CurrentNode = root;
	while (CurrentNode) {
		cout << CurrentNode->data << endl;
		if (CurrentNode->LeftChild)
			q.Add(CurrentNode->LeftChild);
		if (CurrentNode->RightChild)
			q.Add(CurrentNode->RightChild);
		CurrentNode = *q.Delete(CurrentNode);
	}
	// 각 레벨별로 왼쪽에서 오른쪽으로 쭉 출력
}

// 8
void Tree::NoStackInorder() {
	if (!root)
		return;
	TreeNode* top = 0, * LastRight = 0, * p, * q, * r, * r1;
	p = q = root;
	while (1) {
		while (1) {
			if ((!p->LeftChild) && (!p->RightChild)) {
				cout << p->data;
				break;
			}
			if (!p->LeftChild) {
				cout << p->data;
				r = p->RightChild;
				p->RightChild = q;
				q = p;
				p = r;
			}
			else {
				r = p->LeftChild;
				p->LeftChild = q;
				q = p;
				p = r;
			}
		}
		TreeNode* av = p;
		while (1) {
			if (p == root)
				return;
			if (!q->LeftChild) {
				r = q->RightChild;
				q->RightChild = p;
				p = q;
				q = r;
			}
			else if (!q->RightChild) {
				r = q->LeftChild;
				q->LeftChild = p;
				p = q;
				q = r;
				cout << p->data;
			}
			else
				if (q == LastRight) {
					r = top;
					LastRight = r->LeftChild;
					top = r->RightChild;
					r->LeftChild = r->RightChild = 0;
					r = q->RightChild;
					q->RightChild = p;
					p = q;
					q = r;
				}
				else {
					cout << q->data;
					av->LeftChild = LastRight;
					av->RightChild = top;
					top = av;
					LastRight = q;
					r = q->LeftChild;
					q->LeftChild = p;
					r1 = q->RightChild;
					q->RightChild = r;
					p = r1;
					break;
				}
		}
	}
}

int main() {
	Tree t;
	int eq = -1;
	char select = 'i';
	int max = 0, x = 0;
	while (select != 'q') {
		cout << "BinarySearchTree. Selet i : insert, d : Display, e : Nonreclnorder, f : preorder, g : postorder, h : copy and compare, q : Quit =>";
		cin >> select;
		switch (select) {
		case 'i':
			cout << "The number of items = ";
			cin >> max;
			for (int i = 0; i < max; i++) {
				cout << "value = ";
				cin >> x;
				if (!t.Insert(x))
					cout << "Insert Duplicated data" << endl;
			}
		case 'd':
			t.inorder();
			cout << endl;
			break;
		case 'e':
			t.Nonreclnorder();
			break;
		case 'f':
			t.preorder();
			break;
		case 'g':
			t.postorder();
			break;
		case 'h':
			eq = (t == Tree(t));
			if (eq) {
				cout << "compare result : true" << endl;
			}
			else
				cout << "compare result : false" << endl;
			break;
		case 'q':
			cout << "Quit" << endl;
			break;
		default:
			cout << "WRONG INPUT " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}