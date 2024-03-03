#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include "matrix.h"

#define BUFFER_SIZE 1024

typedef enum error
{
    SUCCESS = 0,
    ERROR_CANNOT_OPEN,
    ERROR_DAMAGED,
    ERROR_PARSING
} file_error_t;

file_error_t file_parse_newton(Matrix &matrix, const std::string &filename);
file_error_t file_count_lines(const std::string &filename, int &lines_count);

#endif