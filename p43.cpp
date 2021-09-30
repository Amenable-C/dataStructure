#include <iostream>
#include <memory>
//#include "stackTemplate.h"
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

int isp(char a) {
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

int icp(char a) {
	if (a == '(')
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
	for (char x = NextToken(e); x != NULL; x = NextToken(e)) {
		//cout << "x = " << x << endl;
		if (isOperand(x))
			cout << x;
		else if (x == ')') {
			while(stack.Top() != '(') {
				cout << stack.Top();
				stack.Pop();
			}
			stack.Pop();
		}
		else {
			for (; isp(stack.Top()) >= icp(x); stack.Pop())
				cout << stack.Top();
			stack.Push(x);
		}
	}
	char x;
	while ((x = stack.Top()) != '#') {
		cout << x;
		stack.Pop();
	}
	cout << endl;
}

void Eval(Expression e) {
	Stack<Token> stack;
	stack.Push('#');
	for (Token x = NextToken(e); x != '#'; x = NextToken(e))
		if (isOperand(x))
			stack.Push(x);
		else {
			//remove the correct number of operands for operator x from stack;
			//perform the operation x and store the result onto the stack;
		}
}
void main() {
	index = 0;
	Expression infix, postfix;
	scanf("%s", infix);
	cout << infix << endl;
	postfix = Postfix(infix);
	Eval(postfix);
	cout << postfix << endl;
}