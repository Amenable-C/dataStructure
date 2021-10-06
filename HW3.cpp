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
	// 마지막에 오류가 발생하는거 같은데 체크해보기
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
	cout << "Expression e 길이 다시 : " << strlen(e) << endl;
	cout << "infix 다시 체크1 : " << e << endl;
	Stack<char> stack;
	
	Expression postfixExpression = (char*)malloc(sizeof(char) * (strlen(e)));
	//Expression temp = new char;
	postfixExpression[strlen(e)] = { 0 };
	cout << "1. check temp return : " << postfixExpression << endl;
	//Expression postfixExpression;
	//cout 하는거를 넣어준다고 생각 // postfixExpression[i++] = 
	int i = 0;
	stack.Push('#');
	
	
	for (char x = NextToken(e); x != NULL; x = NextToken(e)) { // 이렇게하면 저절로 next로 된다는건가?
		//cout << "x = " << x << endl;
		if (isOperand(x)) { // operand면 그냥 계속 출력
			cout << x;
			postfixExpression[i] = x;
			i++;
		}
		else if (x == ')') { // 계산이 끝났으므로 여기서 operator 다 출력
			while (stack.Top() != '(') { // 괄호안에 새로운 괄호를 계산하기 전에 
				cout << stack.Top();
				postfixExpression[i] = stack.Top();
				i++;
				stack.Pop(); 
			}
			stack.Pop(); // '(' 제거
		}
		else { // 괄호를 제외한 operator이라는 말
			for (; isp(stack.Top()) >= icp(x); stack.Pop()) {
				cout << stack.Top(); // isp >= icp 이면 그냥 바로 출력
				postfixExpression[i] = stack.Top();
				i++;
			}
			stack.Push(x); // icp를 저장
		}
	}
	cout << "2. check temp return : " << postfixExpression << endl;
	char x;
	while ((x = stack.Top()) != '#') { // 남은
		cout << x;
		postfixExpression[i] = x;
		i++;
		stack.Pop();
	}
	
	cout << endl;
	cout << "check temp return : " << postfixExpression << endl;
	return postfixExpression;
	
	//return 0;
	//return 추가 // cout 할때마다 Expression 만들면 될거 같음.
}

void Eval(Expression e) { // 계산 값 출력
	cout << "Eval에 있는 postfix : " << e << endl;
	cout << e[0] << " " << e[1] << " " << e[2] << " " << e[3] << " " << e[4] << endl;
	Stack<Token> stack;
	//Stack<char> stack;
	stack.Push('#');
	int operand1, operand2, result;
	index = 0;
	//for (Token x = NextToken(e); x != '#'; x = NextToken(e)) {
	for (Token x = NextToken(e); x != NULL; x = NextToken(e)) {
		//cout << "x : " << x << endl;
		if (isOperand(x)){
			//cout << "if_point" << endl;
			stack.Push(x);
			
		}
		else { // operator 라는 말
			//remove the correct number of operands for operator x from stack;
			//perform the operation x and store the result onto the stack
			//전전꺼랑 전꺼랑 operator로 계산
			//그 값을 temp에 저장하고 operator, 전꺼, 전전꺼 pop
			//temp에 저장된 값을 다시 Push
			//cout << "else_point" << endl;
			
			operand2 = (int)(stack.Top())-48;
			cout << "operand2 : " << operand2 << endl;
			stack.Pop();

			operand1 = int(stack.Top())-48;
			cout << "operand1 : " << operand1 << endl;
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
			cout << "result : " << result << endl;
			if (stack.Top() == '#') {
				cout << result;
				return;
			}
			stack.Push(result+48);
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
	cout << "Check postfix again : " << postfix << endl;
	//Eval(postfix); 
	cout << "Eval : ";
	Eval(postfix);
	//cout << postfix << endl;
	return 0;
}