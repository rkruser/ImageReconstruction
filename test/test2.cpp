#include "defs.h"

#include <iostream>

int main() {
	Matrix<double> m(2,2,1);
	std::cout << "m:\n" << m;
	Matrix<double> n(2,2,3);
	std::cout << "n:\n" << n;
	std::cout << "m+n:\n" << m+n;
	m = m+n;
	std::cout << "m = m+n:\n" << m;
	Matrix<int> y(2,3,1);
	Matrix<int> j(3,2,5);
	std::cout << "y*j\n" << y*j;





	return 0;
}
