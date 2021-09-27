#include <iostream>
using namespace std;
#define N 10

class Employee {
	int enumber;
	string ename;
	float salary;
	string dept;
	static int count; // 객체가 생성될 때마다 count++
public:
	Employee();
	Employee(int);
	Employee(const Employee&);
	~Employee();
	Employee& operator = (const Employee&);
	int operator++();
	static int Show(); // count 값을 초기화
	friend ostream& operator << (ostream& stream, Employee&);
};

Employee::Employee() {

}
Employee::Employee(int n) {

}
class EmpTable { // 객체 배열 처리하는 클래스
	int top;
	Employee data[N];
public:
	void initializeEmployee();
	void ShowEmployee();
};
void EmpTable::initializeEmployee()
{
	int n = top;
	for (int i = 0; i < n; i++)
	{
		//cin >> enumber >> ...
		//data[i] = new Employee(...);
	}
}
void EmpTable::ShowEmployee() {

}

void initializeEmployee(Employee* emp[], int); 
void ShowEmployee(Employee* emp[], int);

void main() {
	int num = N;
	EmpTable empt;
	empt.initializeEmployee();
	empt.ShowEmployee();
	system("pause");
}

