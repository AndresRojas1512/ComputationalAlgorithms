#include <iostream>
#include <string>
#include "file.h"
#include "matrix.h"
#include "newton.h"

int main(void)
{
    std::string filename;
    int n;

    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::cout << "Enter n: ";
    std::cin >> n;

    int lines_count;
    int exit_code = file_count_lines(filename, lines_count);
    if (exit_code)
        return exit_code;

    Matrix newton_table(lines_count - 1, n + 2);
    // Matrix hermite_table(lines_count - 1, n + 4);
    
    exit_code = file_parse_newton(newton_table, filename);
    if (exit_code)
        return exit_code;
    std::cout << "Newton:" << std::endl;
    newton_table.print();
    
    // exit_code = file_parse_hermite(hermite_table, filename);
    // if (exit_code)
    //     return exit_code;
    // std::cout << "Hermite:" << std::endl;
    // hermite_table.print();

    // Divided differences
    std::cout << "Divided differences:" << std::endl; 
    compute_divided_differences(newton_table, n);
    newton_table.print();

    return 0;
}