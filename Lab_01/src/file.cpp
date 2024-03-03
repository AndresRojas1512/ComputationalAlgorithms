#include "file.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

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

        // DEBUG
        // std::cout << "Row: " << row << " - x: " << x << ", y: " << y << std::endl;

        row++;
    }

    fclose(file);
    return SUCCESS;
}

file_error_t file_parse_hermite(Matrix &matrix, const std::string &filename)
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
        double x, y, ddx, ddx_2;
        char comma;
        
        if (!(ss >> x >> comma >> y >> comma >> ddx >> comma >> ddx_2))
        {
            fclose(file);
            return ERROR_PARSING;
        }

        matrix[row][0] = x;
        matrix[row][1] = y;
        matrix[row][2] = ddx;
        matrix[row][3] = ddx_2;

        // DEBUG
        // std::cout << "Row: " << row << " - x: " << x << ", y: " << y << std::endl;

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