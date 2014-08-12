#ifndef SOR_H
#define SOR_H

#include "defs.h"
#include "submatrix.h"
#include "column.h"
#include "creation.h"
#include <iostream>
#include <cmath>
using std::cout;

template <class Mat>
double norm(const Mat& x) {
	double sum = 0;
	for (size_t i = 0; i < x.numElts(); i++) {
		sum += x(i)*x(i);
	}
	return std::sqrt(sum);
}

// Solves Ax = B for x
// A must be square
// Puts result in x
// x should contain an initial guess at the solution
// w is the "relaxation factor", in (0,2)
// convergence is the value we tolerate 
// Function is templated to accomodate different matrix types
// 	that have the same operators.
template <class Mat1, class Mat2, class Mat3> 
void SOR(const Mat1& A, const Mat2& B, Mat3& x, double w, double convergence) {
	class not_square {};
	class not_column_vector{};
	class size_mismatch{};
	if (A.numRows() != A.numCols()) {
		not_square n;
		throw n;
	}
	if (B.numCols() > 1 or x.numCols() > 1) {
		not_column_vector e;
		throw e;
	}
	if (B.numRows() != A.numCols() or x.numRows() != A.numCols()) {
		size_mismatch s;
		throw s;
	}

	double normB = norm(B);
	double difference = norm(A*x - B) / normB;
	while (difference > convergence) {
		for (size_t i = 0; i < A.numRows(); i++) {
			double sigma = 0;
			for (size_t j = 0; j < B.numRows(); j++) {
				if (j != i)  {
					sigma += A(i,j)*x(j);
				}
			}
			x(i) = x(i) + w*(((B(i) - sigma) / A(i,i)) - x(i));
		}
		difference = norm(A*x - B) / normB;
	}
}



#endif
