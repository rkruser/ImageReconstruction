#ifndef DEFS_H
#define DEFS_H
#include <cstdlib>
#include <limits>
#include <iostream>
#include <iomanip>
#include <utility>
#include <typeinfo>
using std::size_t; //The only reason for including cstdlib

#define NAN std::numeric_limits<double>::quiet_NaN();

struct RGB {
	unsigned int r : 8;
	unsigned int g : 8;
	unsigned int b : 8;
};


//***************************************************************
//Matrix class
// Still need to test the scalar operators
template <class T>
class Matrix {
	public:
		class size_mismatch {};

		// Fundamental functions
		Matrix();
		Matrix(size_t, size_t);
		Matrix(size_t, size_t, T);
		Matrix(const Matrix<T>&); //Copy constructor
		Matrix<T>& operator= (const Matrix<T>&); //Assignment operator
		Matrix(Matrix<T>&&); //Move copy
		Matrix<T>& operator= (Matrix<T>&&); //Move assignment
		~Matrix();

		// Templated constructor for type conversion
		template <class S>
		explicit Matrix(const Matrix<S>&);

		template <class S>
		Matrix<T>& operator= (const Matrix<S>&);

		// Array size data
		size_t numElts() const { return rows*cols;}
		size_t numRows() const { return rows;}
		size_t numCols() const { return cols;}
		
		// Access operators
		T& operator() (size_t i) { 
			if (transpose) return array[(i%cols)*rows+i/cols];
			else return array[i];
		}
		const T& operator() (size_t i) const { 
			if (transpose) return array[(i%cols)*rows+i/cols];
			else return array[i];
		}
		T& operator() (size_t i, size_t j) { 
			if (transpose) return array[j*rows+i];
			else return array[i*cols+j]; 
		}
		const T& operator() (size_t i, size_t j) const { 
			if (transpose) return array[j*rows+i];
			else return array[i*cols+j];
		}
		// Access elements as if array was transposed
		T& tAccess ( size_t i, size_t j) { return array[j*cols+i]; }
		T& tAccess(size_t i) { return array[(i%rows)*cols+i/rows]; }
		const T& tAccess(size_t i, size_t j) const { return array[j*cols+i]; }
		const T& tAccess(size_t i) const { return array[(i%rows)*cols+i/rows]; }

		// Access elements the way they are layed out in memory
		T& nAccess ( size_t i, size_t j) { return array[i*cols+j]; }
		T& nAccess(size_t i) { return array[i]; }
		const T& nAccess(size_t i, size_t j) const { return array[i*cols+j]; }
		const T& nAccess(size_t i) const { return array[i]; }

		// Transposition
		void deepTranspose();
		void shallowTranspose();

		// Algebraic operators
		void operator+=(const Matrix<T>&);
		void operator+=(T);
		void operator*=(const Matrix<T>&);
		void operator*=(T);
		void operator-=(const Matrix<T>&);
		void operator-=(T);
		void operator/=(T);
			
		//Note: Type T should be printable using << operator
		void print(std::ostream&) const; 
		void write(std::ostream&) const; //For writing to files


	private:
		T* array;
		bool transpose;
		size_t rows;
		size_t cols;

		template <class S>
		void copy(const Matrix<S>&);
};

//Private member function for utility
template <class T>
template <class S>
void Matrix<T>::copy(const Matrix<S>& M) {
	transpose = false;
	rows = M.rows;
	cols = M.cols;
	array = new T[rows*cols];
	for (size_t i = 0; i < rows*cols; i++) {
		array[i] = M(i);
	}
}

/****
 * Constructors, copy constructors, assignment operators, destructor
 ****/

// Default constructor
template <class T>
Matrix<T>::Matrix() : 
	array(nullptr),
	transpose(false),
	rows(0),
	cols(0)
	{}


// Copy constructor
template <class T>
Matrix<T>::Matrix(const Matrix<T>& M) {
	copy(M);
}

// Templated copy constructor
template <class T>
template <class S>
Matrix<T>::Matrix(const Matrix<S>& M) {
	copy(M);
}

// Constructor allocating dimensions
template <class T>
Matrix<T>::Matrix(size_t a, size_t b) {
	rows = a;
	cols = b;
	array = new T[rows*cols];
	transpose = false;
}

// Constructor allocating dimensions and initializing to a value
template <class T>
Matrix<T>::Matrix(size_t r, size_t c, T fill) :
	transpose(false),
	rows(r),
	cols(c)
	{
		array = new T[r*c];
		for (size_t i = 0; i < r*c; i++) array[i] = fill;
}

// Standard Assignment operator
template <class T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& M) {
	if (this != &M) {
		delete[] array;
		copy(M);
	}
	return *this;
}

// Templated Assignment
template <class T>
template <class S>
Matrix<T>& Matrix<T>::operator= (const Matrix<S>& M) {
	if (this != &M) {
		delete[] array;
		copy(M);
	}
	return *this;
}

// Move copy 
template <class T>
Matrix<T>::Matrix(Matrix<T>&& M) {
	array = M.array;
	rows = M.rows;
	cols = M.cols;
	transpose = M.transpose;

	M.array = nullptr;
	M.rows = M.cols = 0;
}

