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

void compute_interval_std(const Matrix& input_matrix, Matrix& output_matrix, double x, int n);

void newton_init_vectors(Matrix &matrix);

void newton_compute_vectors(Matrix &matrix, int n);

void newton_compute_values(Matrix &matrix, int n);

double newton_interpolate(const Matrix &newton_table, double x, int n);

double newton_compute_dxx(const Matrix &newton_table, double x);

void newton_init_from_vectors(Matrix &newton_table, std::vector<double> &x_vals, std::vector<double> &y_vals);

#endif