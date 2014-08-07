#include "defs.h"
#include "creation.h"

#include <iostream>
using namespace std;

int main() {
	/*
	Matrix<double> M = identity(6.00);
	cout << M << '\n';
	cout << 2*M << '\n';
	cout << M*2 << '\n';
	cout << M+3 << '\n';
	cout << 3+M << '\n';
	cout << M-4 << '\n';
	cout << 4-M << '\n';
	cout << M/5 << '\n';
	cout << 5/M << '\n';
	*/

	//Matrix<double> M2 = randMat(40,5);
	//M2.print(cout,4, 10);
	
	Matrix<double> M3 = randMat(400,400);
	Matrix<double> M4 = randMat(400,400);
	Matrix<double> M5 = M3*M4;
	cout << M5(90,150) << '\n';



	return 0;
}
