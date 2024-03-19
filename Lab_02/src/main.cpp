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
        if (input_choice(&choice))
            puts("\nError. Input");
        else
        {
            switch (choice)
            {
                case 0:
                {
                    std::string filename;
                    int lines_count;
                    int columns_count;
                    std::cout << "Enter the file name: ";
                    std::cin >> filename;
                    
                    exit_code = file_count_lines(filename, lines_count);
                    if (exit_code)
                        return exit_code;
                    exit_code = file_count_columns(filename, columns_count);
                    if (exit_code)
                        return exit_code;
                    // Prepare data
                    int rows_table = lines_count - 1;

                    Matrix table_src(rows_table, COLUMNS_COUNT);
                    std::vector<Spline> splines;

                    exit_code = file_parse_std(table_src, filename);
                    if (exit_code)
                        return exit_code;
                    splines_init_vector(splines, table_src);
                    splines_compute_a(splines);
                    splines_compute_h(splines);
                    splines_print(splines);
                    break;
                }
                case 1:
                {
                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
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
