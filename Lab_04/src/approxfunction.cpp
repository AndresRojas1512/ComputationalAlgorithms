#include "approxfunction.h"

void compute_interval_x(std::pair<double, double> &interval, Table &table)
{
    double min_x = table[0][0];
    double max_x = table[0][0];
    for (int i = 1; i < table.get_rows(); ++i)
    {
        double x_value = table[i][0];
        if (x_value < min_x)
        {
            min_x = x_value;
        }
        if (x_value > max_x)
        {
            max_x = x_value;
        }
    }
    interval.first = min_x;
    interval.second = max_x;
}

void compute_interval_y(std::pair<double, double> &interval, Table &table)
{
    double min_y = table[0][1];
    double max_y = table[0][1];

    for (int i = 1; i < table.get_rows(); ++i)
    {
        double y_value = table[i][1];
        if (y_value < min_y)
        {
            min_y = y_value;
        }
        if (y_value > max_y)
        {
            max_y = y_value;
        }
    }
    interval.first = min_y;
    interval.second = max_y;
}

void compute_approxfunction_2d(const std::vector<double> &system_solution, Table &table, const std::pair<double, double> &interval, int x_steps)
{
    double step = (interval.second - interval.first) / x_steps;
    if (std::abs(step) < epsilon)
        step = 0.1;

    double x_cur = interval.first;
    while (x_cur <= interval.second + step)
    {
        double y_cur = 0;
        for (size_t i = 0; i < system_solution.size(); i++)
        {
            y_cur += system_solution[i] * std::pow(x_cur, i);
        }
        table.append(std::vector<double>{x_cur, y_cur});
        x_cur += step;
    }
}

void compute_approxfunction_3d(const std::vector<double> &system_solution, Table &table, const std::pair<double, double> &x_interval, const std::pair<double, double> &y_interval, int x_steps, int y_steps)
{
    double x_step = (x_interval.second - x_interval.first) / x_steps;
    double y_step = (y_interval.second - y_interval.first) / y_steps;

    for (int i = 0; i <= x_steps; ++i)
    {
        double x_cur = x_interval.first + i * x_step;
        for (int j = 0; j <= y_steps; ++j)
        {
            double y_cur = y_interval.first + j * y_step;
            double z_cur = 0;

            for (size_t k = 0; k < system_solution.size(); k++)
            {
                z_cur += system_solution[k] * std::pow(x_cur, k) * std::pow(y_cur, k);  // Simplified; adjust as needed!
            }
            table.append({x_cur, y_cur, z_cur});
        }
    }
}
