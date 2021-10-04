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
	
	for (char x = NextToken(e); x != NULL; x = NextToken(e)) { // 이렇게하면 저절로 next로 된다는건가?
		//cout << "x = " << x << endl;
		if (isOperand(x)) // operand면 그냥 계속 출력
			cout << x;
		else if (x == '(') { // ')' -> '(' 로 바꿈
			while (stack.Top() != ')') { // Last != ( // '(' -> ')' 로 바꿈
				cout << stack.Top(); // 안에 있는거는 그냥 출력???? // 여기 고처야 할거 같은데? // 다시 Postfix해야 하는거 같은데
				stack.Pop(); 
			}
			stack.Pop(); // 괄호는 제거 해야함. 그래서 그냥 Pop으로 제거 // ')'를 제거한거
		}
		else { // 괄호를 제외한 operator이라는 말
			for (; isp(stack.Top()) >= icp(x); stack.Pop()) // 따라오는거랑 비교해서 priority가 높은지 비교
				cout << stack.Top(); //저절로 Pop이 되는건가???
			stack.Push(x); // 왜 Push?? // 머지????
		}
	}

	char x;
	while ((x = stack.Top()) != '#') { //LIFO 이라서 맨 바닥에 있는 #까지 될때까지 출력
		cout << x;
		stack.Pop();
	}
	cout << endl;
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

void main() {
	index = 0;
	Expression infix, postfix;
	scanf("%s", infix);
	cout << infix << endl;
	postfix = Postfix(infix); // 전환을 하는거
	Eval(postfix); 
	cout << postfix << endl;
}