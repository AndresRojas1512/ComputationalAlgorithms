#include "hermite.h"

// Init the X and Y columns with block index
void hermite_init_base_blocks(Matrix &matrix)
{
    for (int i = 0; i < matrix.get_rows(); i++)
    {
        matrix[i][X].block = i;
        matrix[i][Y].block = i;
    }
}

// Multiply the rows by the amount of data that is given about the function
void hermite_init_values_blocks(Matrix &table_interval, Matrix &table_hermite, int data_count)
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

// Init the divided differences vector of X and Y columns
void hermite_init_vectors(Matrix &matrix)
{
    int index = 0;
    for (int row = 0; row < matrix.get_rows(); row++)
    {
        matrix[row][X].integers.push_back(index);
        matrix[row][Y].integers.push_back(index);
        index++;
    }
}

// Compute the divided difference vectors for each cell 
void hermite_compute_vectors(Matrix &matrix)
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

// Add the derivatives where needed
void hermite_compute_derivatives(Matrix &matrix, Matrix &derivatives)
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

// Based on the divided differences vector, calculate the values
void hermite_compute_values(Matrix &matrix)
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

double hermite_interpolate(const Matrix &table_hermite, double x)
{
    double result = table_hermite[0][1].value; // Starting with y0
    double term = 1.0;
    
    // Loop through the table using the divided differences
    for (int i = 1; i < table_hermite.get_cols() - 1; i++)
    { // Note the change here to get_cols() - 1
        term *= (x - table_hermite[i - 1][0].value); // Constructing the (x - xi) term correctly
        result += table_hermite[0][i + 1].value * term; // Accessing the coefficients correctly
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

int hermite_interpolate_points_ld(std::vector<LinkageDegree> &vector_ld, double x, int rows_table, int columns_count, std::string filename)
{
    int exit_code = EXIT_SUCCESS;
    int data_count = columns_count - 1;
    for (long unsigned i = 0; i < vector_ld.size() && !exit_code; i++)
    {
        Matrix table_input(rows_table, 2);
        Matrix table_interval(vector_ld[i].hermite_points, 2);
        Matrix table_hermite(vector_ld[i].hermite_points * data_count, (vector_ld[i].hermite_points * data_count) + 1);
        Matrix table_derivatives(rows_table, columns_count - 2);
        exit_code = file_parse_std(table_input, filename);
        if (!exit_code)
        {
            exit_code = file_parse_derivatives(table_derivatives, filename);
            if (!exit_code)
            {
                hermite_init_base_blocks(table_input);
                compute_interval_std(table_input, table_interval, x, vector_ld[i].hermite_points - 1);
                hermite_init_values_blocks(table_interval, table_hermite, data_count);
                hermite_init_vectors(table_hermite);
                hermite_compute_vectors(table_hermite);
                hermite_compute_derivatives(table_hermite, table_derivatives);
                hermite_compute_values(table_hermite);
                double result = hermite_interpolate(table_hermite, x);
                std::cout << "Points: " << vector_ld[i].hermite_points << ", Result: " << result << std::endl;
            }
        }
    }
    return exit_code;
}

int hermite_interpolate_points_lp(std::vector<LinkagePoint> &vector_lp, double x, int rows_table, int columns_count, std::string filename)
{
    int exit_code = EXIT_SUCCESS;
    int data_count = columns_count - 1;
    for (long unsigned i = 0; i < vector_lp.size() && !exit_code; i++)
    {
        Matrix table_input(rows_table, 2);
        Matrix table_interval(vector_lp[i].hermite_points, 2);
        Matrix table_hermite(vector_lp[i].hermite_points * data_count, (vector_lp[i].hermite_points * data_count) + 1);
        Matrix table_derivatives(rows_table, columns_count - 2);
        exit_code = file_parse_std(table_input, filename);
        if (!exit_code)
        {
            exit_code = file_parse_derivatives(table_derivatives, filename);
            if (!exit_code)
            {
                hermite_init_base_blocks(table_input);
                compute_interval_std(table_input, table_interval, x, vector_lp[i].hermite_points - 1);
                hermite_init_values_blocks(table_interval, table_hermite, data_count);
                hermite_init_vectors(table_hermite);
                hermite_compute_vectors(table_hermite);
                hermite_compute_derivatives(table_hermite, table_derivatives);
                hermite_compute_values(table_hermite);
                double result = hermite_interpolate(table_hermite, x);
                std::cout << "Points: " << vector_lp[i].hermite_points << ", Result: " << result << std::endl;
            }
        }
    }
    return exit_code;
}

// Inverse interpolation
void hermite_invert_derivatives(Matrix &table_derivatives, Matrix &table_derivatives_inverted)
{
    double epsilon = std::numeric_limits<double>::epsilon();
    for (int i = 0; i < table_derivatives.get_rows(); i++)
    {
        for (int j = 0; j < table_derivatives.get_cols(); j++)
        {
            if (std::abs(table_derivatives[i][j].value) < epsilon)
            {
                table_derivatives_inverted[i][j].value = 1e6;
            }
            else
            {
                table_derivatives_inverted[i][j].value = 1.0 / table_derivatives[i][j].value;
            }
        }
    }
}
