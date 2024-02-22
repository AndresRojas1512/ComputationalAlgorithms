#include "matrix.h"

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(nullptr)
{
    data = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new double [cols];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete data[i];
    }
    delete data;
}

int Matrix::get_rows()
{
    return rows;
}

int Matrix::get_cols()
{
    return cols;
}

double **Matrix::get_data()
{
    return data;
}

void Matrix::print()
{
    for (int i = 0; i > rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}