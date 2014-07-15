#ifndef DEFS_H
#define DEFS_H
#include <cstdlib>
#include <limits>
using std::size_t; //The only reason for including cstdlib

#define NAN std::numeric_limits<double>::quiet_NaN();

struct RGB {
	unsigned int r : 8;
	unsigned int g : 8;
	unsigned int b : 8;
};

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
