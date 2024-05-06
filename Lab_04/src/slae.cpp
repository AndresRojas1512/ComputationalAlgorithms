#include "slae.h"

Slae::Slae(int equations_n_param, int coefs_n_param) : rows_n(equations_n_param), cols_n(coefs_n_param), system(equations_n_param, Polynomial(coefs_n_param)), system_solution(equations_n_param, 0.0)
{
}

Slae::Slae(const Slae &other) : rows_n(other.rows_n), cols_n(other.cols_n), system(other.system), system_solution(other.system_solution)
{
}

Slae &Slae::operator=(const Slae &other)
{
    if (this == &other)
        return *this;
    rows_n = other.rows_n;
    cols_n = other.cols_n;
    system = other.system;
    system_solution = other.system_solution;
    return *this;
}

int Slae::get_rows_n()
{
    return rows_n;
}

int Slae::get_cols_n()
{
    return cols_n;
}

const std::vector<double>& Slae::get_system_solution() const
{
    return system_solution;
}

void Slae::compute_init_1v(std::vector<Point> &grid)
{
    double cumulative_sum = 0.0;
    for (int i = 0; i < rows_n; i++)
    {
        for (int j = 0; j < cols_n; j++)
        {
            cumulative_sum = 0.0;
            for (auto &point : grid)
            {
                cumulative_sum += point.get_weight() * std::pow(point.get_x(), i + j);
            }
            system[i][j] = cumulative_sum;
        }
        cumulative_sum = 0.0;
        for (auto &point : grid)
        {
            cumulative_sum += point.get_weight() * point.get_y() * std::pow(point.get_x(), i);
        }
        system[i][system.size()] = cumulative_sum;
    }
}

double getValue_2D(double x, double y, int i, int j)
{
    return std::pow(x, i) * std::pow(y, j);
}

void Slae::compute_init_2v(std::vector<Point> &grid, int n)
{
    std::vector<std::vector<double>> A;
    std::vector<double> B;
    for (int i = 0; i < (n + 1); i++)
    {
        for (int j = 0; j < (n + 1 - i); j++)
        {
            std::vector<double> cur_row;
            for (int k = 0; k < (n + 1); k++)
            {
                for (int l = 0; l < (n + 1 - k); l++)
                {
                    double cumulative_sum_a = 0.0;
                    for (auto &point : grid)
                    {
                        double x = point.get_x();
                        double y = point.get_y();
                        double weight = point.get_weight();
                        cumulative_sum_a += getValue_2D(x, y, k + i, l + j) * weight;
                    }
                    cur_row.push_back(cumulative_sum_a);
                }
            }
            A.push_back(cur_row);
            double cumulative_sum_b = 0.0;
            for (auto &point : grid)
            {
                double x = point.get_x();
                double y = point.get_y();
                double z = point.get_z();
                double weight = point.get_weight();
                cumulative_sum_b += getValue_2D(x, y, i, j) * z * weight;
            }
            B.push_back(cumulative_sum_b);
        }
    }
    for (unsigned int i = 0; i < A.size(); i++)
    {
        A[i].push_back(B[i]);
    }
    for (unsigned int i = 0; i < A.size(); i++)
    {
        for (unsigned int j = 0; j < A[0].size(); j++)
        {
            system[i][j] = A[i][j];
        }
    }
}

void Slae::lin_solve()
{
    Slae row_echelon_matrix = this->row_echelon();
    int num_rows = row_echelon_matrix.get_rows_n();
    int num_cols = row_echelon_matrix.get_cols_n();
    int start_row = num_rows - 1;
    for (int i = start_row; i >= 0; i--)
    {
        double current_result = row_echelon_matrix[i][num_cols - 1];
        double cumulative_sum = 0.0;
        for (int j = i + 1; j < num_rows; j++)
        {
            cumulative_sum += row_echelon_matrix[i][j] * system_solution[j];
        }
        double final_answer = (current_result - cumulative_sum) / row_echelon_matrix[i][i];
        system_solution[i] = final_answer;
    }
}

Slae Slae::row_echelon()
{
    Slae row_echelon(*this);

    int c_row, c_col;
    int max_count = 100000;
    int count = 0;
    bool complete_flag = false;
    while ((!complete_flag) && (count < max_count))
    {
        for (int diag_index = 0; diag_index < row_echelon.rows_n; diag_index++)
        {
            c_row = diag_index;
            c_col = diag_index;

            for (int row_index = c_row + 1; row_index < row_echelon.rows_n; row_index++)
            {
                if (!(close_enough(row_echelon.system[row_index][c_col], 0.0)))
                 {
                    int row_one_index = c_col;
                    double current_element_value = row_echelon.system[row_index][c_col];
                    double row_one_value = row_echelon.system[row_one_index][c_col];
                    if (!(close_enough(row_one_value, 0.0)))
                    {
                        double correction_factor = - (current_element_value / row_one_value);
                        row_echelon.mult_add(row_index, row_one_index, correction_factor);
                    }
                }
            }
        }
        complete_flag = row_echelon.is_row_echelon();
        count++;
    }
    return row_echelon;
}

void Slae::mult_add(int i, int j, double mult_factor)
{
    for (int k = 0; k < cols_n; k++)
        system[i][k] += system[j][k] * mult_factor;
}

bool Slae::is_row_echelon()
{
    double cumulative_sum = 0.0;
    for (int i = 1; i < rows_n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            cumulative_sum += system[i][j];
        }
    }
    return cumulative_sum < epsilon;
}

bool Slae::close_enough(double v1, double v2)
{
    return fabs(v1 - v2) < epsilon;
}

std::ostream &operator<<(std::ostream &out, Slae &slae)
{
    for (auto &polynomial : slae.system)
        out << polynomial << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const std::vector<double> &system_solution)
{
    for (const auto &value : system_solution)
        out << value << " ";
    return out;
}

Polynomial &Slae::operator[](int index)
{
    if (index < 0 || index >= static_cast<int>(system.size()))
        throw std::out_of_range("Polynomial index out of range");
    return system[index];
}

const Polynomial &Slae::operator[](int index) const
{
    if (index < 0 || index >= static_cast<int>(system.size()))
        throw std::out_of_range("Polynomial index out of range");
    return system[index];
}

int compute_nodes_2v(int degree)
{
    return ((degree + 1) * (degree + 2)) / 2;
}