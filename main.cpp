/*
 * beach
 * boats
 * einstein
 * stopSign2
*/
#define IMAGE beach
#include "beach.xpm"
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
typedef std::vector<std::vector<std::vector<double>>> Image;
typedef std::vector<std::vector<double>> Row;
typedef std::vector<double> Column;


// Question: should I use double** and put r,g,b values next to each other?
Image imProcess(const char**);
RGB extractPixels(int);
void printImage(const Image&, Range, Range, Range);

int main(int argc, char** argv) {
	std::cout << "Hello World.\n";

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
	std::cout << "Time elapsed = " << double(timer)/CLOCKS_PER_SEC << '\n';
	printImage(M, Range(0,20,1), Range(0,20,1), Range(0,1,1));

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

void printImage(const Image& M, Range rows, Range columns, Range frames) {
	for (size_t k = frames.start(); k < std::min(frames.end(),M.size()); k += frames.inc()) {
		for (size_t i = rows.start(); i < std::min(rows.end(),M[k].size()); i += rows.inc()) {
			for (size_t j = columns.start(); j < std::min(columns.end(),M[k][i].size());
					j += columns.inc()) {
				std::cout << std::setw(4) << M[k][i][j];
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
}












