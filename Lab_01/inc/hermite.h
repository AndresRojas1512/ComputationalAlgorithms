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

void init_hermite_matrix_vectors_blocks(Matrix &matrix, int data_count);
void compute_hermite_cells_vectors(Matrix &matrix, int n);
void compute_hermite_derivatives(Matrix &matrix, Matrix &derivatives, int n);
void compute_hermite_cells_values(Matrix &matrix, int n);
double compute_factorial(int n);

#endif