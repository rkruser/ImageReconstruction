#ifndef READ_H
#define READ_H
#include "defs.h"
#include <ostream>

RGB extractPixels(int);
void printImage(std::ostream& out, const Image&);
Image imProcess(const char**, bool);
Image makeGrayScale(const Image& M);

#endif
