#include "approxfunction.h"

void compute_interval(std::pair<double, double> &interval, Table &table)
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

void compute_approxfunction(const std::vector<double> &system_solution, Table &table, const std::pair<double, double> &interval)
{
    double step = (interval.second - interval.first) / 1000.0;
    if (std::abs(step) < epsilon)
        step = 0.1;

    double x_cur = interval.first;
    while (x_cur <= interval.second)
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
