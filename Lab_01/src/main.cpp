#include <iostream>
#include <string>
#include "file.h"
#include "matrix.h"
#include "newton.h"
#include "hermite.h"

int main(void)
{
    std::string filename;
    // int n;
    double x;

    std::cout << "Enter the filename: ";
    std::cin >> filename;

    // std::cout << "Enter n: ";
    // std::cin >> n;

    std::cout << "Enter x: ";
    std::cin >> x;

    int lines_count;
    int columns_count;
    int exit_code = EXIT_SUCCESS;

    exit_code = file_count_lines(filename, lines_count);
    if (exit_code)
        return exit_code;

    exit_code = file_count_columns(filename, columns_count);
    if (exit_code)
        return exit_code;
    
    // Standard procedure object creation
    // Matrix newton_table(lines_count - 1, n + 2);
    // Matrix newton_table_inversed(lines_count - 1, lines_count);
    // Matrix newton_table_interval(n + 1, n + 2);

    // Root finding procedure
    Matrix newton_table(lines_count - 1, lines_count);
    Matrix newton_table_inversed(lines_count - 1, lines_count);

    exit_code = file_parse_newton(newton_table, filename);
    if (exit_code)
        return exit_code;

    // Inverse table
    std::cout << "Inversed table:" << std::endl;
    inverse_table_newton(newton_table, newton_table_inversed);
    newton_table_inversed.print_cell_value();
    newton_table_inversed.sort_by_first_column();
    std::cout << "Sorted inversed table:" << std::endl;
    // newton_table_inversed.print_cell_value();
    // Interval table
    // std::cout << "Filtered table:" << std::endl;
    // find_interval_containing_x_newton(newton_table, newton_table_interval, x, n);

    // Divided differences table
    // init_newton_matrix_vectors(newton_table_interval);
    // compute_newton_cells_vectors(newton_table_interval, n);
    // compute_newton_cells_values(newton_table_interval, n);
    // double result = interpolate_newton(newton_table_interval, x, n);
    // std::cout << "Result: " << result << std::endl;

    // Evaluate roots
    init_newton_matrix_vectors(newton_table_inversed);
    compute_newton_cells_vectors(newton_table_inversed, lines_count - 2);
    compute_newton_cells_values(newton_table_inversed, lines_count - 2);
    // std::cout << "Cell value:" << std::endl;
    // newton_table_inversed.print_cell_value();
    double result = interpolate_newton(newton_table_inversed, x, lines_count - 2);
    std::cout << "Result: " << result << std::endl;

    // HERMITE
    // Matrix hermite_table(n, n + 1);
    // Matrix derivative_table(n, columns_count - 2);
    // int data_count = columns_count - 1;

    // exit_code = file_parse_hermite(hermite_table, filename, data_count);
    // if (exit_code)
    //     return exit_code;
    
    // exit_code = file_parse_derivatives(derivative_table, filename);
    // if (exit_code)
    //     return exit_code;

    // init_hermite_matrix_vectors_blocks(hermite_table, data_count);
    // compute_hermite_cells_vectors(hermite_table, n);
    // compute_hermite_derivatives(hermite_table, derivative_table, n);
    // compute_hermite_cells_values(hermite_table, n);
    // hermite_table.print_cell_value();
    return 0;
}