#include "hermite.h"

void init_base_matrix_blocks(Matrix &matrix)
{
    for (int i = 0; i < matrix.get_rows(); i++)
    {
        matrix[i][X].block = i;
        matrix[i][Y].block = i;
    }
}

// Multiplies the rows by data_count
void init_hermite_table(Matrix &table_interval, Matrix &table_hermite, int data_count)
{
    for (int i = 0; i < table_interval.get_rows(); i++)
    {
        for (int j = 0; j < data_count; j++)
        {
            int index = i * data_count + j;
            table_hermite[index][X].value = table_interval[i][X].value;
            table_hermite[index][Y].value = table_interval[i][Y].value;

            table_hermite[index][X].block = table_interval[i][X].block;
            table_hermite[index][Y].block = table_interval[i][Y].block;
        }
    }
}

// Init the first X Y vectors
void init_hermite_matrix_vectors(Matrix &matrix)
{
    int index = 0;
    for (int row = 0; row < matrix.get_rows(); row++)
    {
        matrix[row][X].integers.push_back(index);
        matrix[row][Y].integers.push_back(index);
        index++;
    }
}

// Compute hermite_table vectors
void compute_hermite_cells_vectors(Matrix &matrix)
{
    for (int col = 2; col < matrix.get_cols(); col++)
    {
        for (int row = 0; row < (matrix.get_rows() - 1); row++)
        {
            matrix[row][col].integers.clear();

            auto &left = matrix[row][col - 1].integers;
            auto &left_diagonal = matrix[row + 1][col - 1].integers;
            matrix[row][col].integers.insert(matrix[row][col].integers.end(), left.begin(), left.end());
            matrix[row][col].integers.insert(matrix[row][col].integers.end(), left_diagonal.begin(), left_diagonal.end());

            auto &vec = matrix[row][col].integers;
            std::sort(vec.begin(), vec.end());
            auto last_unique = std::unique(vec.begin(), vec.end());
            vec.erase(last_unique, vec.end());
        }
    }
}

// Put derivatives where they are needed
void compute_hermite_derivatives(Matrix &matrix, Matrix &derivatives)
{
    int derivative_index = 0; // derivative degree
    for (int col = 2; col < matrix.get_cols(); col++)
    {
        for (int row = 0; row < (matrix.get_rows() - 1); row++)
        {
            int left_block = matrix[row][col - 1].block;
            int left_diagonal_block = matrix[row + 1][col - 1].block;
            if ((left_block == left_diagonal_block) && left_block != -1 && left_diagonal_block != -1)
            {
                int cell_vector_len = matrix[row][col].integers.size();
                matrix[row][col].block = left_block;
                double derivative = derivatives[left_block][derivative_index].value;
                double factorial = compute_factorial(cell_vector_len - 1);
                matrix[row][col].value = derivative / factorial;
                // std::cout << "Cell[" << row << "][" << col << "]. Derivative: " << derivative << std::endl;
            }
        }
        derivative_index++;
    }
}

void compute_hermite_cells_values(Matrix &matrix)
{
    for (int col = 2; col < matrix.get_cols(); col++)
    {
        for (int row = 0; row < (matrix.get_rows() - 1); row++)
        {
            if (matrix[row][col].block == -1)
            {
                // std::cout << "[" << row << "]" << "[" << col << "]:" << std::endl;
                // std::cout << "Dividend: " << matrix[row + 1][col - 1].value << " - " << matrix[row][col - 1].value << std::endl;
                // std::cout << "Divisor: " << matrix[matrix[row][col].integers.back()][X].value << " - " << matrix[matrix[row][col].integers.front()][X].value << std::endl;
                
                double dividend = matrix[row + 1][col - 1].value - matrix[row][col - 1].value;
                double divisor = matrix[matrix[row][col].integers.back()][X].value - matrix[matrix[row][col].integers.front()][X].value;
                matrix[row][col].value = dividend / divisor;
            }
        }
    }
}

double interpolate_hermite(const Matrix &table_hermite, double x)
{
    double result = table_hermite[0][1].value;
    double term = 1.0;
    for (int i = 1; i < table_hermite.get_rows(); ++i)
    {
        term *= (x - table_hermite[i - 1][0].value);
        result += table_hermite[0][i + 1].value * term;
    }
    return result;
}

double compute_factorial(int n)
{
    double result = 1.0;
    for (int i = 2; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}