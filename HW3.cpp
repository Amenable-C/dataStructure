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
	
	for (char x = NextToken(e); x != NULL; x = NextToken(e)) { // �̷����ϸ� ������ next�� �ȴٴ°ǰ�?
		//cout << "x = " << x << endl;
		if (isOperand(x)) // operand�� �׳� ��� ���
			cout << x;
		else if (x == '(') { // ')' -> '(' �� �ٲ�
			while (stack.Top() != ')') { // Last != ( // '(' -> ')' �� �ٲ�
				cout << stack.Top(); // �ȿ� �ִ°Ŵ� �׳� ���???? // ���� ��ó�� �Ұ� ������? // �ٽ� Postfix�ؾ� �ϴ°� ������
				stack.Pop(); 
			}
			stack.Pop(); // ��ȣ�� ���� �ؾ���. �׷��� �׳� Pop���� ���� // ')'�� �����Ѱ�
		}
		else { // ��ȣ�� ������ operator�̶�� ��
			for (; isp(stack.Top()) >= icp(x); stack.Pop()) // ������°Ŷ� ���ؼ� priority�� ������ ��
				cout << stack.Top(); //������ Pop�� �Ǵ°ǰ�???
			stack.Push(x); // �� Push?? // ����????
		}
	}

	char x;
	while ((x = stack.Top()) != '#') { //LIFO �̶� �� �ٴڿ� �ִ� #���� �ɶ����� ���
		cout << x;
		stack.Pop();
	}
	cout << endl;
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

void main() {
	index = 0;
	Expression infix, postfix;
	scanf("%s", infix);
	cout << infix << endl;
	postfix = Postfix(infix); // ��ȯ�� �ϴ°�
	Eval(postfix); 
	cout << postfix << endl;
}