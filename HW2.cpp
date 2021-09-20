#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

using namespace std;
class Polynomial;

class Term
{
	friend Polynomial; // friend�� �����ϸ�, ����� Ŭ������ private�� protected�� ���ٰ���
	// ������ �����ε�
	friend istream& operator << (istream&, Polynomial&);
	friend ostream& operator >> (ostream&, Polynomial&);
private:
	float coef; // ���
	int exp; // ����
};

class Polynomial {
public:
	// ������ �����ε�
	friend istream& operator << (istream&, Polynomial&);
	friend ostream& operator >> (ostream&, Polynomial&);

	Polynomial();
	// construct the polynomial p(x) = 0;
	Polynomial Add(Polynomial b);
	// Sub ����
	Polynomial Sub(Polynomial b);
	// return the sum of the polynomials *this and b
	Polynomial Mult(Polynomial b);
	// return the product of the polynomials *this and b
	float Eval(float f);
	// evaluate the polynomial *this at f and return the result
	void NewTerm(const float theCoeft, const int theExp);
	int Display();
	int GetData();
private:
	static Term* termArray; // ���Ⱑ �����Ͷ� coef�� exp�� ���� ����
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};
// ����Ʈ ������ �����ε�
istream& operator >> (istream& in, Polynomial& p) {
	int newTerms;
	float coef;
	int exp;
	in >> newTerms;
	for (int i = 0; i < newTerms; i++) {
		in >> coef >> exp;
		p.NewTerm(coef, exp);
	}
	return in;
}
//ostream& operator << (ostream& out, Polynomial& p) { // const Polynomial& p �̰Ÿ� �ٲپ��µ� ��������???
//	for (int i = 0; i < p.terms; i++) {
//		if (p.termArray[i].coef && p.termArray[i].coef != 1 && p.termArray[i].coef != -1)
//			out << p.termArray[i].coef;
//
//	}
//}



Polynomial::Polynomial() {
	start = -1;
	finish = -1;
	terms = 0;
}
int Polynomial::Display() {
	int aPos = start;
	for (; aPos <= finish; aPos++) {
		cout << termArray[aPos].coef << "x^" << termArray[aPos].exp;
		if ((aPos - finish) != 0) // aPos < finish ��� ��
			cout << " + ";
	}
	cout << "\n";
	return 0;
}
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity) { // �뷮 �ø��� (capacity 2���ϱ�)
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + free, temp); // ��������, ���� ��, ������ ��ġ
		delete[] termArray;
		termArray = temp;
	}
	termArray[free].coef = theCoeff; // ���ĭ�� �ְ�
	termArray[free++].exp = theExp; // ����ĭ�� �ְ� // �������� ++�ؼ� ���߿� �����°͵� �ٷ� ���� �� �ֵ��� �ϴ°�
}
int Polynomial::GetData() {
	int i, degree;
	float coef;
	int expo;
	cout << "Enter Degree Of Polynomial:";
	cin >> degree; // ��� ���� ����
	start = free;
	for (i = degree; i > 0; i--) {
		cout << "Enter coefficient of x^" << i << ":";
		cin >> coef;
		cout << "Enter exponent of x^" << i << ":";
		cin >> expo;
		NewTerm(coef, expo);
	}
	finish = free - 1; // free�� static�̶� ���⼭ ��� ���� // NewTerm�� �ϸ� �������� free�� +1�ϱ� ������ ���� �������� -1�ؾ���.
	terms = finish - start + 1; // ����
	return 0;
}
Polynomial Polynomial::Add(Polynomial b) {
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free; // a�� �������� ���ϴ°��̹Ƿ� free�� ���°�
	while ((aPos <= finish) && (bPos <= b.finish)) { // �ΰ� �߿� ��� �ϳ��� ������ �� // �ٵ� �� <=?
		if ((termArray[aPos].exp == b.termArray[bPos].exp)) { // ������ ������ ����� ���Ѵٴ°�
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) // ����� 0�� �ƴϸ� Ȯ���ؼ� c�� �ֱ�
				c.NewTerm(t, termArray[aPos].exp);
			aPos++;
			bPos++; // ������ �غ�
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp)) { // ������ �ٸ��� ū�� ���� �ֱ�
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++; // �̷��� ���� ���� �Ѿ�°�
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	// �����͵� ó���ϴ°�
	for (; aPos <= finish; aPos++) // aPos <= finish �̷��� �ؾ� �ϴ°� �ƴѰ�?
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos <= b.finish; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	c.finish = free - 1; 
	return c;
}
// Sub ����
Polynomial Polynomial::Sub(Polynomial b) {
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free; // a�� �������� ���ϴ°��̹Ƿ� free�� ���°�
	while ((aPos <= finish) && (bPos <= b.finish)) { // �ΰ� �߿� ��� �ϳ��� ������ �� // �ٵ� �� <=?
		if ((termArray[aPos].exp == b.termArray[bPos].exp)) { // ������ ������ ����� ���Ѵٴ°�
			float t = termArray[aPos].coef - b.termArray[bPos].coef; // ���ֱ�
			if (t) // ����� 0�� �ƴϸ� Ȯ���ؼ� c�� �ֱ�
				c.NewTerm(t, termArray[aPos].exp);
			aPos++;
			bPos++; // ������ �غ�
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp)) { // ������ �ٸ��� ū�� ���� �ֱ�
			c.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp); // -�� �ٲٰ� �����ֱ�
			bPos++; // �̷��� ���� ���� �Ѿ�°�
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	// �����͵� ó���ϴ°�
	for (; aPos <= finish; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos <= b.finish; bPos++)
		c.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp); // - ���ְ� ���ֱ�
	c.finish = free - 1; 
	return c;
}

