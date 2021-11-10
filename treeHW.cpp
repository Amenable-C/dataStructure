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
	char data;
	TreeNode* RightChild;

	TreeNode() {
		LeftChild = RightChild = 0;
	}

	TreeNode(char ch, TreeNode* Lefty, TreeNode* Righty) {
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

	bool Insert(char);
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
	friend class Tree;
public:
	char* Next();
	//void Next();
	InorderIterator(Tree& tree) : t(tree) {
		CurrentNode = t.root; // ó������ CurrentNode�� ����
	}
private:
	//char* Next(TreeNode*);
	Tree t;
	Stack<TreeNode*> s;
	TreeNode* CurrentNode;
};

//void InorderIterator::Next() {
//	Next(CurrentNode);
//}

// 6
char* InorderIterator::Next() {
	while (CurrentNode) {
		s.Add(CurrentNode);
		CurrentNode = CurrentNode->LeftChild;
	}
	if (!s.IsEmpty()) {
		CurrentNode = *s.Delete(CurrentNode);
		char& temp = CurrentNode->data;
		CurrentNode = CurrentNode->RightChild; // �׳� ��� inorder�� ���鼭, ���� �����ϴ°�
		return &temp; // �̰� �ٸ� �ʿ��� Next()�� �θ��� ���� ��
	}
	
	else 
		return 0;
	
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
	// VLR // data�� V�ΰ� ����
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
		temp->RightChild = copy(orignode->RightChild); // �Ѿ�鼭 �� ��帶�� data ����
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
	if ((!a) && (!b)) // �� �� ���� ���
		return 1; // �� �� ���°��� ���ٰ� ����??????
	if (a && b && (a->data == b->data) && equal(a->LeftChild, b->LeftChild) && equal(a->RightChild, b->RightChild))
		return 1; // a�� b�� �����ϰ� data, leftchild, rightchild �� �������
	return 0;
}

// Insert for Prefix /////////////////// ���� 1�� ///////////////////
bool Tree::Insert(char x) {
	Stack<TreeNode*> sForInsert;
	TreeNode* CurrentNode = root;
	TreeNode* q = 0;
	while (1) { 
		while (CurrentNode) {
			sForInsert.Add(CurrentNode);
			CurrentNode = CurrentNode->LeftChild;
		}
		if (!root){ // root�� ���� ���
			CurrentNode = new TreeNode;
			CurrentNode->LeftChild = CurrentNode->RightChild = 0;
			CurrentNode->data = x;
			root = CurrentNode;
			return true;
		}
		CurrentNode = *sForInsert.Delete(CurrentNode);
		q = CurrentNode;
		
		// �ش� ��尡 operator�̰�, leftchild�� ���� ���
		if (CurrentNode->data == '+' || CurrentNode->data == '-' || CurrentNode->data == '*') {
			CurrentNode = CurrentNode->LeftChild;
			CurrentNode = new TreeNode;
			CurrentNode->LeftChild = CurrentNode->RightChild = 0;
			CurrentNode->data = x;
			q->LeftChild = CurrentNode;
			return
				true;
		} 
		else  { // ���� ��尡 operand�� ���
			// �ѹ��� �ڷ� ������
			CurrentNode = *sForInsert.Delete(CurrentNode);
			q = CurrentNode; 
			
			if (!CurrentNode->RightChild) { // left���� operand�� �ְ�, right�� ����ִ� ���
				CurrentNode = CurrentNode->RightChild;
				CurrentNode = new TreeNode;
				CurrentNode->LeftChild = CurrentNode->RightChild = 0;
				CurrentNode->data = x;
				q->RightChild = CurrentNode;
				return
					true;
			}
			else { // right���� ������ �ִ� ���
				// �ٽ� Ȯ���ؾ� ��
				// rightchild���� �ٽ� �����ؼ�, while�� ������ ��.
				CurrentNode = CurrentNode->RightChild;
			}
		}
	}
}

// 4
void Tree::Nonreclnorder() {
	// inorder�ε� ����Լ��� �ƴ� Stack�� �̿��ϴ� ��
	Stack<TreeNode*> s;
	TreeNode* CurrentNode = root;
	while (1) {
		while (CurrentNode) {
			s.Add(CurrentNode);
			CurrentNode = CurrentNode->LeftChild;
			// LeftChild�� ������ stack�� ��� �����鼭 ���°�
		}
		if (!s.IsEmpty()) {
			CurrentNode = *s.Delete(CurrentNode);
			// ������ �� ���� CurrentNode�� �Ǿ��ٰ�, �ٽ� ���������� ���ư���
			cout << CurrentNode->data << endl;
			// ���(= L���)
			CurrentNode = CurrentNode->RightChild;
			// ���⼭ �ٽ� �����ٰ� if������ �ͼ� s.Delete�� �ϸ� V�� ���
			// �� ���� RightChild�� ���� R�� ���
			// �׸��� �ٽ� ���ο� L�� ��� // ��� �ݺ�~~~~~
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
	// �� �������� ���ʿ��� ���������� �� ���
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
	int max = 0;
	char x = 0;
	char* nextReturn = 0;
	/*t.Insert('*');
	t.Insert('a');*/
	InorderIterator k = t;
	while (select != 'q') {
		cout << endl;
		cout << "BinarySearchTree. Selet i : insert the prefix, d : Display(inorder), e : Nonreclnorder, f : preorder, g : postorder, h : copy and compare, n : inorder using next, q : Quit =>";
		cin >> select;
		switch (select) {
		case 'n': // Next()�� inorder����ϱ�. /////////////////// ���� 2�� ///////////////////
			k = t;
			cout << "inorder using next : ";
			nextReturn = k.Next();
			while (nextReturn != 0) {
				cout << *nextReturn;
				cout << " ";
				nextReturn = k.Next();
			}
			cout << endl;
			break;
		case 'i':
			cout << "The number of items = ";
			cin >> max;
			for (int i = 0; i < max; i++) {
				cout << "prefix value = ";
				cin >> x;
				if (!t.Insert(x))
					cout << "Insert Duplicated data" << endl;
			}
			cout << endl;
			break;
		case 'd':
			cout << "infix : ";
			t.inorder();
			cout << endl;
			break;
		case 'e':
			t.Nonreclnorder();
			break;
		case 'f':
			cout << "prefix : ";
			t.preorder();
			cout << endl;
			break;
		case 'g':
			cout << "postfix : ";
			t.postorder();
			cout << endl;
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