#include <iostream>
#include "matrix.h"
#include "file.h"
#include "point.h"
#include "spline.h"
#include "newton.h"
#include "table.h"
#include "interpolatemd.h"
#include "ui.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    int choice;
    do
    {
        menu();
        if (input_choice(choice))
            puts("\nError. Input");
        else
        {
            switch (choice)
            {
                case 11:
                {
                    std::string filename;
                    std::cout << "Enter the file name: ";
                    std::cin >> filename;
                    Table table;
                    parseCSVToTable(filename, table);
                    table.init_zs();
                    double result_newton = newton_trilinear(1.5, 1.5, 1.5, 1, 1, 1, table);
                    double result_spline = spline_trilinear(1.5, 1.5, 1.5, table);
                    std::cout << "Result Newton: " << result_newton << std::endl;
                    std::cout << "Result Spline: " << result_spline << std::endl;
                    break;
                }
                case 21: // fi''(x0) = 0 | fi''(xN) = 0 (Lecture)
                {
                    std::string filename;
                    int lines_count;
                    int columns_count;
                    int spline_index_x0;
                    int spline_index_xN;
                    // Input
                    std::cout << "Enter the file name: ";
                    std::cin >> filename;
                    // Validate - Get data
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    // Prepare data - Create Objects
                    int rows_table = lines_count - 1;
                    Matrix table_src(rows_table, COLUMNS_COUNT);
                    std::vector<Spline> splines;
                    // Parse file
                    exit_code = file_parse_std(table_src, filename);
                    if (exit_code)
                        return exit_code;
                    // Get arguments x0 and xN
                    double x0 = table_src[0][0].value;
                    double xN = table_src[table_src.get_rows() - 1][0].value;
                    // Spline
                    splines_init_vector(splines, table_src);
                    splines_compute_h(splines);
                    splines_compute_a(splines);
                    splines_compute_xi(splines, 0);
                    splines_compute_eta(splines, 0);
                    splines_compute_c(splines, 0, 0);
                    splines_compute_b(splines);
                    splines_compute_bn(splines);
                    splines_compute_d(splines);
                    splines_compute_dn(splines);

                    exit_code = spline_find(splines, x0, spline_index_x0);
                    if (exit_code)
                        return exit_code;
                    exit_code = spline_find(splines, xN, spline_index_xN);
                    if (exit_code)
                        return exit_code;
                    
                    double y0 = splines[spline_index_x0].spline_interpolate(x0);
                    double yN = splines[spline_index_xN].spline_interpolate(xN);

                    std::cout << "y0: " << y0 << std::endl;
                    std::cout << "yN: " << yN << std::endl;
                    break;
                }
                case 22: // fi''(x0) = P''(x0) | fi''(xN) = 0
                {
                    std::string filename;
                    int lines_count;
                    int columns_count;
                    int spline_index_x0;
                    int spline_index_xN;
                    int degree = 3;
                    // Input
                    std::cout << "Enter the file name: ";
                    std::cin >> filename;
                    // Validate - Get data
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    // Prepare data - Create Objects
                    int rows_table = lines_count - 1;
                    Matrix table_src(rows_table, degree + 2);
                    Matrix newton_table_interval(degree + 1, degree + 2);
                    std::vector<Spline> splines;
                    // Parse file
                    exit_code = file_parse_std(table_src, filename);
                    if (exit_code)
                        return exit_code;
                    // Get arguments x0 and xN
                    double x0 = table_src[0][0].value;
                    double xN = table_src[table_src.get_rows() - 1][0].value;
                    // ----- NEWTON -----
                    compute_interval_std(table_src, newton_table_interval, x0, degree);
                    newton_init_vectors(newton_table_interval);
                    newton_compute_vectors(newton_table_interval, degree);
                    newton_compute_values(newton_table_interval, degree);
                    double newton_dxx = newton_compute_dxx(newton_table_interval, x0);
                    // ----- SPLINE -----
                    splines_init_vector(splines, table_src);
                    splines_compute_h(splines);
                    splines_compute_a(splines);
                    splines_compute_xi(splines, newton_dxx);
                    splines_compute_eta(splines, newton_dxx);
                    splines_compute_c(splines, newton_dxx, 0);
                    splines_compute_b(splines);
                    splines_compute_bn(splines);
                    splines_compute_d(splines);
                    splines_compute_dn(splines);

                    exit_code = spline_find(splines, x0, spline_index_x0);
                    if (exit_code)
                        return exit_code;
                    exit_code = spline_find(splines, xN, spline_index_xN);
                    if (exit_code)
                        return exit_code;
                    
                    double y0 = splines[spline_index_x0].spline_interpolate(x0);
                    double yN = splines[spline_index_xN].spline_interpolate(xN);

                    std::cout << "y0: " << y0 << std::endl;
                    std::cout << "yN: " << yN << std::endl;
                    break;
                }
                case 23:
                {
                    std::string filename;
                    int lines_count;
                    int columns_count;
                    int spline_index_x0;
                    int spline_index_xN;
                    int degree = 3;
                    // Input
                    std::cout << "Enter the file name: ";
                    std::cin >> filename;
                    // Validate - Get data
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    // Prepare data - Create Objects
                    int rows_table = lines_count - 1;
                    Matrix table_src(rows_table, degree + 2);
                    Matrix newton_table_interval_x0(degree + 1, degree + 2);
                    Matrix newton_table_interval_xN(degree + 1, degree + 2);
                    std::vector<Spline> splines;
                    // Parse file
                    exit_code = file_parse_std(table_src, filename);
                    if (exit_code)
                        return exit_code;
                    // Get arguments x0 and xN
                    double x0 = table_src[0][0].value;
                    double xN = table_src[table_src.get_rows() - 1][0].value;
                    // ----- NEWTON (x0) -----
                    compute_interval_std(table_src, newton_table_interval_x0, x0, degree);
                    newton_init_vectors(newton_table_interval_x0);
                    newton_compute_vectors(newton_table_interval_x0, degree);
                    newton_compute_values(newton_table_interval_x0, degree);
                    double newton_dxx_x0 = newton_compute_dxx(newton_table_interval_x0, x0);
                    // ----- NEWTON (xN) -----
                    compute_interval_std(table_src, newton_table_interval_xN, xN, degree);
                    newton_init_vectors(newton_table_interval_xN);
                    newton_compute_vectors(newton_table_interval_xN, degree);
                    newton_compute_values(newton_table_interval_xN, degree);
                    double newton_dxx_xN = newton_compute_dxx(newton_table_interval_xN, xN);
                    // ----- SPLINE -----
                    splines_init_vector(splines, table_src);
                    splines_compute_h(splines);
                    splines_compute_a(splines);
                    splines_compute_xi(splines, newton_dxx_x0);
                    splines_compute_eta(splines, newton_dxx_x0);
                    splines_compute_c(splines, newton_dxx_x0, newton_dxx_xN);
                    splines_compute_b(splines);
                    splines_compute_bn(splines);
                    splines_compute_d(splines);
                    splines_compute_dn(splines);

                    exit_code = spline_find(splines, x0, spline_index_x0);
                    if (exit_code)
                        return exit_code;
                    exit_code = spline_find(splines, xN, spline_index_xN);
                    if (exit_code)
                        return exit_code;
                    
                    double y0 = splines[spline_index_x0].spline_interpolate(x0);
                    double yN = splines[spline_index_xN].spline_interpolate(xN);

                    std::cout << "y0: " << y0 << std::endl;
                    std::cout << "yN: " << yN << std::endl;
                    break;
                }
                case 31:
                {
                    std::string filename;
                    int lines_count;
                    int columns_count;
                    int spline_index;
                    double x;
                    int degree = 3;
                    // Input
                    std::cout << "Enter the file name: ";
                    std::cin >> filename;
                    std::cout << "Enter x: ";
                    std::cin >> x;
                    // Validate - Get data
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    int rows_table = lines_count - 1;
                    // Create objects
                    Matrix table_src(rows_table, degree + 2);
                    Matrix newton_table_interval(degree + 1, degree + 2);
                    std::vector<Spline> splines;
                    // Parse file
                    exit_code = file_parse_std(table_src, filename);
                    if (exit_code)
                        return exit_code;
                    // ----- NEWTON -----
                    compute_interval_std(table_src, newton_table_interval, x, degree);
                    newton_init_vectors(newton_table_interval);
                    newton_compute_vectors(newton_table_interval, degree);
                    newton_compute_values(newton_table_interval, degree);
                    newton_table_interval.print_cell_value();
                    double y_newton = newton_interpolate(newton_table_interval, x, degree);
                    std::cout << "Y Newton: " << y_newton << std::endl;
                    // ----- SPLINE -----
                    splines_init_vector(splines, table_src);
                    splines_compute_h(splines);
                    splines_compute_a(splines);
                    splines_compute_xi(splines, 0);
                    splines_compute_eta(splines, 0);
                    splines_compute_c(splines, 0, 0);
                    splines_compute_b(splines);
                    splines_compute_bn(splines);
                    splines_compute_d(splines);
                    splines_compute_dn(splines);
                    exit_code = spline_find(splines, x, spline_index);
                    if (exit_code)
                        return exit_code;
                    double y_spline = splines[spline_index].spline_interpolate(x);
                    std::cout << "Y Spline: " << y_spline << std::endl;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
    while (choice != 4);
    return 0;
}