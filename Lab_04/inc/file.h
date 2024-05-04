#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "table.h"

#define BUFFER_SIZE 256

typedef enum error
{
    SUCCESS = 0,
    ERROR_CANNOT_OPEN,
    ERROR_DAMAGED,
    ERROR_PARSING
} file_error_t;

file_error_t file_parse_1v(Table &table, const std::string &filename);

file_error_t file_parse_2v(Table &table, const std::string &filename);

file_error_t file_count_rows(int &lines_count, const std::string &filename);

file_error_t file_count_columns(int &columns_count, const std::string &filename);

#endif