// Move assignment
template <class T>
Matrix<T>& Matrix<T>::operator= (Matrix<T>&& M) {
	if (this != &M) {
		delete[] array;
		array = M.array;
		rows = M.rows;
		cols = M.cols;
		transpose = M.transpose;

		M.array = nullptr;
		M.rows = M.cols = 0;
	}
	return *this;
}


// Destructor
template <class T>
Matrix<T>::~Matrix() {
	delete[] array;
}

/****
 * Transposition
 ****/

// Deep transpose: reorder data in memory
template <class T>
void Matrix<T>::deepTranspose() {
	shallowTranspose();
	if (transpose) {
		Matrix<T> newMat(*this);
		*this = std::move(newMat); 
	}
}

// Shallow transpose: access in different order
template <class T>
void Matrix<T>::shallowTranspose() {
	transpose = !transpose;
	std::swap(rows,cols);
}

/****
 * Functions for printing matrices
 ****/

// Pretty print
template <class T>
void Matrix<T>::print(std::ostream& out) const {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			out << std::setprecision(4) << std::setw(5) << (*this)(i,j);
		}
		out << '\n';
	}	
}

// File write
template <class T>
void Matrix<T>::write(std::ostream& out) const {
	out << rows << '\n' << cols << '\n';
	for (size_t i = 0; i < rows*cols; i++) {
		out << (*this)(i) << '\n';
	}
}

/****
 * Operators on Matrices
 ****/

// Output operator
template <class T>
std::ostream& operator<< (std::ostream& out, Matrix<T> M) {
	M.print(out);
	return out;
}

// Plus equals
template <class T>
void Matrix<T>::operator+=(const Matrix<T>& M) {
	if (M.rows != rows or M.cols != cols) {
		size_mismatch s;
		throw s;
	}
	for (size_t i = 0; i < rows*cols; i++) {
		(*this)(i) += M(i);
	}
}

// Plus equals with a scalar
template <class T>
void Matrix<T>::operator+=(T a) {
	for (size_t i = 0; i < rows*cols; i++) {
		(*this)(i) += a;
	}
}

// Minus equals
template <class T>
void Matrix<T>::operator-=(const Matrix<T>& M) {
	if (M.rows != rows or M.cols != cols) {
		size_mismatch s;
		throw s;
	}
	for (size_t i = 0; i < rows*cols; i++) {
		(*this)(i) -= M(i);
	}
}

// Minus equals with scalar
template <class T>
void Matrix<T>::operator-=(T a) {
	for (size_t i = 0; i < rows*cols; i++) {
		(*this)(i) -= a;
	}
}

// Plus operator
template <class T>
Matrix<T> operator+ (const Matrix<T>& A, const Matrix<T>& B) {
	Matrix<T> C(A);
	C += B;
	return C;
}

// Minus operator
template <class T>
Matrix<T> operator- (const Matrix<T>& A, const Matrix<T>& B) {
	Matrix<T> C(A);
	C -= B;
	return C;
}

// Times equals
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
	transpose = false;
}

// Times equals with scalar
template <class T>
void Matrix<T>::operator*= (T a) {
	for (size_t i = 0; i < rows*cols; i++) {
		(*this)(i) *= a;
	}
}

// Divided by equals (necessarily with scalar)
template <class T>
void Matrix<T>::operator/= (T a) {
	/*
	for (size_t i = 0; i < rows*cols; i++) {
		(*this)(i) /= a;
	}
	*/
	for (auto i = array; i != array + rows*cols; ) {
		*i++ /= a;
	}
}

// Times
template <class T>
Matrix<T> operator* (const Matrix<T>& A, const Matrix<T>& B) {
	Matrix<T> C(A);
	C*=B;
	return C;
}

// Times with right scalar
template <class T>
Matrix<T> operator* (const Matrix<T>& A, T b) {
	Matrix<T> C(A);
	C *= b;
	return C;
}

// Times with left scalar
template <class T>
Matrix<T> operator* (T a, const Matrix<T>& B) {
	Matrix<T> C(B);
	C *= a;
	return C;
}

//Divided by with right scalar
template <class T>
Matrix<T> operator/ (const Matrix<T>& A, T b) {
	Matrix<T> C(A);
	C /= b;
	return C;
}

//Divided by with left scalar
template <class T>
Matrix<T> operator/ (T a, const Matrix<T>& B) {
	Matrix<T> C(B);
	for (size_t i = 0; i < C.numElts(); i++) {
		C(i) = a / C(i);
	}
	return C;
}

//***********************************************

Matrix<double> identity(size_t size) {
	Matrix<double> I(size,size,0);
	for (size_t i = 0; i < size; i++) {
		I(i,i) = 1;
	}
	return I;
}

//************************************************

struct Image { 
	bool color;
	Matrix<double> R;
	Matrix<double> G;
	Matrix<double> B;

	Image():
		color(false),
		R(),
		G(),
		B(){};
	Image(size_t a, size_t b, bool c = false):
		color(c),
		R(a,b) {
			if (c) {
				G = B = Matrix<double>(a,b);
			}
	};
	Image(size_t a, size_t b, double v, bool c = false):
		color(c),
		R(a,b,v),
		G(),
		B() {
			if (c) {
				G = B = Matrix<double>(a,b,v);
			}
	};

	double& operator() (size_t x, size_t y) {
		return R(x,y);
	}
	const double& operator() (size_t x, size_t y) const {
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
