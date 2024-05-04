#include "table.h"
#include "point.h"
#include "file.h"
#include "polynomial.h"
#include "slae.h"
#include <iostream>
#include <string>

int main(void)
{
    // std::string filename;
    // int rows;
    // int columns;
    // Table table;
    // int exit_code = EXIT_SUCCESS;

    // exit_code = file_count_rows(rows, "data_1v.csv");
    // if (exit_code)
    //     return exit_code;
    // exit_code = file_count_columns(columns, "data_1v.csv");
    // if (exit_code)
    //     return exit_code;
    // table = Table(rows, columns);
    // exit_code = file_parse_1v(table, "data_1v.csv");
    // if (exit_code)
    //     return exit_code;
    // std::cout << "Rows: " << rows << std::endl;
    // std::cout << "Columns: " << columns << std::endl;

    // Polynomial polynomial(3);
    // std::cout << polynomial << std::endl;

    Slae slae(3, 3);
    std::cout << slae;

    return 0;
}