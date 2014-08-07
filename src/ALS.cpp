#include "ALS.h"

Matrix<double> ALS(Matrix<double> M, int features, double lambda, int maxIter) {
	size_t m, n;
	m = M.numRows();
	n = M.numCols();
	int numIter = 0;
	Matrix<double> U = randMat(m, features);
	Matrix<double> V(n, features, 0);

	// Idea: create a whole bunch of submatrix objects in advance
	// Perhaps modify the objects so as to efficiently undergo mitosis

	while (numIter < maxIter) {
		Matrix<double> newU(U.numRows(), U.numCols(), 0);
		Matrix<double> newV(V.numRows(), V.numCols(), 0);

		for (size_t i = 0; i < m; i++) {


		}

		for (size_t j = 0; j < n; j++ ) {


		}








		numIter++;
	}

}
