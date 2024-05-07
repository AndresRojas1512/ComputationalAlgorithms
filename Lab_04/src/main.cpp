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
    // 2D
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

    exit_code = file_count_rows(rows, "datasv_01.csv");
    if (exit_code)
        return exit_code;
    exit_code = file_count_columns(columns, "datasv_01.csv");
    if (exit_code)
        return exit_code;
    table = Table(rows, columns);
    exit_code = file_parse_1v(table, "datasv_01.csv");
    if (exit_code)
        return exit_code;
    points_1v_load(grid, table);
    std::cout << "Input degree: ";
    std::cin >> degree;
    nodes = degree + 1;
    Slae slae(nodes, nodes + 1);
    slae.compute_init_1v(grid);
    slae.lin_solve();
    slae.write_solution_csv("solution_2d.csv");

    // 3D
    // std::string filename;
    // int rows;
    // int columns;
    // int degree;
    // int nodes;
    // Table table;
    // Table table_approx_function;
    // std::pair<double, double> interval_x;
    // std::pair<double, double> interval_y;
    // std::vector<Point> grid;
    // int exit_code = EXIT_SUCCESS;

    // exit_code = file_count_rows(rows, "datadv_01.csv");
    // if (exit_code)
    //     return exit_code;
    // exit_code = file_count_columns(columns, "datadv_01.csv");
    // if (exit_code)
    //     return exit_code;
    // table = Table(rows, columns);
    // exit_code = file_parse_2v(table, "datadv_01.csv");
    // if (exit_code)
    //     return exit_code;
    // points_2v_load(grid, table);
    // std::cout << "Input degree: ";
    // std::cin >> degree;
    // nodes = ((degree + 1) * (degree + 2) / 2);
    // std::cout << "Equations: " << nodes << std::endl;
    // Slae slae(nodes, nodes + 1);
    // slae.compute_init_2v(grid, degree);
    // slae.lin_solve();
    // slae.write_solution_csv("solution_3d.csv");

    // ODE
    // std::vector<double> x_points = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
    // std::vector<Func> funcs_2degree = {f0, f1, f2};
    // std::vector<Func> coeffFuncs_2degree = {c0, c1, c2};

    // std::vector<Func> funcs_3degree = {f0, f1, f2, f3};
    // std::vector<Func> coeffFuncs_3degree = {c0, c1, c2, f3};

    // std::vector<Func> funcs_4degree = {f0, f1, f2, f3, f4};
    // std::vector<Func> coeffFuncs_4degree = {c0, c1, c2, c3, c4};

    // Slae slae_ode_2degree(2, 2 + 1);
    // Slae slae_ode_3degree(3, 3 + 1);
    // Slae slae_ode_4degree(4, 4 + 1);

    // GetApproximateODE(slae_ode_2degree, x_points, 2, funcs_2degree, coeffFuncs_2degree);
    // slae_ode_2degree.lin_solve();
    // std::cout << "ODE system 2 solution: " << std::endl;
    // std::cout << slae_ode_2degree.get_system_solution() << std::endl;

    // GetApproximateODE(slae_ode_3degree, x_points, 3, funcs_3degree, coeffFuncs_3degree);
    // slae_ode_3degree.lin_solve();
    // std::cout << "ODE system 3 solution: " << std::endl;
    // std::cout << slae_ode_3degree.get_system_solution() << std::endl;

    // GetApproximateODE(slae_ode_4degree, x_points, 4, funcs_4degree, coeffFuncs_4degree);
    // slae_ode_4degree.lin_solve();
    // std::cout << "ODE system 4 solution: " << std::endl;
    // std::cout << slae_ode_4degree.get_system_solution() << std::endl;

    return 0;
}