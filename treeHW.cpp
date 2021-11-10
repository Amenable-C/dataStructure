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
		CurrentNode = t.root; // 처음꺼를 CurrentNode로 세팅
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
		CurrentNode = CurrentNode->RightChild; // 그냥 계속 inorder는 돌면서, 값을 저장하는거
		return &temp; // 이게 다른 쪽에서 Next()를 부르면 리턴 값
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

// Insert for Prefix /////////////////// 과제 1번 ///////////////////
bool Tree::Insert(char x) {
	Stack<TreeNode*> sForInsert;
	TreeNode* CurrentNode = root;
	TreeNode* q = 0;
	while (1) { 
		while (CurrentNode) {
			sForInsert.Add(CurrentNode);
			CurrentNode = CurrentNode->LeftChild;
		}
		if (!root){ // root가 없을 경우
			CurrentNode = new TreeNode;
			CurrentNode->LeftChild = CurrentNode->RightChild = 0;
			CurrentNode->data = x;
			root = CurrentNode;
			return true;
		}
		CurrentNode = *sForInsert.Delete(CurrentNode);
		q = CurrentNode;
		
		// 해당 노드가 operator이고, leftchild가 없는 경우
		if (CurrentNode->data == '+' || CurrentNode->data == '-' || CurrentNode->data == '*') {
			CurrentNode = CurrentNode->LeftChild;
			CurrentNode = new TreeNode;
			CurrentNode->LeftChild = CurrentNode->RightChild = 0;
			CurrentNode->data = x;
			q->LeftChild = CurrentNode;
			return
				true;
		} 
		else  { // 현재 노드가 operand인 경우
			// 한번더 뒤로 가야함
			CurrentNode = *sForInsert.Delete(CurrentNode);
			q = CurrentNode; 
			
			if (!CurrentNode->RightChild) { // left에는 operand가 있고, right가 비어있는 경우
				CurrentNode = CurrentNode->RightChild;
				CurrentNode = new TreeNode;
				CurrentNode->LeftChild = CurrentNode->RightChild = 0;
				CurrentNode->data = x;
				q->RightChild = CurrentNode;
				return
					true;
			}
			else { // right에도 노드들이 있는 경우
				// 다시 확인해야 함
				// rightchild부터 다시 시작해서, while로 돌려야 함.
				CurrentNode = CurrentNode->RightChild;
			}
		}
	}
}

// 4
void Tree::Nonreclnorder() {
	// inorder인데 재귀함수가 아닌 Stack을 이용하는 거
	Stack<TreeNode*> s;
	TreeNode* CurrentNode = root;
	while (1) {
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
		case 'n': // Next()로 inorder출력하기. /////////////////// 과제 2번 ///////////////////
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