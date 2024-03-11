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

// Standard Interpolation

void hermite_init_base_blocks(Matrix &matrix);

void hermite_init_values_blocks(Matrix &table_interval, Matrix &table_hermite, int data_count);

void hermite_init_vectors(Matrix &matrix);

void hermite_compute_vectors(Matrix &table_hermite);

void hermite_compute_derivatives(Matrix &matrix, Matrix &derivatives);

void hermite_compute_values(Matrix &matrix);

double hermite_interpolate(const Matrix &hermite_table, double x);

// Inverse Interpolation

void hermite_invert_derivatives(Matrix &table_derivatives, Matrix &table_derivatives_inverted);

// Compare Interpolations

int hermite_interpolate_points_ld(std::vector<LinkageDegree> &vector_ld, double x, int rows_table, int columns_count, std::string filename);

int hermite_interpolate_points_lp(std::vector<LinkagePoint> &vector_lp, double x, int rows_table, int columns_count, std::string filename);

// Compute Factorial

double compute_factorial(int n);

#endif