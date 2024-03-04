#include "hermite.h"

void init_hermite_matrix_vectors_blocks(Matrix &matrix, int data_count)
{
    int index = 0;

    for (int row = 0; row < matrix.get_rows(); ++row)
    {
        int row_block = row / data_count;

        matrix[row][X].block = row_block;
        matrix[row][Y].block = row_block;

        matrix[row][X].integers.push_back(index);
        matrix[row][Y].integers.push_back(index);

        index++;
    }
}

void compute_hermite_cells_vectors(Matrix &matrix, int n)
{
    for (int col = 2; col < (n + 1); col++)
    {
        for (int row = 0; row <  (n - 1); row++)
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

void compute_hermite_derivatives(Matrix &matrix, Matrix &derivatives, int n)
{
    int derivative_index = 0;
    for (int col = 2; col < (n + 1); col++)
    {
        for (int row = 0; row <  (n - 1); row++)
        {
            int left_block = matrix[row][col - 1].block;
            int left_diagonal_block = matrix[row + 1][col - 1].block;
            if ((left_block == left_diagonal_block) && left_block != -1 && left_diagonal_block != -1)
            {
                matrix[row][col].block = left_block;
                double derivative = derivatives[left_block][derivative_index].value;

                std::cout << "Cell[" << row << "][" << col << "]. Derivative: " << derivative << std::endl;
            }
        }
        derivative_index++;
    }
}

