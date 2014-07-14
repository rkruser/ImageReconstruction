#ifndef DEFS_H
#define DEFS_H
#include <cstdlib>
#include <vector>
#include <limits>
using std::size_t; //The only reason for including cstdlib

#define NAN std::numeric_limits<double>::quiet_NaN();

typedef std::vector<std::vector<std::vector<double>>> Image;
typedef std::vector<std::vector<double>> Row;
typedef std::vector<double> Column;

struct RGB {
	unsigned int r : 8;
	unsigned int g : 8;
	unsigned int b : 8;
};

class too_many_chars_per_pixel {};
class not_color_format {};


#endif
