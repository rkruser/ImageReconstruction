#ifndef ALS_H
#define ALS_H
#include "defs.h"
#include "creation.h"
#include "submatrix.h"
#include "sor.h"
#include "column.h"

#include <vector>
#include <utility>

Matrix<double> ALS(Matrix<double>& M, int features, double lambda, int maxIter);

#endif
