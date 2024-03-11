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
            puts("\nError: Enter option 0 - 3");
        else
        {
            switch (choice)
            {
                case 0:
                {
                    std::string filename;
                    int method_choice;
                    double x;
                    int lines_count;
                    int columns_count;

                    std::cout << "Enter file name: ";
                    std::cin >> filename;

                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    
                    std::cout << "0 - Newton ; 1 - Hermite: ";
                    std::cin >> method_choice;
                    
                    // Prepared data
                    int rows_table = lines_count - 1;

                    if (!method_choice) // NEWTON
                    {
                        std::cout << "\tNEWTON" << std::endl;
                        int degree;
                        std::cout << "Enter degree: ";
                        std::cin >> degree;
                        std::cout << "Enter x: ";
                        std::cin >> x;

                        // Create the tables
                        Matrix newton_table_base(rows_table, degree + 2);
                        Matrix newton_table_interval(degree + 1, degree + 2);

                        exit_code = file_parse_newton(newton_table_base, filename);
                        if (exit_code)
                            return exit_code;
                        
                        compute_table_interval_newton(newton_table_base, newton_table_interval, x, degree);
                        init_newton_matrix_vectors(newton_table_interval);
                        compute_newton_cells_vectors(newton_table_interval, degree);
                        compute_newton_cells_values(newton_table_interval, degree);
                        double result = interpolate_newton(newton_table_interval, x, degree);
                        std::cout << "Result: " << result << std::endl;
                        newton_table_interval.print_matrix_style();
                    }
                    else // HERMITE
                    {
                        std::cout << "\tHERMITE\t" << std::endl;
                        int points;
                        std::cout << "Enter points: ";
                        std::cin >> points;
                        std::cout << "Enter x: ";
                        std::cin >> x;

                        int data_count = columns_count - 1;

                        Matrix table_input(rows_table, 2);
                        Matrix table_interval(points, 2);
                        Matrix table_hermite(points * data_count, (points * data_count) + 1);
                        Matrix table_derivatives(rows_table, columns_count - 2);

                        exit_code = file_parse_newton(table_input, filename);
                        if (exit_code)
                            return exit_code;
                        
                        exit_code = file_parse_derivatives(table_derivatives, filename);
                        if (exit_code)
                            return exit_code;

                        init_base_matrix_blocks(table_input);
                        compute_table_interval_newton(table_input, table_interval, x, points - 1);
                        init_hermite_table(table_interval, table_hermite, data_count);
                        init_hermite_matrix_vectors(table_hermite);
                        compute_hermite_cells_vectors(table_hermite);
                        compute_hermite_derivatives(table_hermite, table_derivatives);
                        compute_hermite_cells_values(table_hermite);
                        table_hermite.print_cell_value();
                        double result = interpolate_hermite(table_hermite, x);
                        std::cout << "Result: " << result << std::endl;
                    }
                    break;
                }
                case 1: // Comparar resultados
                {
                    int type_choice;
                    std::string filename;
                    double x;
                    int lines_count;
                    int columns_count;
                    
                    // Input
                    std::cout << "Enter file name: ";
                    std::cin >> filename;

                    std::cout << "Enter x: ";
                    std::cin >> x;

                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    
                    
                    std::cout << "0 - by degree | 1 - by points: ";
                    std::cin >> type_choice;

                    int rows_table = lines_count - 1;

                    if (!type_choice) // By degree | p = 2, 5, 8
                    {
                        int degrees_std[3] = {2, 5, 8};
                        std::vector<int> degrees_vec;
                        std::vector<LinkageDegree> vector_ld;
                        int degrees_n = 3;
                        for (int i = 0; i < degrees_n; i++)
                            degrees_vec.push_back(degrees_std[i]);
                        
                        linkage_degree_map(vector_ld, degrees_vec);
                        // --------- NEWTON ---------
                        exit_code = interpolate_degrees_newton_ld(vector_ld, x, rows_table, filename);
                        if (exit_code)
                            return exit_code;
                        // --------- HERMITE ---------
                        exit_code = interpolate_points_hermite_ld(vector_ld, x, rows_table, columns_count, filename);
                        if (exit_code)
                            return exit_code;
                    }
                    else // By points | n = 2_5
                    {
                        int points_std[3] = {2, 3, 4};
                        std::vector<int> points_vec;
                        std::vector<LinkagePoint> vector_lp;
                        int points_n  = 3;
                        for (int i = 0; i < points_n; i++)
                            points_vec.push_back(points_std[i]);
                        
                        linkage_point_map(vector_lp, points_vec);
                        // --------- NEWTON ---------
                        exit_code = interpolate_degrees_newton_lp(vector_lp, x, rows_table, filename);
                        if (exit_code)
                            return exit_code;
                        // --------- HERMITE ---------
                        exit_code = interpolate_points_hermite_lp(vector_lp, x, rows_table, columns_count, filename);
                        if (exit_code)
                            return exit_code;
                    }
                    break;
                }
                case 2: // Encontrar raiz
                {
                    std::cout << "Find root" << std::endl;
                    std::string filename;
                    int method_choice;
                    int lines_count;
                    int columns_count;

                    std::cout << "Enter file name: ";
                    std::cin >> filename;

                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    
                    std::cout << "0 - Newton ; 1 - Hermite: ";
                    std::cin >> method_choice;
                    
                    // Prepared data
                    int rows_table = lines_count - 1;

                    // -------- NEWTON --------
                    if (!method_choice)
                    {
                        std::cout << "\tNEWTON" << std::endl;
                        int standard_degree = 4;
                        int y = 0.0;

                        Matrix newton_table_base(rows_table, standard_degree + 2);
                        Matrix newton_table_inverted(rows_table, standard_degree + 2);
                        Matrix newton_table_interval(rows_table, standard_degree + 2);

                        exit_code = file_parse_newton(newton_table_base, filename);
                        if (exit_code)
                            return exit_code;

                        inverse_table_newton(newton_table_base, newton_table_inverted);
                        compute_table_interval_newton(newton_table_inverted, newton_table_interval, y, standard_degree);
                        init_newton_matrix_vectors(newton_table_interval);
                        compute_newton_cells_vectors(newton_table_interval, standard_degree);
                        compute_newton_cells_values(newton_table_interval, standard_degree);
                        double result = interpolate_newton(newton_table_interval, y, standard_degree);
                        std::cout << "Root: " << result << std::endl;
                    }
                    else
                    {
                        std::cout << "\tHERMITE\t" << std::endl;
                        int standard_points = 4;
                        int y = 0.0;

                        int data_count = columns_count - 1;

                        Matrix table_input(rows_table, 2);
                        Matrix table_input_inverted(rows_table, 2);

                        Matrix table_interval(standard_points, 2);
                        Matrix table_hermite(standard_points * data_count, (standard_points * data_count) + 1);

                        Matrix table_derivatives(rows_table, columns_count - 2);
                        Matrix table_derivatives_inverted(rows_table, columns_count - 2);

                        exit_code = file_parse_newton(table_input, filename);
                        if (exit_code)
                            return exit_code;
                        
                        exit_code = file_parse_derivatives(table_derivatives, filename);
                        if (exit_code)
                            return exit_code;
                        
                        invert_table_derivatives(table_derivatives, table_derivatives_inverted);
                        inverse_table_newton(table_input, table_input_inverted);
                        init_base_matrix_blocks(table_input_inverted);

                        compute_table_interval_newton(table_input_inverted, table_interval, y, standard_points - 1);
                        init_hermite_table(table_interval, table_hermite, data_count);
                        init_hermite_matrix_vectors(table_hermite);
                        compute_hermite_cells_vectors(table_hermite);
                        compute_hermite_derivatives(table_hermite, table_derivatives_inverted);
                        compute_hermite_cells_values(table_hermite);
                        double result = interpolate_hermite(table_hermite, y);
                        std::cout << "Result: " << result << std::endl;
                    }
                    break;
                }
                case 3: // Resolver sistema
                {
                    std::cout << "System solving" << std::endl;
                    std::string filename_fx;
                    std::string filename_gx;
                    std::vector<double> results;
                    int lines_count;
                    int columns_count;

                    std::cout << "Enter filename_fx: ";
                    std::cin >> filename_fx;

                    std::cout << "Enter file_gx: ";
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
                    

                    exit_code = file_parse_newton(newton_table_base_fx, filename_fx);
                    if (exit_code)
                        return exit_code;
                    
                    exit_code = file_parse_newton(newton_table_base_gx, filename_gx);
                    if (exit_code)
                        return exit_code;

                    interpolate_complete_table(newton_table_base_fx, newton_table_base_gx, newton_table_interpolated_gx, standard_degree);
                    find_functions_difference(newton_table_base_fx, newton_table_interpolated_gx, newton_table_differences);
                    inverse_table_newton(newton_table_differences, newton_table_diffinv);

                    compute_table_interval_newton(newton_table_diffinv, newton_table_diffinv_interval, 0.0, standard_degree);
                    init_newton_matrix_vectors(newton_table_diffinv_interval);
                    compute_newton_cells_vectors(newton_table_diffinv_interval, standard_degree);
                    compute_newton_cells_values(newton_table_diffinv_interval, standard_degree);
                    double x_root = interpolate_newton(newton_table_diffinv_interval, 0.0, standard_degree);

                    compute_table_interval_newton(newton_table_base_fx, newton_table_fx_interval, x_root, standard_degree);
                    init_newton_matrix_vectors(newton_table_fx_interval);
                    compute_newton_cells_vectors(newton_table_fx_interval, standard_degree);
                    compute_newton_cells_values(newton_table_fx_interval, standard_degree);
                    double y_root = interpolate_newton(newton_table_fx_interval, x_root, standard_degree);

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
    while (choice != 0 || choice != 4);

    return 0;
}