// Mul ����(���� ���)
Polynomial Polynomial::Mult(Polynomial b) {
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free; 

	for (; aPos < finish; aPos++) {
		Polynomial m;
		float newCoef;
		int newExp;
		if (c.terms) { // c�� ������
			// m.start = c.start + c.terms; // �̰�?
			m.start = c.free;
		}
		else { // c�� ������
			// m.start = c.start + c.terms + 1; // �̰�?
			m.start = c.free;
		}

		for (int bPos = b.start; bPos <= b.finish; bPos++) {
			newCoef = termArray[aPos].coef * termArray[bPos].coef;
			newExp = termArray[aPos].exp + termArray[bPos].exp;
			m.NewTerm(newCoef, newExp);
			/*m.finish = free - 1;*/
			c.Add(m); // �̰� ������ �ȵǳ�?????
		}
		// n = n.Add(m); // n�� ����ؼ� �������� ���� �׾��ֱ�
		//c.finish = m.start - 1;
		//c.terms = n.terms;
		//c.start = m.finish; // �̰� �³�?
	}
	// �̷��Ը� �ص� ���� ������?
	return c;
}
//Eval() ����
float Polynomial::Eval(float f) {
	float result = 0;
	for (int i = 0; i < terms; i++) {
		float temp = 1;
		for (int j = 0; j < termArray[i].exp; j++) {
			temp = temp * termArray[i].coef;
		}
		result = result + temp;
	}
	return result;
}

int Polynomial::capacity = 100;
Term* Polynomial::termArray = new Term[100];
int Polynomial::free = 0;
int main(void) {
	int choice;
	Polynomial P1, P2, P3, P4;
	cout << "Instruction:- \nExample:-\nP(x)=5x^3+3x^1\nEnter the Polynomial like\nP(x) = 5x^3 + 0x^2 + 3x^1 + 0x^0\n";
	cout << "Enter Polynomial1:-" << endl;
	// P1.GetData();
	cin >> P1;
	cout << "Enter Polynomial2:-" << endl;
	// P2.GetData();
	cin >> P2;
	cout << "Enter Polynomial3:-" << endl;
	cin >> P3;
	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Substraction\n3: Multiplication\n0: Exit" << endl;
		cout << "Enter your choice:";
		cin >> choice;
		switch (choice) {
		case1:
			cout << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1:";
			P1.Display();
			//cout << P1;
			cout << "Polynomial2:";
			P2.Display();
			//cout << P2;
			//cout << P3;
			P3 = P1.Add(P2);
			cout << "Add:";
			P3.Display();
			//P4 = P1 + P2 + P3;  // Ǯ��
			//P3.Display();
			//cout << P4;
			cout << "---------------------------------------- \n";
			break;
		case 2:
			cout << "\n------------- Substraction -------------\n";
			cout << "Polynomial1:";
			P1.Display();
			//cout << P1;
			cout << "Polynomial2:";
			P2.Display();
			//cout << P2;
			P3 = P1.Sub(P2); //�л� ���� �ǽ� ���
			cout << "Sub:";
			P3.Display();
			//P4 = P1 - P2; // Ǯ��
			//cout << P4;
			cout << "---------------------------------------- \n";
			break;
		case 3:
			cout << "\n----------- Multiplication -------------\n";
			cout << "Polynomial1:";
			P1.Display();
			//cout << P1;
			cout << "Polynomial2:";
			P2.Display();
			//cout << P2;
			P3 = P1.Mult(P2);
			//P3 = P1 * P2; Ǯ��
			cout << "Mul:";
			P3.Display();
			// cout << P3; �̰� ���� �ϴ°� ������??
			cout << "---------------------------------------- \n";
			break;
		case 4: //P2.Eval(5); �л� ���� �ǽ� ���
			cout << "P2.Eval(3)";
			//cout << P4;
			cout << P2.Eval(3);
			break;
		case 0:
			cout << "Good Bye...!!!" << endl;
			exit(0);
		}
	}
	system("pause");
	return 0;
}