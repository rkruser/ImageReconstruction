#include "naivenn.h"
#include "defs.h"

#include <cmath>
#include <iostream> //For debugging

/*******************************************************************************
Note! This implementation works differently than the Matlab
interpretation! The difference is the order in which surrounding pixels are 
visited. 
*******************************************************************************/

//Iterates over every pixel in the image
//If the pixel is a nan, then set it equal to the average of the nearest kPixels
void naivenn(Image& M, int kPixels) {
	for (size_t k = 0; k < M.frames; ++k) {
		for (size_t i = 0; i < M.rows; ++i) {
			for (size_t j = 0; j < M.cols; ++j) {
				if (std::isnan(M(i,j,k))) {
					spiralIterator iter(i,j);
					int count = 0;
					double accumulator = 0;
					while (count < kPixels) {
						iter.inc();
						if (iter.x < 0 or iter.x >= M.rows
								or iter.y < 0 or iter.y >= M.cols) {
							continue;
						}
						if (!std::isnan(M(iter.x,iter.y,k))) {
							accumulator += M(iter.x,iter.y,k);
							count++;
						}
					}
					M(i,j,k) = std::round(accumulator / kPixels);
				}
			}
		}
	}

}
