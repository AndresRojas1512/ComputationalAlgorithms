#ifndef NEWTON_H
#define NEWTON_H

#include <iostream>
#include <vector>
#include "matrix.h"

class Newton
{
    private:
        int n;
        Matrix matrix;
    public:
        Newton(int n_param, Matrix &matrix_param) : n(n_param), matrix(matrix_param)
        {
        }
        ~Newton() = default;
};

#endif