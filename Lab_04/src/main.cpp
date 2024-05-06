#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <cmath>
#include "table.h"
#include "point.h"
#include "file.h"
#include "polynomial.h"
#include "slae.h"
#include "approxfunction.h"
#include "ode.h"

double f0(double x) { return 1 - x; }
double f1(double x) { return x * (1 - x); }
double f2(double x) { return std::pow(x, 2) * (1 - x); }
double f3(double x) { return std::pow(x, 3) * (1 - x); }
double f4(double x) { return std::pow(x, 4) * (1 - x); }

double c0(double x) { return 1 - (4 * x); }
double c1(double x) { return -2 + 2 * x - 3 * std::pow(x, 2); }
double c2(double x) { return 2 - 6 * x + 3 * std::pow(x, 2) - 4 * std::pow(x, 3); }
double c3(double x) { return 6 * x - 12 * std::pow(x, 2) + 4 * std::pow(x, 3) - 5 *std::pow(x, 4); }
double c4(double x) { return 12 * std::pow(x, 2) - 20 * std::pow(x, 3) + 5 * std::pow(x, 4) + 6 * std::pow(x, 5); }

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

    exit_code = file_count_rows(rows, "datadv_01.csv");
    if (exit_code)
        return exit_code;
    exit_code = file_count_columns(columns, "datadv_01.csv");
    if (exit_code)
        return exit_code;
    table = Table(rows, columns);
    // exit_code = file_parse_1v(table, "datadv_01.csv"); // 1v
    exit_code = file_parse_2v(table, "datadv_01.csv");
    if (exit_code)
        return exit_code;
    // points_1v_load(grid, table); // 1v
    points_2v_load(grid, table); // 2v
    std::cout << "Input degree: ";
    std::cin >> degree;
    nodes = ((degree + 1) * (degree + 2) / 2);
    std::cout << "Equations: " << nodes << std::endl;
    Slae slae(nodes, nodes + 1);
    slae.compute_init_2v(grid, degree);
    slae.lin_solve();
    std::cout << "Solution:" << std::endl;
    std::cout << slae.get_system_solution() << std::endl;

    // ODE
    int degree_ode = 2;
    std::vector<double> x_points = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
    std::vector<Func> funcs = {f0, f1, f2};
    std::vector<Func> coeffFuncs = {c0, c1, c2};

    Slae slae_ode(degree_ode, degree_ode + 1);
    GetApproximateODE(slae_ode, x_points, degree_ode, funcs, coeffFuncs);
    std::cout << slae_ode;
    slae_ode.lin_solve();
    // compute_interval(interval, table);
    // // std::cout << "[ " << interval.first << ", " << interval.second << " ]" << std::endl;
    // compute_approxfunction(slae.get_system_solution(), table_approx_function, interval);
    // table_approx_function.writeXY("aproxfunction.csv");

    return 0;
}