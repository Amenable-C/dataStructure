#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

using namespace std;
class Polynomial;

class Term
{
	friend Polynomial; // friend로 설정하면, 선언된 클래스의 private와 protected에 접근가능
	// 연산자 오버로딩
	friend istream& operator << (istream&, Polynomial&);
	friend ostream& operator >> (ostream&, Polynomial&);
private:
	float coef; // 계수
	int exp; // 지수
};

class Polynomial {
public:
	// 연산자 오버로딩
	friend istream& operator << (istream&, Polynomial&);
	friend ostream& operator >> (ostream&, Polynomial&);

	Polynomial();
	// construct the polynomial p(x) = 0;
	Polynomial Add(Polynomial b);
	// Sub 구현
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
	static Term* termArray; // 여기가 포인터라서 coef랑 exp을 따로 저장
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};
// 쉬프트 연산자 오버로딩
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
//ostream& operator << (ostream& out, Polynomial& p) { // const Polynomial& p 이거를 바꾸었는데 괜찮은가???
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
		if ((aPos - finish) != 0) // aPos < finish 라는 말
			cout << " + ";
	}
	cout << "\n";
	return 0;
}
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity) { // 용량 늘리기 (capacity 2배하기)
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + free, temp); // 원본시작, 원본 끝, 복사할 위치
		delete[] termArray;
		termArray = temp;
	}
	termArray[free].coef = theCoeff; // 계수칸에 넣고
	termArray[free++].exp = theExp; // 지수칸에 넣고 // 마지막에 ++해서 나중에 들어오는것도 바로 들어올 수 있도록 하는거
}
int Polynomial::GetData() {
	int i, degree;
	float coef;
	int expo;
	cout << "Enter Degree Of Polynomial:";
	cin >> degree; // 몇개를 넣을 건지
	start = free;
	for (i = degree; i > 0; i--) {
		cout << "Enter coefficient of x^" << i << ":";
		cin >> coef;
		cout << "Enter exponent of x^" << i << ":";
		cin >> expo;
		NewTerm(coef, expo);
	}
	finish = free - 1; // free가 static이라서 여기서 사용 가능 // NewTerm을 하면 마지막에 free를 +1하기 때문에 최종 마지막은 -1해야함.
	terms = finish - start + 1; // 길이
	return 0;
}
Polynomial Polynomial::Add(Polynomial b) {
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free; // a를 기준으로 더하는것이므로 free를 적는거
	while ((aPos <= finish) && (bPos <= b.finish)) { // 두개 중에 어느 하나라도 끝나면 끝 // 근데 왜 <=?
		if ((termArray[aPos].exp == b.termArray[bPos].exp)) { // 지수가 같으면 상수만 더한다는거
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) // 상수가 0이 아니면 확정해서 c에 넣기
				c.NewTerm(t, termArray[aPos].exp);
			aPos++;
			bPos++; // 다음꺼 준비
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp)) { // 지수가 다르면 큰거 먼저 넣기
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++; // 이렇게 더한 것은 넘어가는거
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	// 남은것들 처리하는거
	for (; aPos <= finish; aPos++) // aPos <= finish 이렇게 해야 하는거 아닌가?
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos <= b.finish; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	c.finish = free - 1; 
	return c;
}
// Sub 구현
Polynomial Polynomial::Sub(Polynomial b) {
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free; // a를 기준으로 더하는것이므로 free를 적는거
	while ((aPos <= finish) && (bPos <= b.finish)) { // 두개 중에 어느 하나라도 끝나면 끝 // 근데 왜 <=?
		if ((termArray[aPos].exp == b.termArray[bPos].exp)) { // 지수가 같으면 상수만 더한다는거
			float t = termArray[aPos].coef - b.termArray[bPos].coef; // 빼주기
			if (t) // 상수가 0이 아니면 확정해서 c에 넣기
				c.NewTerm(t, termArray[aPos].exp);
			aPos++;
			bPos++; // 다음꺼 준비
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp)) { // 지수가 다르면 큰거 먼저 넣기
			c.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp); // -로 바꾸고 더해주기
			bPos++; // 이렇게 더한 것은 넘어가는거
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	// 남은것들 처리하는거
	for (; aPos <= finish; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos <= b.finish; bPos++)
		c.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp); // - 해주고 빼주기
	c.finish = free - 1; 
	return c;
}

// Mul 구현(수정 요망)
Polynomial Polynomial::Mult(Polynomial b) {
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free; 

	for (; aPos < finish; aPos++) {
		Polynomial m;
		float newCoef;
		int newExp;
		if (c.terms) { // c가 없으면
			// m.start = c.start + c.terms; // 이거?
			m.start = c.free;
		}
		else { // c가 있으면
			// m.start = c.start + c.terms + 1; // 이거?
			m.start = c.free;
		}

		for (int bPos = b.start; bPos <= b.finish; bPos++) {
			newCoef = termArray[aPos].coef * termArray[bPos].coef;
			newExp = termArray[aPos].exp + termArray[bPos].exp;
			m.NewTerm(newCoef, newExp);
			/*m.finish = free - 1;*/
			c.Add(m); // 이거 넣으면 안되나?????
		}
		// n = n.Add(m); // n에 계속해서 차곡차곡 값들 쌓아주기
		//c.finish = m.start - 1;
		//c.terms = n.terms;
		//c.start = m.finish; // 이게 맞나?
	}
	// 이렇게만 해도 되지 않을까?
	return c;
}
//Eval() 구현
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
			//P4 = P1 + P2 + P3;  // 풀기
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
			P3 = P1.Sub(P2); //학생 구현 실습 대상
			cout << "Sub:";
			P3.Display();
			//P4 = P1 - P2; // 풀기
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
			//P3 = P1 * P2; 풀기
			cout << "Mul:";
			P3.Display();
			// cout << P3; 이거 들어가야 하는거 같은데??
			cout << "---------------------------------------- \n";
			break;
		case 4: //P2.Eval(5); 학생 구현 실습 대상
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