#include <iostream>
#include <string>
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

                    if (!method_choice)
                    {
                        std::cout << "\tNEWTON" << std::endl;
                        int degree;
                        std::cout << "Enter degree : ";
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
                    }
                    else
                    {
                        std::cout << "\tHERMITE\t" << std::endl;
                    }
                    break;
                }
                case 1:
                {
                    std::string filename;
                    std::vector<int> degrees; 
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

                    if (!method_choice)
                    {
                        std::cout << "\tNEWTON" << std::endl;
                        int degree_count;
                        std::cout << "Enter degree count: ";
                        std::cin >> degree_count;
                        std::cout << "Enter x: ";
                        std::cin >> x;

                        for (int i = 1; i <= degree_count; i++)
                            degrees.push_back(i);

                        exit_code = interpolate_degrees_newton(degrees, x, rows_table, filename);
                        if (exit_code)
                            return exit_code;
                    }
                    else
                    {
                        std::cout << "\tHERMITE\t" << std::endl;
                    }
                    
                    break;
                }
                case 2:
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

                    if (!method_choice)
                    {
                        std::cout << "\tNEWTON" << std::endl;
                        int standard_degree = 3;
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
                    }
                    break;
                }
                case 3:
                {
                    std::cout << "System solving" << std::endl;
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