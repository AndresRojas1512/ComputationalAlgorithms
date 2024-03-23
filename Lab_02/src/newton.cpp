#include "newton.h"

void compute_interval_std(const Matrix& input_matrix, Matrix& output_matrix, double x, int n)
{
    n += 1;
    int rows = input_matrix.get_rows();
    int best_start_index = 0;
    double min_diff = std::numeric_limits<double>::max();

    for (int i = 0; i <= rows - n; ++i)
    {
        double left_value = input_matrix[i][0].value;
        double right_value = input_matrix[i + n - 1][0].value;
        
        if (left_value <= x && x <= right_value)
        {
            double diff = std::abs((right_value - left_value) / 2 + left_value - x);
            if (diff < min_diff)
            {
                min_diff = diff;
                best_start_index = i;
            }
        }
        else if (x < left_value)
        {
            double diff = left_value - x;
            if (diff < min_diff)
            {
                min_diff = diff;
                best_start_index = i;
            }
        }
        else if (x > right_value)
        {
            double diff = x - right_value;
            if (diff < min_diff)
            {
                min_diff = diff;
                best_start_index = i;
            }
        }
    }

    output_matrix = Matrix(n, input_matrix.get_cols());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < input_matrix.get_cols(); ++j)
        {
            output_matrix[i][j] = input_matrix[best_start_index + i][j];
        }
    }
}

void newton_init_vectors(Matrix &matrix)
{
    for (int i = 0; i < matrix.get_rows(); i++)
    {
        matrix[i][X].integers.push_back(i);
        matrix[i][Y].integers.push_back(i);
    }
}

void newton_compute_vectors(Matrix &matrix, int n)
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

void newton_compute_values(Matrix &matrix, int n)
{
    for (int col = 2; col < (n + 2); col++)
    {
        for (int row = 0; row < n; row++)
        {            
            double dividend = matrix[row + 1][col - 1].value - matrix[row][col - 1].value;
            double divisor = matrix[matrix[row][col].integers.back()][X].value - matrix[matrix[row][col].integers.front()][X].value;
            matrix[row][col].value = dividend / divisor;
        }
    }
}

double newton_interpolate(const Matrix &newton_table, double x, int n)
{
    double result = newton_table[0][1].value;
    double term = 1.0;
    for (int i = 1; i < n + 1; ++i)
    {
        term *= (x - newton_table[i - 1][0].value);
        result += newton_table[0][i + 1].value * term;
    }
    return result;
}

double newton_compute_dxx(const Matrix &newton_table, double x)
{
    double result = 2 * newton_table[0][3].value + 6 * newton_table[0][4].value * ((x - newton_table[1][0].value) + (x - newton_table[0][0].value));
    return result;
}