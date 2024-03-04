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
    int data_count = columns_count - 1;
    int row_count = (lines_count - 1) * data_count;
    int row_blocks = lines_count - 1;

    Matrix hermite_table(row_count, data_count);
    exit_code = file_parse_hermite(hermite_table, filename, data_count);
    if (exit_code)
        return exit_code;
    std::cout << "Hermite: " << std::endl;
    hermite_table.print_cell_value();
    init_hermite_matrix_vectors_blocks(hermite_table, row_blocks, data_count);
    hermite_table.print_cell_block();
    // NEWTON
    // Matrix newton_table(lines_count - 1, n + 2);
    // exit_code = file_parse_newton(newton_table, filename);
    // if (exit_code)
    //     return exit_code;
    // std::cout << "Newton:" << std::endl;
    // init_newton_matrix_vectors(newton_table);
    // newton_table.print_cell();

    // compute_newton_cells_vectors(newton_table, n);
    // std::cout << "Cells vector:" << std::endl;
    // newton_table.print_cell_vector();

    // compute_newton_cells_values(newton_table, n);
    // std::cout << "Cells values:" << std::endl;
    // newton_table.print_cell_value();

    return 0;
}