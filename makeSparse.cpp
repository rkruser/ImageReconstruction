#include "makeSparse.h"
#include "defs.h"

#include <cstdlib>
#include <vector>

class PoutOfRange{};

// Set 100*P percent of the pixels of M as nan
void makeSparse(Image& M, double P) {
	if (P < 0 or P > 1) {
		PoutOfRange e;
		throw e;
	}
	int numRemoved;
	if (P > 0.5) {
		numRemoved = (1-P)*M.size;
	}
	else {
		numRemoved = P*M.size;
	}

	std::vector<bool> toChange(M.size, false);
	for (int i = 1; i <= numRemoved; ++i) {
		int index = std::rand()%M.size;
		while (toChange[index]) {
			index = std::rand()%M.size;
		}
		toChange[index] = true;
	}

	if (P > 0.5) {
		toChange.flip();
	}

	for (size_t i = 0; i < M.size; ++i) {
		if (toChange[i]) {
			M(i) = NAN;
		}
	}
}
