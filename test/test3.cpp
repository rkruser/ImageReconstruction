#include "sor.h"
#include "defs.h"

#include <iostream>
using namespace std;

int main() {
	Matrix<double> A(2,2,0), B(2,1,0), X(2,1,0);
	A(0,0) = A(0,1) = A(1,0) = 2;
	A(1,1) = 1;

	B(0) = 10;
	B(1) = 6;
	X(0) = 1.10;
	X(1) = 3.92;

	cout << "A:\n" << A << "B:\n" << B << "X\n" << X;
	SOR(A, B, X, 0.05, 0.000000001);
	cerr << "After SOR:\n" << X;

	



	return 0;
}
