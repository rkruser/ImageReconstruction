#include "defs.h"

#include <vector>


class size_mismatch{};

template <class T>
class Submatrix {
	public:

		Submatrix(Matrix<T>& mat) : M(mat) {};
		~Submatrix() {
		   	indices.~vector<size_t>();
		}

		void pushIndex(size_t i) {
			indices.push_back(i);
		}

		T& operator() (size_t i, size_t j) {
			return M(indices[i], j);
		}
		const T& operator() (size_t i, size_t j) const {
			return M(indices[i], j);
		}
		T& operator() (size_t i) {
			return M(indices[i/numCols()], i%numCols());
		}
		const T& operator() (size_t i) const {
			return M(indices[i/numCols()], i%numCols());
		}	
		size_t numRows() {
			return indices.size();
		}
		size_t numCols() {
			return M.numCols();
		}
		size_t numElts() {
			return indices.size()*M.numCols();
		}

		template <class S>
		Submatrix<T>& operator= (const S&);
		
		template <class S>
		void operator+= (const S&);

		template <class S>
		void operator-= (const S&);

		template <class S>
		void operator*= (const S&);

	private:
		Matrix<T>& M;
		std::vector<size_t> indices;
};

template <class T>
template <class S>
Submatrix<T>& Submatrix<T>::operator= (const S& mat) {
	if (mat.numRows() != numRows() or mat.numCols() != numCols()) {
		size_mismatch error;
		throw error;
	}

	for (size_t i = 0; i < numRows(); i++) {
		for (size_t j = 0; j < numCols(); j++) {
			(*this)(i,j) = mat(i,j);
		}
	}
	
	return *this;
}

template <class T>
template <class S>
void Submatrix<T>::operator+= (const S& mat) {
	if (mat.numRows() != numRows() or mat.numCols() != numCols()) {
		size_mismatch error;
		throw error;
	}

	for (size_t i = 0; i < numRows(); i++) {
		for (size_t j = 0; j < numCols(); j++) {
			(*this)(i,j) += mat(i,j);
		}
	}
}

template <class T>
template <class S>
void Submatrix<T>::operator-= (const S& mat) {
	if (mat.numRows() != numRows() or mat.numCols() != numCols()) {
		size_mismatch error;
		throw error;
	}

	for (size_t i = 0; i < numRows(); i++) {
		for (size_t j = 0; j < numCols(); j++) {
			(*this)(i,j) -= mat(i,j);
		}
	}
}

template <class T>
template <class S>
void Submatrix<T>::operator*= (const S& mat) {
	if (numCols() != mat.numRows() or numCols() != mat.numCols()) {
		size_mismatch error;
		throw error;
	}

	Matrix<T> newmat(numRows(), numCols(),0);
	for (size_t i = 0; i < numRows(); i++) {
		for (size_t j = 0; j < numCols(); j++) {
			for (size_t k = 0; k < numCols(); k++) {
				newmat(i,j) += (*this)(i,k)*mat(k,j);
			}
		}
	}
	(*this) = newmat;
}

/*
template <class T, class S, class U>
static void add(Matrix<T>& mat, const S& larg, const U& rarg) {
	for (size_t i = 0; i < larg.numRows(); i++) {
		for (size_t j = 0; j < larg.numCols(); j++) {
			mat(i,j) = larg(i,j) + rarg(i,j);
		}
	}
}

template <class T>
Matrix<T> operator+ (const Submatrix<T>& A, const Submatrix<T>& B) {
	Matrix<T> mat(A.numRows(),A.numCols(),0);
	if (A.numRows() != B.numRows() or A.numCols() != B.numCols()) {
		size_mismatch error;
		throw error;
	}
	add(mat, A, B);
	return mat;
}
*/
