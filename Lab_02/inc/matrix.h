#ifndef MATRIX_H
#define MATRIX_H

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
        double coefficient;
};

class Matrix
{
    private:
        int rows;
        int cols;
        std::vector<std::vector<Cell>> data;
    public:
        Matrix (int r, int c);

        // Getters
        int get_rows() const;
        int get_cols() const;
};

#endif