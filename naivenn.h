#ifndef NAIVE_NN_H
#define NAIVE_NN_H

#include "defs.h"

void naivenn(Image&, int);
 
struct spiralIterator {
	int x;
	int y;
	
	private:
	int dCount;
	int num;
	int numCount;
	bool modTwo;

	public:
	spiralIterator() : x(0), y(0), dCount(-2), 
		num(2), numCount(0), modTwo(false) {};
	spiralIterator(int a, int b) : x(a), y(b), dCount(-2), 
		num(2), numCount(0), modTwo(false) {};
	void inc() {
		if (dCount < 0) {
			if (dCount == -2) x++, dCount++;
			else  y++, dCount++;
		}
		else {
			if (numCount == num) {
				if (modTwo) num++;
				modTwo = !modTwo;
				numCount = 0;
				dCount = (dCount+1)%4;
			}

			numCount++;
			if (dCount == 0) x--;
			else if (dCount == 1) y--;
			else if (dCount == 2) x++;
			else y++;
		}
	}

};

#endif
