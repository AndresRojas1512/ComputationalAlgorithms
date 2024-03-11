#include <iostream>
#include <string>
#include "linkage.h"
#include "ui.h"
#include "file.h"
#include "matrix.h"
#include "newton.h"
#include "hermite.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    int choice;
    do
    {
        menu();
        if (input_choice(&choice))
            puts("\nОшибка. Ввод действия");
        else
        {
            switch (choice)
            {
                case 0:
                {
                    std::string filename;
                    std::string newton_values_csv = "newton_values_0.csv";
                    std::string hermite_values_csv = "hermite_values_0.csv";
                    std::string newton_vectors_csv = "newton_vectors_0.csv";
                    std::string hermite_vectors_csv = "hermite_vectors_0.csv";
                    std::string hermite_blocks_csv = "hermite_blocks_0.csv";

                    int lines_count;
                    int columns_count;
                    double x;
                    int degree;
                    int points;
                    // Input data
                    std::cout << "Введите имя файла: ";
                    std::cin >> filename;
                    std::cout << "Введите степень полинома Ньютона: ";
                    std::cin >> degree;
                    std::cout << "Введите количество узлов для полинома Эрмита: ";
                    std::cin >> points;
                    std::cout << "Введите X: ";
                    std::cin >> x;
                    // Validate - Get data
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    // Prepare data
                    int rows_table = lines_count - 1;
                    // ---------- NEWTON ----------
                    double newton_result;
                    Matrix newton_table_base(rows_table, degree + 2);
                    Matrix newton_table_interval(degree + 1, degree + 2);
                    exit_code = file_parse_std(newton_table_base, filename);
                    if (exit_code)
                        return exit_code;
                    compute_interval_std(newton_table_base, newton_table_interval, x, degree);
                    newton_init_vectors(newton_table_interval);
                    newton_compute_vectors(newton_table_interval, degree);
                    newton_compute_values(newton_table_interval, degree);
                    newton_result = newton_interpolate(newton_table_interval, x, degree);
                    std::cout << "Результат (Ньютон): " << newton_result << std::endl;
                    newton_table_interval.print_cell_value_csv(newton_values_csv);
                    newton_table_interval.print_cell_vector_csv(newton_vectors_csv);
                    // ---------- HERMITE ----------
                    double hermite_result;
                    int data_count = columns_count - 1;
                    Matrix table_input(rows_table, 2);
                    Matrix table_interval(points, 2);
                    Matrix table_hermite(points * data_count, (points * data_count) + 1);
                    Matrix table_derivatives(rows_table, columns_count - 2);
                    exit_code = file_parse_std(table_input, filename);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_parse_derivatives(table_derivatives, filename);
                    if (exit_code)
                        return exit_code;
                    hermite_init_base_blocks(table_input);
                    compute_interval_std(table_input, table_interval, x, points - 1);
                    hermite_init_values_blocks(table_interval, table_hermite, data_count);
                    hermite_init_vectors(table_hermite);
                    hermite_compute_vectors(table_hermite);
                    hermite_compute_derivatives(table_hermite, table_derivatives);
                    hermite_compute_values(table_hermite);
                    hermite_result = hermite_interpolate(table_hermite, x);
                    std::cout << "Результат (Эрмит): " << hermite_result << std::endl;
                    table_hermite.print_cell_value_csv(hermite_values_csv);
                    table_hermite.print_cell_block_csv(hermite_blocks_csv);
                    table_hermite.print_cell_vector_csv(hermite_vectors_csv);
                    break;
                }
                case 1: // Comparar resultados
                {
                    std::string filename;
                    int lines_count;
                    int columns_count;
                    double x;
                    // Input
                    std::cout << "Введите имя файла: ";
                    std::cin >> filename;
                    std::cout << "Введите Х";
                    std::cin >> x;
                    // Validate-Get Data
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    
                    int rows_table = lines_count - 1;
                    // ---------- DEGREE p = 2, 5, 8 ----------
                    int degrees_std[3] = {2, 5, 8};
                    std::vector<int> degrees_vec;
                    std::vector<LinkageDegree> vector_ld;
                    int degrees_n = 3;
                    for (int i = 0; i < degrees_n; i++)
                        degrees_vec.push_back(degrees_std[i]);
                    linkage_degree_map(vector_ld, degrees_vec);
                        // --------- NEWTON ---------
                    exit_code = newton_interpolate_degrees_ld(vector_ld, x, rows_table, filename);
                    if (exit_code)
                        return exit_code;
                        // --------- HERMITE ---------
                    exit_code = hermite_interpolate_points_ld(vector_ld, x, rows_table, columns_count, filename);
                    if (exit_code)
                        return exit_code;

                    // ---------- POINTS p = 2, 5, 8 ----------
                    int points_std[3] = {2, 3, 4};
                    std::vector<int> points_vec;
                    std::vector<LinkagePoint> vector_lp;
                    int points_n  = 3;
                    for (int i = 0; i < points_n; i++)
                        points_vec.push_back(points_std[i]);
                    linkage_point_map(vector_lp, points_vec);
                    // --------- NEWTON ---------
                    exit_code = newton_interpolate_degrees_lp(vector_lp, x, rows_table, filename);
                    if (exit_code)
                        return exit_code;
                    // --------- HERMITE ---------
                    exit_code = hermite_interpolate_points_lp(vector_lp, x, rows_table, columns_count, filename);
                    if (exit_code)
                        return exit_code;
                    break;
                }
                case 2: // Encontrar raiz
                {
                    std::string filename;
                    std::string newton_values_csv = "newton_values_2.csv";
                    std::string hermite_values_csv = "hermite_values_2.csv";
                    std::string newton_vectors_csv = "newton_vectors_2.csv";
                    std::string hermite_vectors_csv = "hermite_vectors_2.csv";
                    std::string hermite_blocks_csv = "hermite_blocks_2.csv";
                    int lines_count;
                    int columns_count;
                    double y = 0.0;
                    // Input
                    std::cout << "Введите имя файла: ";
                    std::cin >> filename;
                    // Validate-Get Data
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                                        
                    // Prepare data
                    int rows_table = lines_count - 1;
                    // -------- NEWTON --------
                    double newton_result;
                    int standard_degree = 2;
                    Matrix newton_table_base(rows_table, standard_degree + 2);
                    Matrix newton_table_inverted(rows_table, standard_degree + 2);
                    Matrix newton_table_interval(rows_table, standard_degree + 2);
                    exit_code = file_parse_std(newton_table_base, filename);
                    if (exit_code)
                        return exit_code;
                    newton_inverse(newton_table_base, newton_table_inverted);
                    compute_interval_std(newton_table_inverted, newton_table_interval, y, standard_degree);
                    newton_init_vectors(newton_table_interval);
                    newton_compute_vectors(newton_table_interval, standard_degree);
                    newton_compute_values(newton_table_interval, standard_degree);
                    newton_result = newton_interpolate(newton_table_interval, y, standard_degree);
                    std::cout << "Результат (Ньютон): " << newton_result << std::endl;
                    newton_table_interval.print_cell_value_csv(newton_values_csv);
                    newton_table_interval.print_cell_vector_csv(newton_vectors_csv);
                    // ---------- HERMITE ----------
                    int standard_points = 2;
                    int data_count = columns_count - 1;
                    Matrix hermite_table_base(rows_table, 2);
                    Matrix hermite_table_base_inverted(rows_table, 2);
                    Matrix hermite_table_interval(standard_points, 2);
                    Matrix hermite_table_format(standard_points * data_count, (standard_points * data_count) + 1);
                    Matrix hermite_table_derivatives(rows_table, columns_count - 2);
                    Matrix hermite_table_derivatives_inverted(rows_table, columns_count - 2);

                    exit_code = file_parse_std(hermite_table_base, filename);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_parse_derivatives(hermite_table_derivatives, filename);
                    if (exit_code)
                        return exit_code;
                        
                    hermite_invert_derivatives(hermite_table_derivatives, hermite_table_derivatives_inverted);
                    newton_inverse(hermite_table_base, hermite_table_base_inverted);
                    hermite_init_base_blocks(hermite_table_base_inverted);
                    compute_interval_std(hermite_table_base_inverted, hermite_table_interval, y, standard_points - 1);
                    // std::cout << "Hermite interval: " << std::endl;
                    // hermite_table_interval.print_cell_value();
                    hermite_init_values_blocks(hermite_table_interval, hermite_table_format, data_count);
                    hermite_init_vectors(hermite_table_format);
                    hermite_compute_vectors(hermite_table_format);
                    hermite_compute_derivatives(hermite_table_format, hermite_table_derivatives_inverted);
                    // std::cout << "Hermite derivatives: " << std::endl;
                    // hermite_table_format.print_cell_value();
                    hermite_compute_values(hermite_table_format);
                    // std::cout << "Hermite values: " << std::endl;
                    // hermite_table_format.print_cell_value();
                    double result = hermite_interpolate(hermite_table_format, y);
                    std::cout << "Результат(Эрмит): " << result << std::endl;
                    hermite_table_format.print_cell_value_csv(hermite_values_csv);
                    hermite_table_format.print_cell_vector_csv(hermite_vectors_csv);
                    hermite_table_format.print_cell_block_csv(hermite_blocks_csv);
                    break;
                }
                case 3: // Resolver sistema
                {
                    std::string filename_fx;
                    std::string filename_gx;
                    std::vector<double> results;
                    int lines_count;
                    int columns_count;

                    std::cout << "Введите имя файля для f(x): ";
                    std::cin >> filename_fx;

                    std::cout << "Введите имя файля для g(x): ";
                    std::cin >> filename_gx;

                    exit_code = file_count_lines(filename_fx, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename_fx, columns_count);
                    if (exit_code)
                        return exit_code;
                    
                    // Prepared data
                    int rows_table = lines_count - 1;

                    int standard_degree = 4;

                    Matrix newton_table_base_fx(rows_table, standard_degree + 2);
                    Matrix newton_table_fx_interval(rows_table, standard_degree + 2);

                    Matrix newton_table_base_gx(rows_table, standard_degree + 2);
                    Matrix newton_table_interpolated_gx(rows_table, standard_degree + 2);
                    
                    Matrix newton_table_differences(rows_table, standard_degree + 2);
                    Matrix newton_table_diffinv(rows_table, standard_degree + 2);
                    Matrix newton_table_diffinv_interval(rows_table, standard_degree + 2);
                    

                    exit_code = file_parse_std(newton_table_base_fx, filename_fx);
                    if (exit_code)
                        return exit_code;
                    
                    exit_code = file_parse_std(newton_table_base_gx, filename_gx);
                    if (exit_code)
                        return exit_code;

                    newton_interpolate_complete_table(newton_table_base_fx, newton_table_base_gx, newton_table_interpolated_gx, standard_degree);
                    newton_compute_functions_difference(newton_table_base_fx, newton_table_interpolated_gx, newton_table_differences);
                    newton_inverse(newton_table_differences, newton_table_diffinv);

                    compute_interval_std(newton_table_diffinv, newton_table_diffinv_interval, 0.0, standard_degree);
                    newton_init_vectors(newton_table_diffinv_interval);
                    newton_compute_vectors(newton_table_diffinv_interval, standard_degree);
                    newton_compute_values(newton_table_diffinv_interval, standard_degree);
                    double x_root = newton_interpolate(newton_table_diffinv_interval, 0.0, standard_degree);

                    compute_interval_std(newton_table_base_fx, newton_table_fx_interval, x_root, standard_degree);
                    newton_init_vectors(newton_table_fx_interval);
                    newton_compute_vectors(newton_table_fx_interval, standard_degree);
                    newton_compute_values(newton_table_fx_interval, standard_degree);
                    double y_root = newton_interpolate(newton_table_fx_interval, x_root, standard_degree);

                    std::cout << "X: " << x_root << ", Y: " << y_root << std::endl;
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