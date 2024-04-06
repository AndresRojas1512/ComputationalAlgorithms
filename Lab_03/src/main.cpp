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
    std::string filename;
    double x, y, z;
    int nx, ny, nz;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    input_vals(x, y, z);
    input_degrees(nx, ny, nz);
    Table table;
    parseCSVToTable(filename, table);
    table.init_zs();
    double result_newton = newton_trilinear(x, y, z, nx, ny, nz, table);
    double result_spline = spline_trilinear(x, y, z, table);
    double result_mixed = mixed_trilinear(x, y, z, nx, ny, nz, table);
    std::cout << "Result Newton: " << result_newton << std::endl;
    std::cout << "Result Spline: " << result_spline << std::endl;
    std::cout << "Result Mixed: " << result_mixed << std::endl;
    return 0;
}