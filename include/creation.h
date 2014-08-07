#include "defs.h"
#include "submatrix.h"

//#include <cstdlib>
#include <random>

template <class U>
Matrix<U> identity(U size) {
	size_t intSize = size_t(size);
	Matrix<U> I(intSize,intSize,0);
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


