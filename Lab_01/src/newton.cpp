#include "newton.h"

void init_matrix_vectors(Matrix &matrix)
{
    for (int i = 0; i < matrix.get_rows(); i++)
    {
        matrix[i][X].integers.push_back(i);
        matrix[i][Y].integers.push_back(i);
    }
}

void compute_cells_vectors(Matrix &matrix, int n)
{
    for (int col = 2;  col < std::min(n + 2, matrix.get_cols()); col++)
    {
        for (int row = 0;row < n && row < matrix.get_rows(); row++)
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

void format_cells_vectors(Matrix &matrix, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = i + 2; j < n + 1; j++) {
            std::cout << "Clearing: [" << i << "][" << j << "]" << std::endl;
            matrix[i][j].integers.clear();
        }
    }
}
