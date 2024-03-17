#ifndef SPLINE_H
#define SPLINE_H

#include <iostream>
#include <vector>
#include "matrix.h"

#define X 0
#define Y 1

#define A_COL 0
#define B_COL 1
#define C_COL 2
#define D_COL 3

int spline_compute_steps(std::vector<double> &steps, Matrix &table_src, int splines_n);

void vector_print(const std::vector<double> &vector);

#endif