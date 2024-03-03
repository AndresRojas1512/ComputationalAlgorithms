#include "file.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

// Assuming Matrix is a class that allows direct access via operator[]
// and assuming ERROR_CANNOT_OPEN and ERROR_PARSING are defined appropriately

file_error_t file_parse_newton(Matrix &matrix, const std::string &filename)
{
    FILE *file = fopen(filename.c_str(), "r");
    if (!file)
        return ERROR_CANNOT_OPEN;

    char buffer[BUFFER_SIZE];
    int row = 0;

    if (!fgets(buffer, sizeof(buffer), file))
    {
        fclose(file);
        return ERROR_PARSING;
    }

    while (fgets(buffer, sizeof(buffer), file))
    {
        std::stringstream ss(buffer);
        double x, y;
        char comma;
        
        if (!(ss >> x >> comma >> y))
        {
            fclose(file);
            return ERROR_PARSING;
        }

        matrix[row][0] = x;
        matrix[row][1] = y;

        std::cout << "Row: " << row << " - x: " << x << ", y: " << y << std::endl;

        row++;
    }

    fclose(file);
    return SUCCESS;
}


file_error_t file_count_lines(const std::string &filename, int &lines_count)
{
    lines_count = 0;
    FILE *file = fopen(filename.c_str(), "r");
    if (!file)
    {
        return ERROR_CANNOT_OPEN;
    }
    int lines = 0;
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file))
    {
        ++lines;
    }
    lines_count = lines;
    fclose(file);
    return SUCCESS;
}