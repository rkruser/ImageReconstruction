#include "defs.h"
#include "read.h"

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <cmath>

#define CHARBUFFER 10

RGB extractPixels(int n) {
	RGB p;
	p.r = (n >> 16) & 0xff;
	p.g = (n >> 8) & 0xff;
	p.b = n&0xff;
	return p;
}

Image makeGrayScale(const Image& M) {
	if (M.frames <= 1) return M;
	Image newIm(M.rows,M.cols,1);
	for (size_t i = 0; i < M.rows; ++i) {
		for (size_t j = 0; j < M.cols; ++j) {
			newIm(i,j,0) = std::round(0.2989*M(i,j,0)+0.5870*M(i,j,1)+0.1140*M(i,j,2));
			//The numbers come from the literature on apparent brightness of various colors
		}
	}
	return newIm;
}

Image imProcess(const char** m) {
 // Read first line
 // Extract numbers
 // Hash table of colors
 // extract pixels
 // return object
 
	// Read and Process the first line
	size_t pos = 0;
	std::stringstream str(m[pos]);
	++pos;
	int columns, rows, colors, charsPerPixel;
	str >> columns >> rows >> colors >> charsPerPixel;

	if (charsPerPixel >= CHARBUFFER) {
		too_many_chars_per_pixel error;
		throw error;
	}

	// Form hash table of colors
	std::unordered_map<std::string, RGB> colorTable;
	size_t limit = pos+colors;
	for ( ; pos < limit; ++pos) {
		std::stringstream str(m[pos]);
		char s[CHARBUFFER];
		str.get(s, charsPerPixel+1);
		char option;
		str >> option; //Read color option
		if (option != 'c') {
			not_color_format error;
			throw error;
		}
		str >> option; //To get rid of # symbol
		int color;
		str >> std::hex >> color;
		RGB pixelValue;
		pixelValue = extractPixels(color);
		colorTable.insert(std::make_pair(std::string(s),pixelValue));
	}

	//Form the image
	Image M(rows, columns, 3);
	for (int i = 0; i < rows; ++i) {
		std::stringstream str(m[pos+i]);
		for (int j = 0; j < columns; ++j) {
			char s[CHARBUFFER];
			str.get(s,charsPerPixel+1);
			RGB& pixel = colorTable.at(std::string(s));
			M(i,j,0) = pixel.r;
			M(i,j,1) = pixel.g;
			M(i,j,2) = pixel.b;
		}
	}

	return M;
}

void printImage(const Image& M) {
	int numberOfTimes = 1;
	if (M.frames == 1) numberOfTimes = 3;
	for (int n = 1; n <= numberOfTimes; n++) {
		for (size_t l = 0; l < M.size; ++l) {
			if (std::isnan(M(l))) {
				std::cout << 255 << '\n';
			}
			else {
				std::cout << M(l) << '\n';
			}
		}
	}
}

