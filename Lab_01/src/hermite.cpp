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
        for (int row = 0; row < (n - 1); row++)
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

void compute_hermite_cells_values(Matrix &matrix, int n)
{
    for (int col = 2; col < (n + 1); col++)
    {
        for (int row = 0; row < (n - 1); row++)
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

void print_hermite_polynomial(const Matrix &hermite_table, int nodes)
{
    const double EPSILON = std::numeric_limits<double>::epsilon();
    std::cout << "The Hermite Interpolation Polynomial is:\n";

    std::cout << hermite_table[0][1].value;

    for (int i = 1; i < nodes; ++i)
    {
        std::cout << " + " << hermite_table[0][i + 1].value;

        for (int j = 0, power = 1; j < i; ++j, ++power) {
            if (hermite_table[j][0].value >= 0)
                std::cout << "(x - " << hermite_table[j][0].value << ")";
            else
                std::cout << "(x + " << -hermite_table[j][0].value << ")";

            if (j < i - 1 && std::abs(hermite_table[j][0].value - hermite_table[j + 1][0].value) < EPSILON)
            {
                std::cout << "^" << power;
            }
            else
            {
                power = 0;
            }
        }
    }

    std::cout << std::endl;
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