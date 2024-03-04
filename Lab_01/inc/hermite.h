#ifndef HERMITE_H
#define HERMITE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>
#include "matrix.h"

#define X 0
#define Y 1

void init_hermite_matrix_vectors_blocks(Matrix &matrix, int row_blocks, int data_count);

#endif