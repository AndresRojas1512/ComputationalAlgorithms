#include "interpolatemd.h"

// NEWTON

double newton_linear(double x, int nx, std::vector<double> &x_vals, std::vector<double> &y_vals)
{
    int rows = x_vals.size();
    Matrix newton_table(rows, nx + 2);
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

// SPLINE

double spline_linear(double x, std::vector<double> &x_vals, std::vector<double> &y_vals)
{
    int spline_index;
    int rows = x_vals.size();
    Matrix table_src(rows, 2);
    std::vector<Spline> splines;
    newton_init_from_vectors(table_src, x_vals, y_vals);
    splines_init_vector(splines, table_src);
    splines_compute_h(splines);
    splines_compute_a(splines);
    splines_compute_xi(splines, 0);
    splines_compute_eta(splines, 0);
    splines_compute_c(splines, 0, 0);
    splines_compute_b(splines);
    splines_compute_bn(splines);
    splines_compute_d(splines);
    splines_compute_dn(splines);
    spline_find(splines, x, spline_index);
    double result = splines[spline_index].spline_interpolate(x);
    return result;
}

double spline_bilinear(double x, double y, Layer &layer)
{
    std::vector<double> results;
    double result_iter;
    for (unsigned int i = 0; i < layer.y_vals.size(); i++)
    {
        result_iter = spline_linear(x, layer.x_vals, layer.data[i]);
        results.push_back(result_iter);
    }
    double result = spline_linear(y, layer.y_vals, results);
    return result;
}

double spline_trilinear(double x, double y, double z, Table &table)
{
    std::vector<double> results;
    double result_iter;
    for (unsigned long int i = 0; i < table.layers.size(); i++)
    {
        result_iter = spline_bilinear(x, y, table.layers[i]);
        results.push_back(result_iter);
    }
    double result = spline_linear(z, table.z_vals, results);
    return result;
}

// MIXED

double mixed_bilinear(double x, double y, int nx, int ny, Layer &layer)
{
    std::vector<double> results;
    double result_iter;
    for (unsigned int i = 0; i < layer.y_vals.size(); i++)
    {
        result_iter = newton_linear(x, nx, layer.x_vals, layer.data[i]);
        // result_iter = spline_linear(x, layer.x_vals, layer.data[i]);
        results.push_back(result_iter);
    }
    double result = spline_linear(y, layer.y_vals, results);
    // double result = newton_linear(y, ny, layer.y_vals, results);
    return result;
}

double mixed_trilinear(double x, double y, double z, int nx, int ny, int nz, Table &table)
{
    std::vector<double> results;
    double result_iter;
    for (unsigned long int i = 0; i < table.layers.size(); i++)
    {
        result_iter = mixed_bilinear(x, y, nx, ny, table.layers[i]);
        results.push_back(result_iter);
    }
    double result = spline_linear(z, table.z_vals, results);
    // double result = newton_linear(z, nz, table.z_vals, results);
    return result;
}
