#include <iostream>
#include "matrix.h"
#include "file.h"
#include "point.h"
#include "spline.h"
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
                    int lines_count;
                    int columns_count;
                    int spline_index;
                    double x;

                    // Input
                    std::cout << "Enter the file name: ";
                    std::cin >> filename;
                    std::cout << "Enter the x: ";
                    std::cin >> x;
                    
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    
                    // Prepare data
                    int rows_table = lines_count - 1;
                    
                    // Create objects
                    Matrix table_src(rows_table, COLUMNS_COUNT);
                    std::vector<Spline> splines;

                    exit_code = file_parse_std(table_src, filename);
                    if (exit_code)
                        return exit_code;
                    
                    // Spline
                    splines_init_vector(splines, table_src);
                    splines_compute_h(splines);
                    splines_compute_a(splines);
                    splines_compute_xi(splines);
                    splines_compute_eta(splines);
                    splines_compute_c(splines);
                    splines_compute_b(splines);
                    splines_compute_bn(splines);
                    splines_compute_d(splines);
                    splines_compute_dn(splines);

                    exit_code = spline_find(splines, x, spline_index);
                    double y = splines[spline_index].spline_interpolate(x);
                    std::cout << "Y: " << y << std::endl;
                    break;
                }
                case 21:
                {
                    std::string filename;
                    int lines_count;
                    int columns_count;
                    int spline_index_x0;
                    int spline_index_xN;

                    // Input
                    std::cout << "Enter the file name: ";
                    std::cin >> filename;

                    // File data
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    
                    // Prepare data
                    int rows_table = lines_count - 1;

                    // Create objects
                    Matrix table_src(rows_table, COLUMNS_COUNT);
                    std::vector<Spline> splines;

                    // Parse file
                    exit_code = file_parse_std(table_src, filename);
                    if (exit_code)
                        return exit_code;
                    
                    // Get arguments x0 and xN
                    double x0 = table_src[0][0];
                    double xN = table_src[table_src.get_rows() - 1][0];
                    std::cout << "x0: " << x0 << std::endl;
                    std::cout << "xN: " << xN << std::endl;

                    // Spline
                    splines_init_vector(splines, table_src);
                    splines_compute_h(splines);
                    splines_compute_a(splines);
                    splines_compute_xi(splines);
                    splines_compute_eta(splines);
                    splines_compute_c(splines);
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
                case 22:
                {
                    break;
                }
                case 23:
                {
                    break;
                }
                case 31:
                {
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
