#include <iostream>
#include <string>
#include "file.h"
#include "matrix.h"
#include "newton.h"
#include "hermite.h"

int main(void)
{
    std::string filename;
    int n;

    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::cout << "Enter n: ";
    std::cin >> n;

    int lines_count;
    int columns_count;
    int exit_code = EXIT_SUCCESS;

    exit_code = file_count_lines(filename, lines_count);
    if (exit_code)
        return exit_code;
    std::cout << "Lines: " << lines_count << std::endl;

    exit_code = file_count_columns(filename, columns_count);
    if (exit_code)
        return exit_code;
    std::cout << "Columns: " << columns_count << std::endl;

    // HERMITE
    Matrix hermite_table(n, n + 1);
    Matrix derivative_table(n, columns_count - 2);
    int data_count = columns_count - 1;

    exit_code = file_parse_hermite(hermite_table, filename, data_count);
    if (exit_code)
        return exit_code;
    
    exit_code = file_parse_derivatives(derivative_table, filename);
    if (exit_code)
        return exit_code;

    init_hermite_matrix_vectors_blocks(hermite_table, data_count);
    compute_hermite_cells_vectors(hermite_table, n);
    compute_hermite_derivatives(hermite_table, derivative_table, n);
    compute_hermite_cells_values(hermite_table, n);
    print_hermite_polynomial(hermite_table, n);


    // NEWTON
    // Matrix newton_table(lines_count - 1, n + 2);
    // exit_code = file_parse_newton(newton_table, filename);
    // if (exit_code)
    //     return exit_code;

    // init_newton_matrix_vectors(newton_table);
    // compute_newton_cells_vectors(newton_table, n);
    // compute_newton_cells_values(newton_table, n);
    // double result = interpolate_newton(newton_table, -0.75, n);
    // std::cout << "Result: " << result << std::endl;
    // print_newton_polynomial(newton_table, n);
    return 0;
}