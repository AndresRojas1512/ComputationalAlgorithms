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

// Base matrix
void init_base_matrix_blocks(Matrix &matrix);

void init_hermite_table(Matrix &table_interval, Matrix &table_hermite, int data_count);
void init_hermite_matrix_vectors(Matrix &matrix);
void compute_hermite_cells_vectors(Matrix &table_hermite);
void compute_hermite_derivatives(Matrix &matrix, Matrix &derivatives);
void compute_hermite_cells_values(Matrix &matrix);
void print_hermite_polynomial(const Matrix &hermite_table, int nodes);
double interpolate_hermite(const Matrix &hermite_table, double x);
double compute_factorial(int n);

#endif