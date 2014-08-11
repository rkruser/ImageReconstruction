#include "sor.h"
#include "defs.h"
#include "submatrix.h"

#include <iostream>
using namespace std;

int main() {
	/*
	Matrix<double> A(2,2,0), B(2,1,0), X(2,1,0);
	A(0,0) = 2; 
	A(0,1) = -1;
	A(1,0) = -1;
	A(1,1) = 2;

	B(0) = -2;
	B(1) = 7;
	X(0) = 3;
	X(1) = 1;

	cout << "A:\n" << A << "B:\n" << B << "X\n" << X;
	cout << "A*x\n" << A*X;
	SOR(A, B, X, 1.1, 0.001);
	cout << "After SOR:\n" << X;
	*/
/*
	Matrix<double> A2(3,3,0), B2(3,1,0), X2(3,1,0);
	A2(0,0) = 2;
	A2(0,1) = -1;
	A2(0,2) = 2;
	A2(1,0) = -1;
	A2(1,1) = 2;
	A2(1,2) = -1;
	A2(2,0) = 2;
	A2(2,1) = -1;
	A2(2,2) = 3;
	B2(0) = 7;
	B2(1) = 1;
	B2(2) = 8;
	X2(0) = 5;
	X2(1) = 2;
	X2(2) = 1.5;
	cout << "A:\n" << A2 << "B:\n" << B2 << "X\n" << X2;
	cout << "A*x\n" << A2*X2;
	SOR(A2, B2, X2, 1.1, 0.00001);
	cout << "After SOR:\n" << X2;
*/
	Matrix<double> A3(2,2,0), B3(2,1,0), X3(2,1,0);
	A3(0,0) = 2;
	A3(0,1) = 2;
	A3(1,0) = 2;
	A3(1,1) = 1;
	B3(0) = 10;
	B3(1) = 6;
	X3(0) = 1.5;
	X3(1) = 3.5;
	cout << "A:\n" << A3 << "B:\n" << B3 << "X\n" << X3;
	SOR(A3, B3, X3, 1.1, 0.00001);
	cout << "After SOR:\n" << X3;


	return 0;
}
