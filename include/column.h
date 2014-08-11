#include "defs.h"

#include <ostream>
#include <iomanip>
#include <vector>


template <class T>
class Column {
	public:
		class size_mismatch{};

		Column(Matrix<T>& mat, const std::vector<size_t>& v, size_t col) :
			M(mat), 
			indices(v),
   			column(col)	{};
		Column(Matrix<T>& mat, const Column<T>& s) :
			M(mat),
			indices(s.indices) 
			column(s.column) {};

		T& operator() (size_t i, size_t j) {
			return M(indices[i], column);
		}
		const T& operator() (size_t i, size_t j) const {
			return M(indices[i], column);
		}
		T& operator() (size_t i) {
			return M(indices[i], column);
		}
		const T& operator() (size_t i) const {
			return M(indices[i], column);
		}	

		T& tAccess(size_t i) { return M(indices[i], column); }
		const T& tAccess(size_t i) const { return M(indices[i], column);}
		T& tAccess(size_t i, size_t j) { return M(indices[i],column); }
		const T& tAccess(size_t i, size_t j) const { return M(indices[i],column); }

		size_t numRows() const {
			return indices.size();
		}
		size_t numCols() const {
			return 1;
		}
		size_t numElts() const {
			return indices.size();
		}

		template <class S>
		Column<T>& operator= (const S&);
		
		template <class S>
		void operator+= (const S&);

		template <class S>
		void operator-= (const S&);

		template <class S>
		void operator*= (const S&);

		void print(std::ostream&);
		void write(std::ostream&);

	private:
		Matrix<T>& M;
		const std::vector<size_t>& indices;
		size_t column
};

template <class T>
void Column<T>::print(std::ostream& out) {
	for (size_t i = 0; i < numRows(); i++) {
		for (size_t j = 0; j < numCols(); j++) {
			out << std::setw(5) << (*this)(i,j);
		}
		out << '\n';
	}
}

template <class T>
void Column<T>::write(std::ostream& out) {
	out << numRows() << '\n' << numCols() << '\n';
	for (size_t i = 0; i < numRows()*numCols(); i++) {
		out << (*this)(i) << '\n';
	}
}

template <class T>
std::ostream& operator<< (std::ostream& out, Column<T> S) {
	S.print(out);
	return out;
}

template <class T>
template <class S>
Column<T>& Column<T>::operator= (const S& mat) {
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
void Column<T>::operator+= (const S& mat) {
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
void Column<T>::operator-= (const S& mat) {
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
void Column<T>::operator*= (const S& mat) {
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
// Wow, I'm absolutely amazed that the following worked
// Requires that A and B have indexing capabilities
// and numRows(), numCols() member functions
template < template <typename> class S, template <typename> class Y, typename T>
Matrix<T> operator+ (const S<T>& A, const Y<T>& B) {
	if (A.numRows() != B.numRows() or A.numCols() != B.numCols()) {
		Column::size_mismatch error;
		throw error;
	}

	Matrix<T> result(A.numRows(), A.numCols());
	for (size_t i = 0; i < A.numRows(); i++) {
		for (size_t j = 0; j < A.numCols(); j++) {
			result(i,j) = A(i,j) + B(i,j);
		}
	}

	return result;
}

template < template <typename> class S, template <typename> class Y, typename T>
Matrix<T> operator- (const S<T>& A, const Y<T>& B) {
	if (A.numRows() != B.numRows() or A.numCols() != B.numCols()) {
		Column::size_mismatch error;
		throw error;
	}

	Matrix<T> result(A.numRows(), A.numCols());
	for (size_t i = 0; i < A.numRows(); i++) {
		for (size_t j = 0; j < A.numCols(); j++) {
			result(i,j) = A(i,j) - B(i,j);
		}
	}

	return result;
}

template < template <typename> class S, template <typename> class Y, typename T>
Matrix<T> operator* (const S<T>& A, const Y<T>& B) {
	if (A.numCols() != B.numRows()) {
		Column::size_mismatch error;
		throw error;
	}

	Matrix<T> result(A.numRows(), B.numCols(),0);
	for (size_t i = 0; i < A.numRows(); i++) {
		for (size_t j = 0; j < B.numCols(); j++) {
			for (size_t k = 0; k < A.numCols(); k++) {
				result(i,j) += A(i,k)*B(k,j);
			}
		}
	}

	return result;
}
*/
