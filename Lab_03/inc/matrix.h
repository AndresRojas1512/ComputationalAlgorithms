#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>

class Cell
{
    public:
        double value;
        std::vector<int> integers;
        int block;
        Cell(double val = 0, int block_param = -1);
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
        int get_rows() const;
        int get_cols() const;
        void print_cell_value() const;
        void print_cell_vector() const;
        void print_cell_block() const;

        void print_cell_value_csv(const std::string &filename) const;
        void print_cell_vector_csv(const std::string &filename) const;
        void print_cell_block_csv(const std::string &filename) const;

        std::vector<Cell> &operator[](int index);
        const std::vector<Cell> &operator[](int index) const;
};

#endif
