#include "ALS.h"

// Returns A^t*A 
Matrix<double> selfProduct(const Matrix<double>& A) {
	Matrix<double> product(A.numCols(), A.numCols(), 0);
	for (size_t i = 0; i < A.numCols(); i++) {
		for (size_t j = 0; j <= i; j++) {
			for (size_t k = 0; k < A.numRows(); k++) {
				product(i,j) += A.tAccess(i,k)*A(k,j);
			}
			product(j,i) = product(i,j);
		}
	}
	return product;
}

template <class S>
Matrix<double> transProduct(const Matrix<double>& A, const S<double>& B) {
	if (A.numRows() != B.numRows()) {
		Matrix::size_mismatch error;
		throw error;
	}
	Matrix<double> product(A.numCols(), B.numCols(), 0);
	for (size_t i = 0; i < A.numCols(); i++) {
		for (size_t j = 0; j < B.numCols(); j++) {
			for (size_t k = 0; k < A.numRows(); k++) {
				product(i,j) += A.tAccess(i,k)*B(k,j);
			}
		}
	}
	return product;
}

void diagonalAdd(Matrix<double& M, double lambda) {
	for (size_t i = 0; i < std::min(M.numRows(),M.numCols()); i++) {
		M(i,i) += lambda;
	}
}

Matrix<double> ALS(Matrix<double> M, int features, double lambda, int maxIter) {
	size_t m, n;
	m = M.numRows();
	n = M.numCols();
	int numIter = 0;
	Matrix<double> U = randMat(m, features);
	Matrix<double> V(n, features, 0);

	std::vector<std::vector<size_t> > selectors;
	selectors.reserve(n+m);
	for (size_t j = 0; j < n; j++) {
		std::vector<size_t> indices;
		indices.reserve(m); // Reserves may not be necessary
		for (size_t i = 0; i < m; i++) {
			if (!std::isnan(M(i,j))) {
				indices.push_back(i);
			}
		}
		selectors.push_back(std::move(indices));
	}
	for (size_t j = 0; j < m; j++) {
		std::vector<size_t> indices;
		indices.reserve(n);
		for(size_t i = 0; i < n; i++) {
			if (!std::isnan(M.tAccess(i,j))) {
				indices.push_back(i);
			}
		}
		selectors.push_back(std::move(indices));
	}



	// Idea: create a whole bunch of submatrix objects in advance
	// Perhaps modify the objects so as to efficiently undergo mitosis

	while (numIter < maxIter) {
		Matrix<double> newU(U.numRows(), U.numCols(), 0);
		Matrix<double> newV(V.numRows(), V.numCols(), 0);

		for (size_t i = 0; i < n; i++) {
			if (selectors[i].size() > 0) {
				Submatrix<double> A(U, selectors[i]);
				Column<double> B(M, selectors[i], i);
				Matrix<double> left = selfProduct(A);
				diagonalAdd(left,lambda);
				Matrix<double> right = transProduct(A,B);


			}
		}

		for (size_t j = 0; j < m; j++ ) {
			if (selectors[n+j].size() > 0) {


			}
		}








		numIter++;
	}

}
