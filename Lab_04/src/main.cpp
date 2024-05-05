#include <iostream>
#include <string>
#include <utility>
#include "table.h"
#include "point.h"
#include "file.h"
#include "polynomial.h"
#include "slae.h"
#include "approxfunction.h"

int main(void)
{
    std::string filename;
    int rows;
    int columns;
    int degree;
    int nodes;
    Table table;
    Table table_approx_function;
    std::pair<double, double> interval;
    std::vector<Point> grid;
    int exit_code = EXIT_SUCCESS;

    exit_code = file_count_rows(rows, "datasv_02.csv");
    if (exit_code)
        return exit_code;
    exit_code = file_count_columns(columns, "datasv_02.csv");
    if (exit_code)
        return exit_code;
    table = Table(rows, columns);
    exit_code = file_parse_1v(table, "datasv_02.csv");
    if (exit_code)
        return exit_code;
    points_1v_load(grid, table);

    std::cout << "Input degree: ";
    std::cin >> degree;
    nodes = degree + 1;

    Slae slae(nodes, nodes + 1);
    slae.compute_init(grid);
    slae.lin_solve();
    compute_interval(interval, table);
    std::cout << "[ " << interval.first << ", " << interval.second << " ]" << std::endl;
    compute_approxfunction(slae.get_system_solution(), table_approx_function, interval);
    table_approx_function.writeXY("aproxfunction.csv");
    return 0;
}