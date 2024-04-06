#ifndef INTERPOLATEMD_H
#define INTERPOLATEMD_H

#include "newton.h"
#include "spline.h"
#include "table.h"

double newton_linear(double x, int nx, std::vector<double> &x_vals, std::vector<double> &y_vals);

double newton_bilinear(double x, double y, int nx, int ny, Layer &layer);

double newton_trilinear(double x, double y, double z, int nx, int ny, int nz, Table &table);

double spline_linear(double x, std::vector<double> &x_vals, std::vector<double> &y_vals);

double spline_bilinear(double x, double y, Layer &layer);

double spline_trilinear(double x, double y, double z, Table &table);

#endif