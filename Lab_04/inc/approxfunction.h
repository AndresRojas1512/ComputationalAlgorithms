#ifndef APPROXFUNCTION_H
#define APPROXFUNCTION_H

#include <vector>
#include <utility>
#include "table.h"
#include "cmath"
#include "slae.h"

void compute_interval(std::pair<double, double> &interval, Table &table);

void compute_approxfunction(const std::vector<double> &system_solution, Table &table, const std::pair<double, double> &interval);

#endif