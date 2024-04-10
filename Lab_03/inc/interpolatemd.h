#ifndef INTERPOLATEMD_H
#define INTERPOLATEMD_H

#include "newton.h"
#include "spline.h"
#include "table.h"

// Newton

double newton_linear(double x, int nx, std::vector<double> &x_vals, std::vector<double> &y_vals);

double newton_bilinear(double x, double y, int nx, int ny, Layer &layer);

double newton_trilinear(double x, double y, double z, int nx, int ny, int nz, Table &table);

// Spline

double spline_linear(double x, std::vector<double> &x_vals, std::vector<double> &y_vals);

double spline_bilinear(double x, double y, Layer &layer);

double spline_trilinear(double x, double y, double z, Table &table);

// Mixed

double mixed_bilinear(double x, double y, int nx, int ny, Layer &layer);

double mixed_trilinear(double x, double y, double z, int nx, int ny, int nz, Table &table);

// Compute regular grid configurarion

void compute_vector_configuration(std::vector<double> &in_values, std::vector<double> &out_values, std::vector<int> &out_indices,double x, int n);

void compute_table_configuration(Table &input_table, Table &output_table, double x, double y, double z, int nx, int ny, int nz);

#endif