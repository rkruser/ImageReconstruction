/*
 * beach
 * boats
 * einstein
 * stopSign2 (stopSign_)
*/
#define IMAGE einstein
#include "einstein.xpm"
#define charBuffer 10

#include "defs.h"

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <algorithm>

// Question: should I use double** and put r,g,b values next to each other?

RGB extractPixels(int);
void printImage(const Image&);
Image imProcess(const char**);

int main(int argc, char** argv) {
	std::clock_t timer;
	timer = std::clock();
	Image M;
	try {
	M = imProcess(IMAGE);
	}
	catch (too_many_chars_per_pixel e) {
		std::cerr << "Too many chars per pixel\n";
		exit(1);
	}
	catch (not_color_format e) {
		std::cerr << "Included XPM not in color format\n";
		exit(1);
	}
	catch (std::out_of_range e) {
		std::cerr << "Pixel descriptor not in hash table\n";
		exit(1);
	}
	timer = std::clock() - timer;
	//std::cout << "Time elapsed = " << double(timer)/CLOCKS_PER_SEC << '\n';
	
	//std::cout << M.size() << ' ' << M[0].size() << ' ' << M[0][0].size() << '\n';
	//Seems to be working
	//Load with fopen, fscanf
	//Load the printout in matlab, then do uint8(reshape(M', col, row)');
	//This will produce the correct read-in
	printImage(M);

	return 0;
}

RGB extractPixels(int n) {
	int Rmask = 0x00FF0000;
	int Gmask = 0x0000FF00;
	int Bmask = 0x000000FF;
	RGB p;
	p.r = (n&Rmask)>>16;
	p.g = (n&Gmask)>>8;
	p.b = n&Bmask;
	return p;
}

Image imProcess(const char** m) {
 // Read first line
 // Extract numbers
 // Hash table of colors
 // extract pixels
 // return object
 
	// Read and Process the first line
	size_t pos = 0;
	std::stringstream str(m[pos]); //Guaranteed to exist
	++pos;
	int columns, rows, colors, charsPerPixel;
	str >> columns >> rows >> colors >> charsPerPixel;

	if (charsPerPixel >= charBuffer) {
		too_many_chars_per_pixel error;
		throw error;
	}

	// Form hash table of colors
	std::unordered_map<std::string, RGB> colorTable;
	size_t limit = pos+colors;
	for ( ; pos < limit; ++pos) {
		std::stringstream str(m[pos]);
		char s[charBuffer]; //The number of chars won't exceed 4, most likely
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

	Image M(3, Row(rows, Column(columns,0))); //3 for r,g,b
	for (int i = 0; i < rows; ++i) {
		std::stringstream str(m[pos+i]);
		for (int j = 0; j < columns; ++j) {
			char s[charBuffer];
			str.get(s,charsPerPixel+1);
			RGB& pixel = colorTable.at(std::string(s));
			M[0][i][j] = pixel.r;
			M[1][i][j] = pixel.g;
			M[2][i][j] = pixel.b;
		}
	}

	return M;
}

void printImage(const Image& M) {
	for (size_t i = 0; i < M.size(); ++i) {
		for (size_t j = 0; j < M[i].size(); ++j) {
			for (size_t k = 0; k < M[i][j].size(); ++k) {
				std::cout << std::setw(4) << M[i][j][k];
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
}












