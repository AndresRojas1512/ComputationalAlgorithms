#include "matrix.h"

Cell::Cell(double val, int block_param) : value(val), block(block_param)
{
}

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<Cell>(c))
{
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

void Matrix::print_cell_value() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << "[" << i << "][" << j << "]:" << std::fixed << std::setprecision(2) << data[i][j].value;
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
            std::cout << "[" << i << "][" << j << "]:";
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

void Matrix::print_cell_value_csv(const std::string &filename) const
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            outFile << std::fixed << std::setprecision(6) << data[i][j].value;
            if (j < cols - 1) outFile << ",";
        }
        outFile << std::endl;
    }
    outFile.close(); // Close the file
}

void Matrix::print_cell_vector_csv(const std::string &filename) const
{
    std::ofstream outFile(filename); // Open the file for writing

    if (!outFile)
    {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            const std::vector<int>& integers = data[i][j].integers;
            for (size_t k = 0; k < integers.size(); k++)
            {
                outFile << integers[k];
                if (k < integers.size() - 1) outFile << "_"; // Add underscore between numbers, but not after the last one
            }
            if (j < cols - 1) outFile << ","; // Don't add a comma after the last element in the row
        }
        outFile << std::endl; // New line after each row
    }

    outFile.close(); // Close the file
}

void Matrix::print_cell_block_csv(const std::string &filename) const
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            outFile << std::fixed << std::setprecision(2) << data[i][j].block;
            if (j < cols - 1) outFile << ",";
        }
        outFile << std::endl;
    }
    outFile.close(); // Close the file
}

std::vector<Cell> &Matrix::operator[](int index)
{
    return data[index];
}

const std::vector<Cell> &Matrix::operator[](int index) const
{
    return data[index];
}