#include "defs.h"

#include <iostream>
using namespace std;

int main() {
	Matrix<double> M(2,3,1);
	M(0,1) = 2;
	M(0,2) = 3;
	M(1,0) = 4;
	M(1,1) = 5;
	M(1,2) = 6;

	cout << M;
	M.transpose();
	cout << M;
	M.transpose();
	cout << M;
	M.transpose();
	cout << M;
	auto M2 = M;
	M2.transpose();
	cout << M*M2;



	return 0;
}
