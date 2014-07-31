#include "makeSparse.h"
#include "defs.h"

#include <cstdlib>
#include <vector>

class PoutOfRange{};

// Set 100*P percent of the pixels of M as nan
void makeSparse(Matrix<double>& M, double P) {
	if (P < 0 or P > 1) {
		PoutOfRange e;
		throw e;
	}
	int numRemoved;
	if (P > 0.5) {
		numRemoved = (1-P)*M.numElts();
	}
	else {
		numRemoved = P*M.numElts();
	}

	std::vector<bool> toChange(M.numElts(), false);
	for (int i = 1; i <= numRemoved; ++i) {
		int index = std::rand()%M.numElts();
		while (toChange[index]) {
			index = std::rand()%M.numElts();
		}
		toChange[index] = true;
	}

	if (P > 0.5) {
		toChange.flip();
	}

	for (size_t i = 0; i < M.numElts(); ++i) {
		if (toChange[i]) {
			M(i) = NAN;
		}
	}
}
