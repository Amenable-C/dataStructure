#include <iostream>
using namespace std;
#define N 10

class Employee {
	int enumber;
	string ename;
	float salary;
	string dept;
	static int count; // ��ü�� ������ ������ count++
public:
	Employee();
	Employee(int);
	Employee(const Employee&);
	~Employee();
	Employee& operator = (const Employee&);
	int operator++();
	static int Show(); // count ���� �ʱ�ȭ
	friend ostream& operator << (ostream& stream, Employee&);
};

Employee::Employee() {

}
Employee::Employee(int n) {

}
class EmpTable { // ��ü �迭 ó���ϴ� Ŭ����
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

