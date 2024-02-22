#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
    private:
        int rows;
        int cols;
        double **data;
    public:
        Matrix(int r, int c);
        ~Matrix();

        int get_rows();
        int get_cols();
        double **get_data();

        void print();
};

#endif