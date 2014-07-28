#ifndef SOR_H
#define SOR_H

#include "defs.h"
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
template <class Mat> 
void SOR(const Mat& A, const Mat& B, Mat& x, double w, double convergence) {
	class not_square {};
	class size_mismatch{};
	if (A.numRows() != A.numCols()) {
		not_square n;
		throw n;
	}
	if (B.numRows() != A.numRows() or x.numRows() != A.numRows()) {
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
