#ifndef DEFS_H
#define DEFS_H
#include <cstdlib>
#include <limits>
#include <iostream>
#include <iomanip>
using std::size_t; //The only reason for including cstdlib

#define NAN std::numeric_limits<double>::quiet_NaN();

struct RGB {
	unsigned int r : 8;
	unsigned int g : 8;
	unsigned int b : 8;
};


//***************************************************************
//Matrix class
template <class T>
class Matrix {
	public:
		class size_mismatch {};

		Matrix();
		Matrix(const Matrix<T>&);
		Matrix(size_t, size_t);
		Matrix(size_t, size_t, T);
		Matrix<T>& operator= (const Matrix<T>&);
		~Matrix();

		size_t numElts() const { return size;}
		size_t numRows() const { return rows;}
		size_t numCols() const { return cols;}
		T& operator() (size_t i) { return array[i]; }
		const T& operator() (size_t i) const { return array[i]; }
		T& operator() (size_t i, size_t j) { return array[i*cols+j]; }
		const T& operator() (size_t i, size_t j) const { return array[i*cols+j]; }

		void operator+=(const Matrix<T>&);
		void operator*=(const Matrix<T>&);
		void operator-=(const Matrix<T>&);

		void print(std::ostream&); //Note: Type T should be printable using << operator


	private:
		T* array;
		size_t size;
		size_t rows;
		size_t cols;
		void copy(const Matrix<T>&);
};

template <class T>
void Matrix<T>::copy(const Matrix<T>& M) {
	size = M.size;
	rows = M.rows;
	cols = M.cols;
	array = new T[size];
	for (size_t i = 0; i < size; i++) {
		array[i] = M.array[i];
	}
}

template <class T>
Matrix<T>::Matrix() : 
	array(nullptr),
	size(0),
	rows(0),
	cols(0) {}

template <class T>
Matrix<T>::Matrix(const Matrix& M) {
	copy(M);
}

template <class T>
Matrix<T>::Matrix(size_t a, size_t b) {
	rows = a;
	cols = b;
	size = a*b;
	array = new T[size];
}


template <class T>
Matrix<T>::Matrix(size_t r, size_t c, T fill) :
	size(r*c),
	rows(r),
	cols(c) {
		array = new T[size];
		for (size_t i = 0; i < size; i++) array[i] = fill;
}

template <class T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& M) {
	delete[] array;
	copy(M);
	return *this;
}

template <class T>
Matrix<T>::~Matrix() {
	delete[] array;
}

template <class T>
void Matrix<T>::print(std::ostream& out) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			out << std::setprecision(4) << std::setw(5) << (*this)(i,j);
		}
		out << '\n';
	}	
	/*
	for (size_t i = 0; i < size; i++) {
		out << array[i] << '\n';
	}
	*/
}

// Nonmember function, overloading output
template <class T>
std::ostream& operator<< (std::ostream& out, Matrix<T> M) {
	M.print(out);
	return out;
}

template <class T>
void Matrix<T>::operator+=(const Matrix<T>& M) {
	if (M.rows != rows or M.cols != cols) {
		size_mismatch s;
		throw s;
	}
	for (size_t i = 0; i < size; i++) {
		array[i] += M.array[i];
	}
}

template <class T>
void Matrix<T>::operator-=(const Matrix<T>& M) {
	if (M.rows != rows or M.cols != cols) {
		size_mismatch s;
		throw s;
	}
	for (size_t i = 0; i < size; i++) {
		array[i] -= M.array[i];
	}
}


//Careful returning a reference
//Not sure if this is bad when return value is probably temporary
template <class T>
Matrix<T> operator+ (const Matrix<T>& A, const Matrix<T>& B) {
	Matrix<T> C(A);
	C += B;
	return C;
}

template <class T>
Matrix<T> operator- (const Matrix<T>& A, const Matrix<T>& B) {
	Matrix<T> C(A);
	C -= B;
	return C;
}

// Possibly change this
// Makes transposition difficult, maybe
template <class T>
void Matrix<T>::operator*= (const Matrix<T>& M) {
	if (cols != M.rows) {
		size_mismatch s;
		throw s;
	}
	T* result = new T[rows*M.cols];
	for (size_t i = 0; i < rows*M.cols; i++) {
		result[i] = 0;
	}
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < M.cols; j++) {
			T& entry = result[i*M.cols+j];
			for (size_t k = 0; k < cols; k++) {
				entry += (*this)(i,k)*M(k,j);
			}
		}
	}
	delete[] array;
	array = result;
	size = rows*M.cols;
	cols = M.cols;
}

template <class T>
Matrix<T> operator* (const Matrix<T>& A, const Matrix<T>& B) {
	Matrix<T> C(A);
	C*=B;
	return C;
}


//************************************************

struct Image {
	double * array;
	size_t size;
	size_t framesize;
	size_t frames;
	size_t rows;
	size_t cols;

	Image() {
		size = 0;
		framesize = 0;
		frames = 0;
		rows = 0;
		cols = 0;
		array = nullptr;
	}

	Image(size_t r, size_t c, size_t f) {
		frames = f;
		rows = r;
		cols = c;
		size = f*r*c;
		framesize = r*c;
		array = new double[size];
		for (size_t i = 0; i < size; ++i) {
			array[i] = NAN;
		}
	}

	
	Image(const Image& M) {
		copy(M);
	}
	
	Image& operator= (const Image& M) {
		delete[] array;
		copy(M);
		return *this;
	}

	~Image() {
		delete[] array;
	}

	// Careful with the reference!
	double& operator() (size_t index) {
		return array[index];
	}

	const double& operator()(size_t index) const {
		return array[index];
	}

	double& operator() (size_t r, size_t c, size_t f) {
		return array[f*framesize + r*cols + c];
	}

	const double& operator() (size_t r, size_t c, size_t f) const {
		return array[f*framesize + r*cols + c];
	}

	private:
	void copy(const Image& M) {
		array = new double[M.size];
		for (size_t i = 0; i < M.size; ++i) {
			array[i] = M.array[i];
		}
		size = M.size;
		framesize = M.framesize;
		frames = M.frames;
		rows = M.rows;
		cols = M.cols;
	}
};

class too_many_chars_per_pixel {};
class not_color_format {};



#endif
