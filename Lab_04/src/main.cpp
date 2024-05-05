#include "table.h"
#include "point.h"
#include "file.h"
#include "polynomial.h"
#include "slae.h"
#include <iostream>
#include <string>

int main(void)
{
    std::string filename;
    int rows;
    int columns;
    int degree;
    int nodes;
    Table table;
    std::vector<Point> grid;
    int exit_code = EXIT_SUCCESS;

    exit_code = file_count_rows(rows, "data_1v.csv");
    if (exit_code)
        return exit_code;
    exit_code = file_count_columns(columns, "data_1v.csv");
    if (exit_code)
        return exit_code;
    table = Table(rows, columns);
    exit_code = file_parse_1v(table, "data_1v.csv");
    if (exit_code)
        return exit_code;
    points_1v_load(grid, table);

    std::cout << "Input degree: ";
    std::cin >> degree;
    nodes = degree + 1;

    Slae slae(nodes, nodes + 1);
    slae.compute_init(grid);
    std::cout << slae;
    std::cout << "Row echelon:" << std::endl;
    slae.row_echelon();
    std::cout << slae;
    return 0;
}