#include "ALS.h"
#include <random>
#include <cassert>
#include <iostream>
using std::cout;

const double w = 1.1;
const double convergence = 0.0001;

Matrix<double> randMat(size_t rows, size_t cols) {
	Matrix<double> mat(rows,cols);
	std::uniform_real_distribution<> randNums;
	std::minstd_rand generator(1);
	for (size_t k = 0; k < mat.numElts(); k++) {
		mat(k) = randNums(generator);
	}
	return mat;
}

// Returns A^t*A 
template <class S>
Matrix<double> selfProduct(const S& A) {
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

template <class R, class S>
Matrix<double> transProduct(const R& A, const S& B) {
	if (A.numRows() != B.numRows()) {
		Matrix<double>::size_mismatch error;
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

void diagonalAdd(Matrix<double>& M, double lambda) {
	for (size_t i = 0; i < std::min(M.numRows(),M.numCols()); i++) {
		M(i,i) += lambda;
	}
}

Matrix<double> ALS(Matrix<double>& M, int features, double lambda, int maxIter) {
	size_t m, n;
	m = M.numRows();
	n = M.numCols();
	int numIter = 0;
	Matrix<double> U = randMat(m, features);
	Matrix<double> V = randMat(features, n);
	std::vector<size_t> fullFeatureCol(features);
	for (size_t i = 0; i < features; i++) {
		fullFeatureCol[i] = i;
	}

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
		cout << "Loop " << numIter << '\n';
		for (size_t i = 0; i < n; i++) {
			if (selectors[i].size() > 0) {
				Submatrix<double> A(U, selectors[i]);
				Column<double> B(M, selectors[i], i);
				Matrix<double> left = selfProduct(A);
				diagonalAdd(left,lambda);
				Matrix<double> right = transProduct(A,B);
				Column<double> X(V, fullFeatureCol, i);
				SOR(left, right, X, w, convergence);
			}
		}
		U.shallowTranspose();
		V.shallowTranspose();
		for (size_t j = 0; j < m; j++ ) {
			if (selectors[n+j].size() > 0) {
				Submatrix<double> A(V, selectors[n+j]);
				Column<double> B(M, selectors[n+j], j);
				Matrix<double> left = selfProduct(A);
				diagonalAdd(left,lambda);
				Matrix<double> right = transProduct(A,B);
				Column<double> X(U, fullFeatureCol, j);
				SOR(left,right,X,w,convergence);
			}
		}
		U.shallowTranspose();
		V.shallowTranspose();
		
		numIter++;
	}
	
	return U*V;
}
