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
    std::cout << "Lines: " << lines_count << std::endl;

    Matrix newton_table(lines_count - 1, n + 2);
    
    exit_code = file_parse_newton(newton_table, filename);
    if (exit_code)
        return exit_code;
    std::cout << "Newton:" << std::endl;
    // newton_table.print_cell();
    // newton_table.print_cell_value();
    init_matrix_vectors(newton_table);
    newton_table.print_cell();

    std::cout << "Div Diff:" << std::endl;
    compute_cells_vectors(newton_table, n);
    format_cells_vectors(newton_table, n);
    newton_table.print_cell_vector();

    return 0;
}