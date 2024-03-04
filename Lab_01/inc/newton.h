#ifndef NEWTON_H
#define NEWTON_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>
#include "matrix.h"

#define X 0
#define Y 1

void init_matrix_vectors(Matrix &matrix);
void compute_cells_vectors(Matrix &matrix, int n);
void format_cells_vectors(Matrix &matrix, int n);

#endif