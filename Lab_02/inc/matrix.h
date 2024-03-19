#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <utility>

class Matrix
{
    private:
        int rows;
        int cols;
        std::vector<std::vector<double>> data;
    public:
        Matrix (int r, int c);

        int get_rows() const;
        int get_cols() const;

        std::vector<double> &operator[](int index);
        const std::vector<double> &operator[](int index) const;
        void print_cell_value() const;
};

#endif