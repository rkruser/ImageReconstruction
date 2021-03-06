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

// Make a color image into a black and white image
Image makeGrayScale(const Image& M) {
	if (!M.color) return M;
	Image newIm(M.R.numRows(),M.R.numCols(),false);
	for (size_t i = 0; i < M.R.numRows(); ++i) {
		for (size_t j = 0; j < M.R.numCols(); ++j) {
			newIm(i,j) = std::round(0.2989*M.R(i,j)+0.5870*M.G(i,j)+0.1140*M.B(i,j));
			//The numbers come from the literature on apparent brightness of various colors
		}
	}
	return newIm;
}

// Turn the included xpm file into an image object
Image imProcess(const char** m, bool colored) {
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
	Image M(rows, columns, colored);
	for (int i = 0; i < rows; ++i) {
		std::stringstream str(m[pos+i]);
		for (int j = 0; j < columns; ++j) {
			char s[CHARBUFFER];
			str.get(s,charsPerPixel+1);
			RGB& pixel = colorTable.at(std::string(s));
			M(i,j) = pixel.r;
			if (colored) {
				M.G(i,j) = pixel.g;
				M.B(i,j) = pixel.b;
			}
		}
	}

	return M;
}

// Print the image to the desired ostream object
void printImage(std::ostream& out, const Image& M) {
	out << M.color << '\n';
	M.R.write(out);
	if (M.color) {
		M.G.write(out);
		M.B.write(out);
	}
}

