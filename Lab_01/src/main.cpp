#include <iostream>
#include <string>
#include "matrix.h"
#include "file.h"

int main(void)
{
    std::string filename;
    int n;

    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::cout << "Enter n: ";
    std::cin >> n;

    int lines_count;
    int exit_code = file_count_lines(filename, lines_count);
    if (!exit_code)
    {
        Matrix newton_table(lines_count, n + 2);
        std::cout << "Lines count: " << lines_count << std::endl;
        exit_code = file_parse_newton(newton_table, filename);
        if (!exit_code)
        {
            std::cout << "Parsed succesfull" << std::endl;
        }
        else
        {
            std::cout << "Error parsing" << std::endl;
        }
    }
    return 0;
}