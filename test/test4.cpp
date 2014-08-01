#include "defs.h"

#include <iostream>
using namespace std;

Matrix<double> func() {
	Matrix<double> B(2,2,0);
	B(1,1) = 19;
	return B;
}

int main() {
	Matrix<double> M(2,3,1);
	M(0,1) = 2;
	M(0,2) = 3;
	M(1,0) = 4;
	M(1,1) = 5;
	M(1,2) = 6;

	cout << M << '\n';
	M.shallowTranspose();
	cout << M << '\n';
	M.shallowTranspose();
	cout << M << '\n';
	M.shallowTranspose();
	cout << M << '\n';
	auto M2 = M;
	M2.shallowTranspose();
	cout << M*M2 << '\n';
	Matrix<double> M3;
    M3 = M*M2;
	cout << "M3!\n" << M3 << '\n';
	M3.shallowTranspose();
	cout << "Shallow M3t!\n" << M3 << '\n';
	M2.deepTranspose();
	cout << "deep:\n" << M2 << '\n';
	M2.deepTranspose();
	cout << "deep:\n" << M2 << '\n';
	M2.deepTranspose();
	cout << "deep:\n" << M2 << '\n';
	M2 = func();
	cout << "After func:\n" << M2 << '\n';
	


	return 0;
}
