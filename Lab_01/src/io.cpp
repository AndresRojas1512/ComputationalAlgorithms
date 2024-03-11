#include "io.h"

int input_data_stdinterp(std::string &filename, int &lines_count, int &columns_count, int &degree, int &points, double &x)
{
    int exit_code = EXIT_SUCCESS;
    std::cout << "Enter file name: ";
    std::cin >> filename;
    exit_code = file_count_lines(filename, lines_count);
    if (exit_code)
        return exit_code;
    exit_code = file_count_columns(filename, columns_count);
    if (exit_code)
        return exit_code;
    return exit_code;
    std::cout << "Enter degree for Newton: ";
    std::cin >> degree;
    std::cout << "Enter N points for Hermite: ";
    std::cin >> points;
    std::cout << "Enter x: ";
    std::cin >> x;
    return exit_code;
}