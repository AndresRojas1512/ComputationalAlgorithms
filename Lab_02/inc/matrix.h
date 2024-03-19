#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>

class Cell
{
    public:
        double value;
        int spline_index;

        Cell(double val = 0, int i = -1);
};

class Matrix
{
    private:
        int rows;
        int cols;
        std::vector<std::vector<Cell>> data;
    public:
        Matrix (int r, int c);

        int get_rows() const;
        int get_cols() const;

        std::vector<Cell> &operator[](int index);
        const std::vector<Cell> &operator[](int index) const;
        void print_cell_value() const;
};

#endif