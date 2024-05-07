#ifndef APPROXFUNCTION_H
#define APPROXFUNCTION_H

#include <vector>
#include <utility>
#include "table.h"
#include "cmath"
#include "slae.h"

void compute_interval_x(std::pair<double, double> &interval, Table &table);

void compute_interval_y(std::pair<double, double> &interval, Table &table);

void compute_approxfunction_2d(const std::vector<double> &system_solution, Table &table, const std::pair<double, double> &interval, int x_steps);

void compute_approxfunction_3d(const std::vector<double> &system_solution, Table &table, const std::pair<double, double> &x_interval, const std::pair<double, double> &y_interval, int x_steps, int y_steps);


#endif