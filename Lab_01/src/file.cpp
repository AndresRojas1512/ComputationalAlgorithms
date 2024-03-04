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
        matrix[row][0].value = x;
        matrix[row][1].value = y;
        row++;
    }
    fclose(file);
    return SUCCESS;
}

file_error_t file_parse_hermite(Matrix &matrix, const std::string &filename, int data_count)
{
    FILE *file = fopen(filename.c_str(), "r");
    if (!file) {
        return ERROR_CANNOT_OPEN;
    }

    char buffer[BUFFER_SIZE];

    if (!fgets(buffer, sizeof(buffer), file))
    {
        fclose(file);
        return ERROR_PARSING;
    }

    int currentMatrixRow = 0;

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

        for (int i = 0; i < data_count; ++i)
        {
            if (currentMatrixRow >= matrix.get_rows())
            {
                fclose(file);
                return ERROR_PARSING;
            }
            matrix[currentMatrixRow][0].value = x;
            matrix[currentMatrixRow][1].value = y;
            ++currentMatrixRow;
        }
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

file_error_t file_count_columns(const std::string &filename, int &columns_count)
{
    FILE *file = fopen(filename.c_str(), "r");
    if (!file)
    {
        return ERROR_CANNOT_OPEN;
    }

    char buffer[BUFFER_SIZE];
    if (!fgets(buffer, sizeof(buffer), file))
    {
        fclose(file);
        return ERROR_PARSING;
    }

    int commas = 0;
    for (char *p = buffer; *p; p++)
    {
        if (*p == ',') {
            commas++;
        }
    }

    columns_count = commas + 1;

    fclose(file);
    return SUCCESS;
}