#include "defs.h"
#include "submatrix.h"
#include "column.h"

#include <iostream>
#include <vector>
using namespace std;

int main() {
	Matrix<double> A(5,5,0);
	for (size_t i = 1; i < A.numElts(); i++) {
		A(i) = i;
	}
	vector<size_t> indices;
	indices.push_back(1);
	indices.push_back(3);
	Submatrix<double> B(A,indices);
	Column<double> C(A,indices,3);

	cout << A << '\n';
	cout << B << '\n';
	cout << C << '\n';




	return 0;
}
