#include "slae.h"

Slae::Slae(int equations_n_param, int coefs_n_param) : rows_n(equations_n_param), cols_n(coefs_n_param), system(equations_n_param, Polynomial(coefs_n_param)), system_solution(equations_n_param)
{
}

int Slae::get_rows_n()
{
    return rows_n;
}

int Slae::get_cols_n()
{
    return cols_n;
}

double Slae::get_solution(int index) const
{
    if (index < 0 || index >= rows_n)
        throw std::out_of_range("Solution index out of range");
    return system_solution[index];
}
void Slae::set_solution(int index, double value)
{
    if (index < 0 || index >= rows_n)
        throw std::out_of_range("Solution index out of range");
    system_solution[index] = value;
}

void Slae::compute_init(std::vector<Point> &grid)
{
    double sum = 0.0;
    for (int i = 0; i < rows_n; i++)
    {
        for (int j = 0; j < cols_n; j++)
        {
            sum = 0.0;
            for (auto &point : grid)
            {
                sum += point.get_weight() * std::pow(point.get_x(), i + j);
            }
            system[i][j] = sum;
        }
        sum = 0;
        for (auto &point : grid)
        {
            sum += point.get_weight() * point.get_y() * std::pow(point.get_x(), i);
        }
        system[i][system.size()] = sum;
    }
}

void Slae::row_echelon() // done
{
    int c_row, c_col;
    int max_count = 100;
    int count = 0;
    bool complete_flag = false;
    while ((!complete_flag) && (count < max_count))
    {
        for (int diag_index = 0; diag_index < rows_n; diag_index++)
        {
            c_row = diag_index;
            c_col = diag_index;

            for (int row_index = c_row + 1; row_index < rows_n; row_index++)
            {
                if (!(close_enough(system[row_index][c_col], 0.0)))
                 {
                    int row_one_index = c_col;
                    double current_element_value = system[row_index][c_col];
                    double row_one_value = system[row_one_index][c_col];
                    if (!(close_enough(row_one_value, 0.0)))
                    {
                        double correction_factor = - (current_element_value / row_one_value);
                        mult_add(row_index, row_one_index, correction_factor);
                    }
                }
            }
        }
        complete_flag = this->is_row_echelon();
        count++;
    }
}

void Slae::mult_add(int i, int j, double mult_factor) // done
{
    for (int k = 0; k < cols_n; k++)
        system[i][k] += system[j][k] * mult_factor;
}

bool Slae::is_row_echelon() // done
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

bool Slae::close_enough(double v1, double v2) // done
{
    return fabs(v1 - v2) < epsilon;
}

std::ostream &operator<<(std::ostream &out, Slae &slae)
{
    for (auto &polynomial : slae.system)
        out << polynomial << std::endl;
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
