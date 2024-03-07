#include "matrix.h"

Cell::Cell(double val, int block_param) : value(val), block(block_param)
{
}

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<Cell>(c))
{
}

void Matrix::sort_by_first_column()
{
    std::sort(data.begin(), data.end(), [](const std::vector<Cell>& a, const std::vector<Cell>& b) {
        return a.front().value < b.front().value;
    });
}

Cell &Matrix::get_cell(int row, int col)
{
    return data[row][col];
}

const Cell &Matrix::get_cell(int row, int col) const
{
    return data[row][col];
}

int Matrix::get_rows() const
{
    return rows;
}

int Matrix::get_cols() const
{
    return cols;
}

void Matrix::print_cell() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << "Cell[" << i << "][" << j << "] - Value: " << data[i][j].value << ", Integers: ";
            for (long unsigned int k = 0; k < data[i][j].integers.size(); k++)
            {
                std::cout << data[i][j].integers[k] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Matrix::print_cell_value() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << std::fixed << std::setprecision(6) << data[i][j].value << "    ";
        }
        std::cout << std::endl;
    }
}

void Matrix::print_cell_vector() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << "Cell[" << i << "][" << j << "]: ";
            for (long unsigned int k = 0; k < data[i][j].integers.size(); k++)
            {
                std::cout << data[i][j].integers[k] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Matrix::print_cell_block() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << "Cell[" << i << "][" << j << "] Block[" << data[i][j].block << "]: " << "Value: " << data[i][j].value << ", Integers: ";
            for (long unsigned int k = 0; k < data[i][j].integers.size(); k++)
            {
                std::cout << data[i][j].integers[k] << " ";
            }
            std::cout << "    ";
        }
        std::cout << std::endl;
    }
}

std::vector<Cell> &Matrix::operator[](int index)
{
    return data[index];
}

const std::vector<Cell> &Matrix::operator[](int index) const
{
    return data[index];
}