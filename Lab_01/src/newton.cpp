#include "newton.h"

void init_newton_matrix_vectors(Matrix &matrix)
{
    for (int i = 0; i < matrix.get_rows(); i++)
    {
        matrix[i][X].integers.push_back(i);
        matrix[i][Y].integers.push_back(i);
    }
}

void compute_newton_cells_vectors(Matrix &matrix, int n)
{
    for (int col = 2; col < (n + 2); col++)
    {
        for (int row = 0; row < n; row++)
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

void compute_newton_cells_values(Matrix &matrix, int n)
{
    for (int col = 2; col < (n + 2); col++)
    {
        for (int row = 0; row < n; row++)
        {
            std::cout << "[" << row << "]" << "[" << col << "]:" << std::endl;
            std::cout << "Dividend: " << matrix[row + 1][col - 1].value << " - " << matrix[row][col - 1].value << std::endl;
            std::cout << "Divisor: " << matrix[matrix[row][col].integers.back()][X].value << " - " << matrix[matrix[row][col].integers.front()][X].value << std::endl;
            
            double dividend = matrix[row + 1][col - 1].value - matrix[row][col - 1].value;
            double divisor = matrix[matrix[row][col].integers.back()][X].value - matrix[matrix[row][col].integers.front()][X].value;
            matrix[row][col].value = dividend / divisor;
        }
    }
}

double interpolate_newton(const Matrix &newton_table, double x, int n)
{
    double result = newton_table[0][1].value;
    double term = 1.0;
    for (int i = 1; i <= n; ++i)
    {
        term *= (x - newton_table[i - 1][0].value);
        result += newton_table[0][i + 1].value * term;
    }
    return result;
}

void find_interval_containing_x_newton(Matrix &input_matrix, Matrix &output_matrix, double x, int n)
{
    n++;
    input_matrix.sort_by_first_column();
    
    int start = 0, end = input_matrix.get_rows(), mid;
    while (start < end)
    {
        mid = start + (end - start) / 2;
        if (input_matrix[mid][0].value < x)
            start = mid + 1;
        else
            end = mid;
    }

    start = std::max(0, start - n/2);
    end = std::min(start + n, input_matrix.get_rows());
    start = std::max(0, end - n);

    for (int i = start; i < end; ++i)
    {
        for (int j = 0; j < input_matrix.get_cols(); ++j)
        {
            output_matrix[i-start][j] = input_matrix[i][j];
        }
    }
}

void print_newton_polynomial(const Matrix &newton_table, int n)
{
    std::cout << "The Newton Interpolation Polynomial of degree " << n << " is:\n";

    std::cout << newton_table[0][1].value;

    for (int i = 1; i <= n; ++i)
    {
        std::cout << " + " << newton_table[0][i + 1].value;

        for (int j = 0; j < i; ++j)
        {
            if (newton_table[j][0].value >= 0)
                std::cout << "(x - " << newton_table[j][0].value << ")";
            else
                std::cout << "(x + " << -newton_table[j][0].value << ")";
        }
    }
    std::cout << std::endl;
}

void inverse_table_newton(Matrix &input_table, Matrix &inverse_table)
{
    for (int i = 0; i < input_table.get_rows(); i++)
    {
        inverse_table[i][0].value = input_table[i][1].value;
        inverse_table[i][1].value = input_table[i][0].value;
    }
}

