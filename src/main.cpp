/*
 * beach
 * boats
 * einstein
 * stopSign2 (stopSign_)
*/
#define IMAGE beach
#include "beach.xpm"
#define BLACK_AND_WHITE true

#include "defs.h"
#include "read.h"
#include "naivenn.h"
#include "makeSparse.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <ctime>

int main(){
	std::clock_t timer;
	timer = std::clock();
	Image M;
	try {
		M = imProcess(IMAGE, BLACK_AND_WHITE);
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
	
	// Problem: for some reason, the online xpm file converter only retains 256 colors,
	// diminishing image quality for color images
	Image sparseImage(M);
	makeSparse(sparseImage.R, 0.7);
	if (sparseImage.color) {
		makeSparse(sparseImage.G, 0.7);
		makeSparse(sparseImage.B, 0.7);
	}

	Image naiveRepair(sparseImage);
	naivenn(naiveRepair.R, 2);
	if (naiveRepair.color) {
		naivenn(naiveRepair.G, 2);
		naivenn(naiveRepair.B, 2);
	}

	std::ofstream f1, f2, f3;
	f1.open("./output/original.txt");
	f2.open("./output/sparse.txt");
	f3.open("./output/naiveRecon.txt");
	printImage(f1, M);
	printImage(f2, sparseImage);
	printImage(f3, naiveRepair);
	f1.close();
	f2.close();
	f3.close();
	timer = std::clock()-timer;
	std::cout << "Time elapsed: " << double(timer)/CLOCKS_PER_SEC << '\n';
	

	return 0;
}
