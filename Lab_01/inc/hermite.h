#ifndef HERMITE_H
#define HERMITE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include "matrix.h"
#include "linkage.h"
#include "file.h"
#include "newton.h"

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
int interpolate_points_hermite_ld(std::vector<LinkageDegree> &vector_ld, double x, int rows_table, int columns_count, std::string filename);
int interpolate_points_hermite_lp(std::vector<LinkagePoint> &vector_lp, double x, int rows_table, int columns_count, std::string filename);

void invert_table_derivatives(Matrix &table_derivatives, Matrix &table_derivatives_inverted);

#endif