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
            // std::cout << "[" << row << "]" << "[" << col << "]:" << std::endl;
            // std::cout << "Dividend: " << matrix[row + 1][col - 1].value << " - " << matrix[row][col - 1].value << std::endl;
            // std::cout << "Divisor: " << matrix[matrix[row][col].integers.back()][X].value << " - " << matrix[matrix[row][col].integers.front()][X].value << std::endl;
            
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

void newton_inverse(Matrix &input_table, Matrix &inverse_table)
{
    for (int i = 0; i < input_table.get_rows(); i++)
    {
        inverse_table[i][0].value = input_table[i][1].value;
        inverse_table[i][1].value = input_table[i][0].value;
    }
}

void newton_interpolate_complete_table(Matrix &f_x, Matrix &g_x, Matrix &interpolated_g_x, int n)
{
    std::vector<double> results;
    for (int i = 0; i < f_x.get_rows(); i++)
    {
        // std::cout << "f_x: " << f_x[i][X].value << ", ";
        Matrix g_x_temp = g_x;
        Matrix div_dif_table(n + 1, n + 2);
        compute_interval_std(g_x_temp, div_dif_table, f_x[i][X].value, n);
        newton_init_vectors(div_dif_table);
        newton_compute_vectors(div_dif_table, n);
        newton_compute_values(div_dif_table, n);
        double result = newton_interpolate(div_dif_table, f_x[i][X].value, n);
        // std::cout << "Result: " << result << std::endl;
        results.push_back(result);
    }
    // Fill the table
    for (int i = 0; i < f_x.get_rows(); i++)
    {
        interpolated_g_x[i][X].value = f_x[i][X].value;
        interpolated_g_x[i][Y].value = results[i];
    }
}

void newton_compute_functions_difference(Matrix &f_x, Matrix &g_x, Matrix &differences)
{
    for (int i = 0; i < f_x.get_rows(); i++)
    {
        std::cout << "Row: " << i << ", Value " << f_x[i][X].value << ": " <<  f_x[i][Y].value << " - " << g_x[i][Y].value << std::endl;
        differences[i][X].value = f_x[i][X].value;
        differences[i][Y].value = f_x[i][Y].value - g_x[i][Y].value;
    }
}

void form_interpolated_g_x(Matrix &interpolated_table_g_x, Matrix &f_x, std::vector<double> interpolated_ys)
{
    for (int i = 0; i < f_x.get_rows(); i++)
    {
        interpolated_table_g_x[i][X].value = f_x[i][X].value;
        interpolated_table_g_x[i][Y].value = interpolated_ys[i];
    }
}

int newton_interpolate_degrees_ld(std::vector<LinkageDegree> vector_ld, double x, int rows_table, std::string filename)
{
    int exit_code = EXIT_SUCCESS;
    for (long unsigned i = 0; i < vector_ld.size() && !exit_code; i++)
    {
        Matrix newton_table_base(rows_table, vector_ld[i].newton_degree + 2);
        Matrix newton_table_interval(vector_ld[i].newton_degree + 1, vector_ld[i].newton_degree + 2);
        exit_code = file_parse_std(newton_table_base, filename);
        if (!exit_code)
        {
            compute_interval_std(newton_table_base, newton_table_interval, x, vector_ld[i].newton_degree);
            newton_init_vectors(newton_table_interval);
            newton_compute_vectors(newton_table_interval, vector_ld[i].newton_degree);
            newton_compute_values(newton_table_interval, vector_ld[i].newton_degree);
            double result = newton_interpolate(newton_table_interval, x, vector_ld[i].newton_degree);
            std::cout << "Степень: " << vector_ld[i].newton_degree << ", Результат: " << result << std::endl;
        }
    }
    return exit_code;
}

int newton_interpolate_degrees_lp(std::vector<LinkagePoint> vector_lp, double x, int rows_table, std::string filename)
{
    int exit_code = EXIT_SUCCESS;
    for (long unsigned i = 0; i < vector_lp.size() && !exit_code; i++)
    {
        Matrix newton_table_base(rows_table, vector_lp[i].newton_degree + 2);
        Matrix newton_table_interval(vector_lp[i].newton_degree + 1, vector_lp[i].newton_degree + 2);
        exit_code = file_parse_std(newton_table_base, filename);
        if (!exit_code)
        {
            compute_interval_std(newton_table_base, newton_table_interval, x, vector_lp[i].newton_degree);
            newton_init_vectors(newton_table_interval);
            newton_compute_vectors(newton_table_interval, vector_lp[i].newton_degree);
            newton_compute_values(newton_table_interval, vector_lp[i].newton_degree);
            double result = newton_interpolate(newton_table_interval, x, vector_lp[i].newton_degree);
            std::cout << "Степень: " << vector_lp[i].newton_degree << ", Результат: " << result << std::endl;
        }
    }
    return exit_code;
}
