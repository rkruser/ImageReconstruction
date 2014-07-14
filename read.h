#ifndef READ_H
#define READ_H
#include "defs.h"

RGB extractPixels(int);
void printImage(const Image&);
Image imProcess(const char**);
Image makeGrayScale(const Image& M);

#endif
