/*
 * beach
 * boats
 * einstein
 * stopSign2 (stopSign_)
*/
#define IMAGE einstein
#include "einstein.xpm"

#include "defs.h"
#include "read.h"

#include <iostream>
#include <stdexcept>
#include <ctime>

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
	
	// Problem: for some reason, the online xpm file converter only retains 256 colors,
	// diminishing image quality
	printImage(M);

	return 0;
}
