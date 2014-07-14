#include "makeSparse.h"
#include "defs.h"

#include <cstdlib>
#include <cmath>

class PoutOfRange{};

// Requires that M actually contain pixels, so size can be read
void makeSparse(Image& M, double P) {
	if (P < 0 or P > 1) {
		PoutOfRange e;
		throw e;
	}
	bool flip = false;
	if (P > 0.5) {
		flip = true;
		P = 1-P;
	}

	int frames = M.size();
	int rows = M[0].size();
	int cols = M[0][0].size();
	int numPixels = frames*rows*cols;
	int framesize = rows*cols;
	int numRemoved = std::round(P*numPixels);

	for (int i = 1; i <= numRemoved; ++i) {
		int index = std::rand()%numPixels; //Which pixel
		int index1 = index/framesize; //Which frame
		int index2 = (index % framesize) / cols; //Which row
		int index3 = (index%framesize)%cols; //Which column
		while (std::isnan(M[index1][index2][index3])) {
			index = std::rand()%numPixels; 
			index1 = index/framesize; 
            index2 = (index % framesize) / cols;
            index3 = (index%framesize)%cols; 
		}
		M[index1][index2][index3] = NAN;
	}
	// Needs to handle flip case


}
