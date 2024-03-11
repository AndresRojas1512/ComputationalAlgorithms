#ifndef IO_H
#define IO_H

#include <string>
#include "newton.h"
#include "hermite.h"

int input_data_stdinterp(std::string &filename, int &lines_count, int &columns_count, int &degree, int &points, double &x);

#endif