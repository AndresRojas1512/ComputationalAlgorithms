#include "interpolatemd.h"

double newton_linear(double x, int nx, std::vector<double> &x_vals, std::vector<double> &y_vals) // done
{
    int cols = x_vals.size();
    Matrix newton_table(cols, nx + 2);
    Matrix newton_table_interval(nx + 1, nx + 2);
    newton_init_from_vectors(newton_table, x_vals, y_vals);
    compute_interval_std(newton_table, newton_table_interval, x, nx);
    newton_init_vectors(newton_table_interval);
    newton_compute_vectors(newton_table_interval, nx);
    newton_compute_values(newton_table_interval, nx);
    double result = newton_interpolate(newton_table_interval, x, nx);
    return result;
}

double newton_bilinear(double x, double y, int nx, int ny, Layer &layer)
{
    std::vector<double> results;
    double result_iter;
    for (unsigned int i = 0; i < layer.y_vals.size(); i++)
    {
        result_iter = newton_linear(x, nx, layer.x_vals, layer.data[i]);
        results.push_back(result_iter);
    }
    double result = newton_linear(y, ny, layer.y_vals, results);
    return result;
}

double newton_trilinear(double x, double y, double z, int nx, int ny, int nz, Table &table)
{
    std::vector<double> results;
    double result_iter;
    for (unsigned long int i = 0; i < table.layers.size(); i++)
    {
        result_iter = newton_bilinear(x, y, nx, ny, table.layers[i]);
        results.push_back(result_iter);
    }
    double result = newton_linear(z, nz, table.z_vals, results);
    return result;
}
