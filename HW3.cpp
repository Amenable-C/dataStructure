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
	// �������� ������ �߻��ϴ°� ������ üũ�غ���
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
	cout << "Expression e ���� �ٽ� : " << strlen(e) << endl;
	cout << "infix �ٽ� üũ1 : " << e << endl;
	Stack<char> stack;
	
	Expression postfixExpression = (char*)malloc(sizeof(char) * (strlen(e)));
	//Expression temp = new char;
	postfixExpression[strlen(e)] = { 0 };
	cout << "1. check temp return : " << postfixExpression << endl;
	//Expression postfixExpression;
	//cout �ϴ°Ÿ� �־��شٰ� ���� // postfixExpression[i++] = 
	int i = 0;
	stack.Push('#');
	
	
	for (char x = NextToken(e); x != NULL; x = NextToken(e)) { // �̷����ϸ� ������ next�� �ȴٴ°ǰ�?
		//cout << "x = " << x << endl;
		if (isOperand(x)) { // operand�� �׳� ��� ���
			cout << x;
			postfixExpression[i] = x;
			i++;
		}
		else if (x == ')') { // ����� �������Ƿ� ���⼭ operator �� ���
			while (stack.Top() != '(') { // ��ȣ�ȿ� ���ο� ��ȣ�� ����ϱ� ���� 
				cout << stack.Top();
				postfixExpression[i] = stack.Top();
				i++;
				stack.Pop(); 
			}
			stack.Pop(); // '(' ����
		}
		else { // ��ȣ�� ������ operator�̶�� ��
			for (; isp(stack.Top()) >= icp(x); stack.Pop()) {
				cout << stack.Top(); // isp >= icp �̸� �׳� �ٷ� ���
				postfixExpression[i] = stack.Top();
				i++;
			}
			stack.Push(x); // icp�� ����
		}
	}
	cout << "2. check temp return : " << postfixExpression << endl;
	char x;
	while ((x = stack.Top()) != '#') { // ����
		cout << x;
		postfixExpression[i] = x;
		i++;
		stack.Pop();
	}
	
	cout << endl;
	cout << "check temp return : " << postfixExpression << endl;
	return postfixExpression;
	
	//return 0;
	//return �߰� // cout �Ҷ����� Expression ����� �ɰ� ����.
}

void Eval(Expression e) { // ��� �� ���
	cout << "Eval�� �ִ� postfix : " << e << endl;
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
		else { // operator ��� ��
			//remove the correct number of operands for operator x from stack;
			//perform the operation x and store the result onto the stack
			//�������� ������ operator�� ���
			//�� ���� temp�� �����ϰ� operator, ����, ������ pop
			//temp�� ����� ���� �ٽ� Push
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
	postfix = Postfix(infix); // ��ȯ�� �ϴ°�
	cout << "Check postfix again : " << postfix << endl;
	//Eval(postfix); 
	cout << "Eval : ";
	Eval(postfix);
	//cout << postfix << endl;
	return 0;
}