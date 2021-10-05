#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include "stackTemplate.h"
typedef char* Expression;
typedef char Token;
using namespace std;

int index = 0;

char NextToken(char* e) {
	char token = e[index];
	index++;
	return token;
}

bool isOperand(char x) {
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')' || x == '%' || x == '#')
		return false;
	else
		return true;
}

int isp(char a) { // �켱������ �������� ���� Ŀ��
	if (a == '(')
		return 0;
	else if (a == ')')
		return 19;
	else if (a == '+' || a == '-')
		return 12;
	else if (a == '*' || a == '%' || a == '/')
		return 13;
	else
		return 0;
}

int icp(char a) { // �켱������ �������� ���� Ŀ��
	if (a == '(') // ��ȣ�ȿ� ��ȣ��°ǰ�?
		return 20;
	else if (a == ')')
		return 19;
	else if (a == '+' || a == '-')
		return 12;
	else if (a == '*' || a == '%' || a == '/')
		return 13;
	else
		return 0;
}

Expression Postfix(Expression e) {
	Stack<char> stack;
	stack.Push('#');
	
	for (char x = NextToken(e); x != NULL; x = NextToken(e)) { // �̷����ϸ� ������ next�� �ȴٴ°ǰ�?
		//cout << "x = " << x << endl;
		if (isOperand(x)) // operand�� �׳� ��� ���
			cout << x;
		else if (x == ')') { // ����� �������Ƿ� ���⼭ operator �� ���
			while (stack.Top() != '(') { // ��ȣ�ȿ� ���ο� ��ȣ�� ����ϱ� ���� 
				cout << stack.Top(); 
				stack.Pop(); 
			}
			stack.Pop(); // '(' ����
		}
		else { // ��ȣ�� ������ operator�̶�� ��
			for (; isp(stack.Top()) >= icp(x); stack.Pop()) 
				cout << stack.Top(); // isp >= icp �̸� �׳� �ٷ� ���
			stack.Push(x); // icp�� ����
		}
	}

	char x;
	while ((x = stack.Top()) != '#') { // ����
		cout << x;
		stack.Pop();
	}
	cout << endl;
	return 0;
}

void Eval(Expression e) { // ��� ���� ����ϴ°� ����.
	Stack<Token> stack;
	stack.Push('#');
	for (Token x = NextToken(e); x != '#'; x = NextToken(e)) {
		if (isOperand(x))
			stack.Push(x);
		else {
			//remove the correct number of operands for operator x from stack;
			//perform the operation x and store the result onto the stack
			//�������� ������ operator�� ���
			//�� ���� temp�� �����ϰ� operator, ����, ������ pop
			//temp�� ����� ���� �ٽ� Push
		}
	}
}

int main() {
	index = 0;
	Expression infix, postfix;
	infix = (char*)malloc(sizeof(char) * 100);
	scanf("%s", infix);
	//cin >> infix;
	cout << "infix : " << infix << endl;
	cout << "postfix : ";
	postfix = Postfix(infix); // ��ȯ�� �ϴ°�
	Eval(postfix); 
	cout << postfix << endl;
	return 0;
}