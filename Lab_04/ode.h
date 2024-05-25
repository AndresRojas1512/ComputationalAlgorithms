#ifndef ODE_H
#define ODE_H

#include <iostream>
#include <cmath>
#include <numbers>
#include <functional>
#include <boost/math/special_functions/erf.hpp>
#include "polynomial.h"
#include "slae.h"

using Func = std::function<double(double)>;

double ODESolution(double x);

void GetApproximateODE(Slae &slae, const std::vector<double>& xs, int n, const std::vector<Func>& funcs, const std::vector<Func>& coeffFuncs);

#endif
