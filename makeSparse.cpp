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

	int numRemoved = std::round(P*M.size);

	for (int i = 1; i <= numRemoved; ++i) {
		int index = std::rand()%M.size; //Which pixel
		while (std::isnan(M(index))) {
			index = std::rand()%M.size;
		}
		M(index) = NAN;
	}
	// Needs to handle flip case


}
