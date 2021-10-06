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
	Expression postfixExpression = (char*)malloc(sizeof(char) * (strlen(e)));

	int count = 0;
	for (char x = NextToken(e); x != NULL; x = NextToken(e)) {
		if (x == '(' || x == ')')
			count++;
	}
	
	postfixExpression[strlen(e)-count] = { 0 };
	int i = 0;
	stack.Push('#');
	
	index = 0;
	for (char x = NextToken(e); x != NULL; x = NextToken(e)) {
		if (isOperand(x)) { 
			//cout << x;
			postfixExpression[i] = x;
			i++;
		}
		else if (x == ')') { 
			while (stack.Top() != '(') { 
				//cout << stack.Top();
				postfixExpression[i] = stack.Top();
				i++;
				stack.Pop();
			}
			stack.Pop(); 
		}

		else { 
			for (; isp(stack.Top()) >= icp(x); stack.Pop()) {
				//cout << stack.Top(); 
				postfixExpression[i] = stack.Top();
				i++;
			}
			stack.Push(x); 
		}
	}
	char x;
	while ((x = stack.Top()) != '#') { 
		//cout << x;
		postfixExpression[i] = x;
		i++;
		stack.Pop();
	}
	return postfixExpression;
}

void Eval(Expression e) {
	cout << "postfix in Eval : " << e << endl;
	//Stack<Token> stack;
	Stack<int> stack;
	stack.Push('#');
	int operand1, operand2, result, num;
	index = 0;
	for (Token x = NextToken(e); x != NULL; x = NextToken(e)) {
		if (isOperand(x)){
			num = (int)(x)-'0';
			stack.Push(num);
		}
		else { 
			//remove the correct number of operands for operator x from stack;
			//perform the operation x and store the result onto the stack
			
			//operand2 = (int)(stack.Top())-48;
			operand2 = stack.Top();
			stack.Pop();


			operand1 = stack.Top();
			stack.Pop();
			
			if (x == '+')
				result = operand1 + operand2;
			else if (x == '-')
				result = operand1 - operand2;
			else if (x == '*')
				result = operand1 * operand2;
			else if (x == '%')
				result = operand1 % operand2;
			else { // x == '/'
				if (operand2 != 0){
				result = operand1 / operand2;
				}
			}
			stack.Push(result);
		}
	}
	cout << stack.Top() << endl;
}

int main() {
	index = 0;
	Expression infix, postfix;
	infix = (char*)malloc(sizeof(char) * 100);
	scanf("%s", infix);
	cout << "infix : " << infix << endl;

	postfix = Postfix(infix);
	cout << "postfix : " << postfix << endl;;


	cout << "Eval : ";
	Eval(postfix);
	cout << endl;

	return 0;
}