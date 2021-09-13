// Do not use 2-D array, such as int a[2][3];
#include <iostream>
#include <stdlib.h>
using namespace std;

//implement the functions : add, sub, mult, transpose
class Matrix {
public:
	Matrix(int row, int col);
	int GetData();
	Matrix Transpose();
	int Display();
	Matrix Multiply(Matrix b);
	Matrix Add(Matrix b);
	Matrix Sub(Matrix b);
	Matrix Multiply2(Matrix b);
	int CompareRowCol(Matrix b);
private:
	int rows, cols;
	int* Term; // 1차원으로 정의하고 있음 
};

Matrix::Matrix(int row, int col) : rows(row), cols(col)
{
	Term = new int[rows * cols];
}

int Matrix::GetData() { // 화면에서 입력받거나 난수를 생성하는걸로 바꿀수 있음?
	int input_value;
	cout << "rows = " << rows << "  cols = " << cols << endl; // private이니깐 그냥 쓰는거?
	for (int j = 0; j < rows * cols; j++)
	{
		cout << "term value = ";
		cin >> input_value; 
		cout << " " << endl;
		Term[j] = input_value; // 쭉 나열?
	}
	return 0;
}

Matrix Matrix::Transpose() { // 전치행렬
	Matrix b(cols, rows);

	int n = rows * cols;
	for (int i = 0; i < cols; i++)
	{
		//To be implemented
		for(int j = 0; j < rows; j++)
        {
			b.Term[i * rows + j] = Term[i + j * cols];
        }
	}
	cout << endl;
	return b;
}

Matrix Matrix::Multiply(Matrix b) {
	if (cols != b.rows) cout << "Imcompatible matrices" << endl;
	Matrix d(rows, b.cols); // 여기서 이미 크기에 대하여 결정 됨.
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < b.cols; j++)
		{
			//To be implemented
			d.Term[i * b.cols + j] = 0;
			for (int k = 0; k < cols; k++)
			{
				cout << Term[i * cols + k] << " " << b.Term[k * b.cols + j] << endl;
				d.Term[i * b.cols + j] += Term[i * cols + k] * b.Term[k * b.cols + j];
			}
			cout << d.Term[i * b.cols + j] << endl;
		}
	}
	return d;
}

Matrix Matrix::Add(Matrix b) {
	if (cols != b.cols) cout << "Incompatible matrices" << endl;
	if (rows != b.rows) cout << "Incompatible matrices" << endl;

	Matrix d(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		//To be implemented
		for (int j = 0; j < cols; j++)
		{
			d.Term[i * cols + j] = Term[i * cols + j] + b.Term[i * cols + j];
		}
	}
	return d;
}

Matrix Matrix::Sub(Matrix b) {
	if (cols != b.cols) cout << "Incompatible matrices" << endl;
	if (rows != b.rows) cout << "Incompatible matrices" << endl;

	Matrix d(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
		    //To be implemented
			d.Term[i * cols + j] = Term[i * cols + j] - b.Term[i * cols + j];
		}
	}
	return d;
}

Matrix Matrix::Multiply2(Matrix b) {
	if (cols != b.rows) cout << "Incompatible matrices" << endl;
	Matrix bXpose = b.Transpose();
	Matrix d(rows, b.cols);
	// Must be implemented by using bXpose
	return d;
}

int Matrix :: CompareRowCol(Matrix b) {
	if (cols != b.rows) return 1;
	else return 0;
}
int Matrix::Display() {
	int n;
	n = rows * cols;
	for (int i = 0; i < rows; i++)
	{
		//To be implemented
		for(int j = 0; j < cols; j++)
        {
		    cout << Term[i * cols + j] << ' ';

        }
		cout << endl;
	}
	cout << endl;
	return 0;
}

int main()
{
	Matrix a(12, 13);
	Matrix b(13, 14);
	Matrix c(12, 14);
	Matrix d(12, 14);
	Matrix t(14, 13);
	cout << "Enter first matrix: " << endl;
	a.GetData();
	cout << "Enter second matrix: " << endl;
	b.GetData();
	cout << "Display first matrix: " << endl;
	a.Display();
	cout << "Display second matrix: " << endl;
	b.Display();
	t = b.Transpose();
	cout << "Transpose() of Matrix b" << endl;
	t.Display();
	/* If colum of first matrix in not euqal to row of second matrix, asking user to enter the size of matrix again. */
	if (a.CompareRowCol(b))
	{
		cout << "Error! column of first matrix not equal to row of second.";
		cout << "Enter rows and columns for first matrix: ";
	}
	c = a.Multiply(b); //not using transpose()
	cout << "Multiply of Matrix a,b " << endl;
	c.Display(); //cout << c; // 옆에 것으로 바꿈
	cout << "Sub of Matrix c,d " << endl; // 추가

	cout << "Display D" << endl; // 확인용 추가
	d.Display(); // 확인용 추가

	d = c.Sub(d); // 빼기 잘 작동함 
	d.Display(); // cout << d; // 옆에 것으로 바꿈
	cout << "using transpose()" << endl;
	t = b.Transpose();
	c = a.Multiply2(t);
	c.Display(); // cout << c; // 옆에 것으로 바꿈
	system("pause");
	return 0;

}