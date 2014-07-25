#include "defs.h"

#include <iostream>
using namespace std;

int main() {
	// Default constructor
	Matrix<double> M1;
	cout << "Default constructor:\n" << M1;

	// Size constructor
	Matrix<double> M2(3,2);
	cout << "Size constructor:\n" << M2;

	// Initializing constructor
	Matrix<double> M3(4,4,1);
	cout << "Initializing constructor:\n" << M3;

	// Element access
	M3(1,2) = 4;
	M3(2,1) = 5;
	M3(3,3) = -2;
	cout << "Element Access:\n" << M3;

	// Copy constructor
	Matrix<double> M4(M3);
	cout << "Copy constructor:\n" << M4;

	// Operator =
	Matrix<double> M5 = M4;
    cout << "Operator= :\n" << M5;

	// Sequential access
	cout << "Sequential access:\n";
	for (int i = 0; i < M5.numElts(); i++) {
		cout << M5(i) << '\n';
	}

	// Matrix times vector
	Matrix<double> A(2,2);
	A(0,0) = 2;
	A(0,1) = 2;
	A(1,0) = 2;
	A(1,1) = 1;
	Matrix<double> B(2,1);
	B(0) = 1;
	B(1) = 4;
	cout << "A=\n" << A;
	cout << "B=\n" << B;
	cout << "A*B=\n" << A*B;
	cout << "A*A=\n" << A*A;
	cout << "M4*M4=\n" << M4*M4;

	cout << "M4-M4=\n" << M4-M4;
	cout << "M4+M4=\n" << M4+M4;

	return 0;
}
