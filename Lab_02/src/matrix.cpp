#include "matrix.h"

Cell::Cell(double val, int i) : value(val), index(i)
{
}

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<Cell>(c))
{
}

int Matrix::get_rows() const
{
    return rows;
}

int Matrix::get_cols() const
{
    return cols;
}

std::vector<Cell> &Matrix::operator[](int index)
{
    return data[index];
}

const std::vector<Cell> &Matrix::operator[](int index) const
{
    return data[index];
}

void Matrix::print_cell_value() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << "[" << i << "][" << j << "]:" << std::fixed << std::setprecision(2) << data[i][j].value << " ";
        }
        std::cout << std::endl;
    }
}
