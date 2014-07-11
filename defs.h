#ifndef DEFS_H
#define DEFS_H
#include <cstdlib>
using std::size_t; //The only reason for including the library

struct RGB {
	int r : 8;
	int g : 8;
	int b : 8;
};

class Range {
	public:
		class bad_range {};
		Range(size_t s, size_t e, size_t i) {
			if (i == 0) {
				bad_range e;
				throw e;
			} 
			startVal = s;
			endVal = e;
			incVal = i;
		}
		size_t start() { return startVal; }
		size_t end() { return endVal; }
		size_t inc() { return incVal; }

	private:
		size_t startVal;
		size_t endVal;
		size_t incVal;
};

class too_many_chars_per_pixel {};
class not_color_format {};


#endif
