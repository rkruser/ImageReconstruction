#ifndef CREATION_H
#define CREATION_H

#include "defs.h"
#include "submatrix.h"

//#include <cstdlib>
#include <random>
/*
Matrix<double> identity(size_t size) {
	Matrix<double> I(size,size,0);
	for (size_t i = 0; i < size; i++) {
		I(i,i) = 1;
	}
	return I;
}

Matrix<double> randMat(size_t rows, size_t cols) {
	Matrix<double> mat(rows,cols);
	std::uniform_real_distribution<> randNums;
	std::minstd_rand generator(1);
	for (size_t k = 0; k < mat.numElts(); k++) {
		mat(k) = randNums(generator);
	}
	return mat;
}
*/

#endif
