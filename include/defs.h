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
		Matrix(size_t, size_t);
		Matrix(size_t, size_t, T);
		Matrix(const Matrix<T>&);
		Matrix<T>& operator= (const Matrix<T>&);
		Matrix(Matrix<T>&&); //Move copy
		Matrix<T>& operator= (Matrix<T>&&); //Move assignment
		~Matrix();

		size_t numElts() const { return rows*cols;}
		size_t numRows() const { return rows;}
		size_t numCols() const { return cols;}
		T& operator() (size_t i) { return array[i]; }
		const T& operator() (size_t i) const { return array[i]; }
		T& operator() (size_t i, size_t j) { return array[i*cols+j]; }
		const T& operator() (size_t i, size_t j) const { return array[i*cols+j]; }

		void operator+=(const Matrix<T>&);
		void operator*=(const Matrix<T>&);
		void operator-=(const Matrix<T>&);
			
		//Note: Type T should be printable using << operator
		void print(std::ostream&); 
		void write(std::ostream&); //For writing to files


	private:
		T* array;
		size_t rows;
		size_t cols;
		void copy(const Matrix<T>&);
};

template <class T>
void Matrix<T>::copy(const Matrix<T>& M) {
	rows = M.rows;
	cols = M.cols;
	array = new T[rows*cols];
	for (size_t i = 0; i < rows*cols; i++) {
		array[i] = M.array[i];
	}
}

template <class T>
Matrix<T>::Matrix() : 
	array(nullptr),
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
	array = new T[rows*cols];
}


template <class T>
Matrix<T>::Matrix(size_t r, size_t c, T fill) :
	rows(r),
	cols(c) {
		array = new T[r*c];
		for (size_t i = 0; i < r*c; i++) array[i] = fill;
}

template <class T>
Matrix<T>::Matrix(Matrix<T>&& M) {
	array = M.array;
	rows = M.rows;
	cols = M.cols;

	M.array = nullptr;
	M.rows = M.cols = 0;
}

template <class T>
Matrix<T>& Matrix<T>::operator= (Matrix<T>&& M) {
	if (this != &M) {
		delete[] array;
		array = M.array;
		rows = M.rows;
		cols = M.cols;

		M.array = nullptr;
		M.rows = M.cols = 0;
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& M) {
	// Self-assignment does nothing
	if (this != &M) {
		delete[] array;
		copy(M);
	}
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
}

template <class T>
void Matrix<T>::write(std::ostream& out) {
	out << rows << '\n' << cols << '\n';
	for (size_t i = 0; i < rows*cols; i++) {
		out << array[i] << '\n';
	}
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
	for (size_t i = 0; i < rows*cols; i++) {
		array[i] += M.array[i];
	}
}

template <class T>
void Matrix<T>::operator-=(const Matrix<T>& M) {
	if (M.rows != rows or M.cols != cols) {
		size_mismatch s;
		throw s;
	}
	for (size_t i = 0; i < rows*cols; i++) {
		array[i] -= M.array[i];
	}
}

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
	cols = M.cols;
}

template <class T>
Matrix<T> operator* (const Matrix<T>& A, const Matrix<T>& B) {
	Matrix<T> C(A);
	C*=B;
	return C;
}


//************************************************

template <class T>
struct Image { 
	bool color;
	Matrix<T> R;
	Matrix<T> G;
	Matrix<T> B;

	Image():
		R(),
		G(),
		B(),
		color(false){};
	Image(size_t a, size_t b, bool c = false):
		R(a,b),
		color(c){
			if (c) {
				G = B = Matrix<T>(a,b);
			}
	};
	Image(size_t a, size_t b, T v, bool c = false):
		R(a,b,v),
		G(),
		B(),
		color(c){
			if (c) {
				G = B = Matrix<T>(a,b,v);
			}
	};

	T& operator() (size_t x, size_t y) {
		return R(x,y);
	}
	const T& operator() (size_t x, size_t y) const {
		return R(x,y);
	}

};





/*
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
*/

class too_many_chars_per_pixel {};
class not_color_format {};



#endif
