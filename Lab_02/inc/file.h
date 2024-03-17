#ifndef FILE_H
#define FILE_H

#include <iostream>
#include "matrix.h"

#define BUFFER_SIZE 256
#define COLUMNS_COUNT 2

typedef enum error
{
    SUCCESS = 0,
    ERROR_CANNOT_OPEN,
    ERROR_DAMAGED,
    ERROR_PARSING
} file_error_t;

file_error_t file_parse_std(Matrix &matrix, const std::string &filename);

file_error_t file_count_lines(const std::string &filename, int &lines_count);

file_error_t file_count_columns(const std::string &filename, int &columns_count);

#endif