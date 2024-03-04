#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <vector>
#include <unordered_map>

class Cell
{
    public:
        double value;
        std::vector<int> integers;
        int block;
        Cell(double val = -1, int block_param = -1);
};

class Matrix
{
    private:
        int rows;
        int cols;
        std::vector<std::vector<Cell>> data;
    public:
        Matrix(int r, int c);
        // Getters
        Cell &get_cell(int row, int col);
        const Cell &get_cell(int row, int col) const;
        int get_rows() const;
        int get_cols() const;
        void print_cell() const;
        void print_cell_value() const;
        void print_cell_vector() const;
        void print_cell_block() const;
        std::vector<Cell> &operator[](int index);
        const std::vector<Cell> &operator[](int index) const;
};

#endif