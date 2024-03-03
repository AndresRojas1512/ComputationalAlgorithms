#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

class Matrix
{
    private:
        int rows;
        int cols;
        double **data;
    public:
        Matrix(int r, int c);
        Matrix(int r);
        Matrix() = default;
        ~Matrix();

        int get_rows();
        int get_cols();
        double **get_data();

        // Helper methods
        void print();

        // Operator overloading
        double *operator[](int row);
        const double *operator[](int row) const;
};

#endif