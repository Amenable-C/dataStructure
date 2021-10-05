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

int isp(char a) { // 우선순위가 높을수록 값이 커짐
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

int icp(char a) { // 우선순위가 높을수록 값이 커짐
	if (a == '(') // 괄호안에 괄호라는건가?
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
	
	for (char x = NextToken(e); x != NULL; x = NextToken(e)) { // 이렇게하면 저절로 next로 된다는건가?
		//cout << "x = " << x << endl;
		if (isOperand(x)) // operand면 그냥 계속 출력
			cout << x;
		else if (x == ')') { // 계산이 끝났으므로 여기서 operator 다 출력
			while (stack.Top() != '(') { // 괄호안에 새로운 괄호를 계산하기 전에 
				cout << stack.Top(); 
				stack.Pop(); 
			}
			stack.Pop(); // '(' 제거
		}
		else { // 괄호를 제외한 operator이라는 말
			for (; isp(stack.Top()) >= icp(x); stack.Pop()) 
				cout << stack.Top(); // isp >= icp 이면 그냥 바로 출력
			stack.Push(x); // icp를 저장
		}
	}

	char x;
	while ((x = stack.Top()) != '#') { // 남은
		cout << x;
		stack.Pop();
	}
	cout << endl;
	return 0;
}

void Eval(Expression e) { // 계산 값을 출력하는거 같음.
	Stack<Token> stack;
	stack.Push('#');
	for (Token x = NextToken(e); x != '#'; x = NextToken(e)) {
		if (isOperand(x))
			stack.Push(x);
		else {
			//remove the correct number of operands for operator x from stack;
			//perform the operation x and store the result onto the stack
			//전전꺼랑 전꺼랑 operator로 계산
			//그 값을 temp에 저장하고 operator, 전꺼, 전전꺼 pop
			//temp에 저장된 값을 다시 Push
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
	postfix = Postfix(infix); // 전환을 하는거
	Eval(postfix); 
	cout << postfix << endl;
	return 0;
}