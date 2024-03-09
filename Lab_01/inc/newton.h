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

void init_newton_matrix_vectors(Matrix &matrix);
void compute_newton_cells_vectors(Matrix &matrix, int n);
void format_newton_cells_vectors(Matrix &matrix, int n);
void compute_newton_cells_values(Matrix &matrix, int n);
double interpolate_newton(const Matrix &newton_table, double x, int n);
void compute_table_interval_newton(const Matrix& input_matrix, Matrix& output_matrix, double x, int n);
void inverse_table_newton(Matrix &input_table, Matrix &inverse_table);
int interpolate_degrees_newton_ld(std::vector<LinkageDegree> vector_ld, double x, int rows_table, std::string filename);
int interpolate_degrees_newton_lp(std::vector<LinkagePoint> vector_lp, double x, int rows_table, std::string filename);
void interpolate_complete_table(Matrix &f_x, Matrix &g_x, Matrix &interpolated_g_x, int n);
void find_functions_difference(Matrix &f_x, Matrix &g_x, Matrix &differences);

#endif