#include "defs.h"

#include <iostream>
using namespace std;

int main() {
	Matrix<double> M = identity(6);
	cout << M << '\n';
	cout << 2*M << '\n';
	cout << M*2 << '\n';
	cout << M+3 << '\n';
	cout << 3+M << '\n';
	cout << M-4 << '\n';
	cout << 4-M << '\n';
	cout << M/5 << '\n';
	cout << 5/M << '\n';
	




	return 0;
}
