#include "submatrix.h"
#include "defs.h"

#include <iostream>
using namespace std;

int main() {
	Matrix<double> M(5,5,0);
	for (size_t i = 0; i < M.numElts(); i++) {
		M(i) = i;
	}
	Submatrix<double> S(M);
	S.pushIndex(0);
	S.pushIndex(3);
	cout << M << '\n' << S << '\n';
	S(1,2) = -4;
	cout << M << '\n' << S << '\n';

	for (size_t i = 0; i < S.numElts(); i++) {
		S(i) = -8;
	}

	cout << M << '\n' << S << '\n';

	Matrix<double> M2(S.numRows(), S.numCols(), 1);
	S = S + M2;
	cout << M << '\n' << S << '\n';
	S += M2;
	cout << M << '\n' << S << '\n';

	Matrix<double> M3(S.numCols(), S.numCols(), 2);
	S *= M3;
	cout << M << '\n' << S << '\n';

	M2.shallowTranspose();
	cout << M2 << '\n';
	try {
		S *= M2;
	}
	catch (size_mismatch e) {
		cout << "size_mismatch error caught\n\n";
	}

	cout << S*M2 << '\n' << M2*S << '\n';

	//S *= M;
	//cout << M << '\n' << S << '\n';
	S = S*M;
	cout << M << '\n' << S << '\n';






	

	return 0;
}
