#ifndef NEWTON_H
#define NEWTON_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>
#include "matrix.h"
#include "file.h"
#include "linkage.h"

#define X 0
#define Y 1

// Standard interpolation

void compute_interval_std(const Matrix& input_matrix, Matrix& output_matrix, double x, int n);

void newton_init_vectors(Matrix &matrix);

void newton_compute_vectors(Matrix &matrix, int n);

void newton_compute_values(Matrix &matrix, int n);

double newton_interpolate(const Matrix &newton_table, double x, int n);

// Inverse interpolation

void newton_inverse(Matrix &input_table, Matrix &inverse_table);

// Interpolation for many degrees

int newton_interpolate_degrees_ld(std::vector<LinkageDegree> vector_ld, double x, int rows_table, std::string filename);

int newton_interpolate_degrees_lp(std::vector<LinkagePoint> vector_lp, double x, int rows_table, std::string filename);

// Solve equation system

void newton_interpolate_complete_table(Matrix &f_x, Matrix &g_x, Matrix &interpolated_g_x, int n);

void newton_compute_functions_difference(Matrix &f_x, Matrix &g_x, Matrix &differences);

#endif
