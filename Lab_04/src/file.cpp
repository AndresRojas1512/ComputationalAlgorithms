#include "file.h"

file_error_t file_parse_1v(Table &table, const std::string &filename)
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
        double x, y, weight;
        char comma;
        
        if (!(ss >> x >> comma >> y >> comma >> weight))
        {
            fclose(file);
            return ERROR_PARSING;
        }
        table[row][0] = x;
        table[row][1] = y;
        table[row][2] = weight;
        row++;
    }
    fclose(file);
    return SUCCESS;
}

file_error_t file_parse_2v(Table &table, const std::string &filename)
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
        double x, y, z, weight;
        char comma;
        
        if (!(ss >> x >> comma >> y >> comma >> z >> comma >> weight))
        {
            fclose(file);
            return ERROR_PARSING;
        }
        table[row][0] = x;
        table[row][1] = y;
        table[row][2] = z;
        table[row][2] = weight;
        row++;
    }
    fclose(file);
    return SUCCESS;
}

file_error_t file_count_rows(int &lines_count, const std::string &filename)
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
    lines_count = lines - 1;
    fclose(file);
    return SUCCESS;
}

file_error_t file_count_columns(int &columns_count, const std::string &filename)
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

