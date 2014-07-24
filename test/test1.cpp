#include "naivenn.h"

#include <iostream>
using namespace std;

int main() {
	spiralIterator iter;

	for (int i = 0; i < 30; i++) {
		cout << iter.x << ' ' << iter.y << '\n';
		iter.inc();
	}

	cerr << "Stuff! Yeah!\n";


	return 0;
}
