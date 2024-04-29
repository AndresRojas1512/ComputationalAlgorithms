#include "interpolatemd.h"

// NEWTON

double newton_linear(double x, int nx, std::vector<double> &x_vals, std::vector<double> &y_vals)
{
    // Debug
    // std::cout << "\tLinear:" << std::endl;
    // std::cout << "X: ";
    // vector_print(x_vals);
    // std::cout << "Y: ";
    // vector_print(y_vals);
    // End debug
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
    // Debug
    // std::cout << "\tBilinear:" << std::endl;
    // std::cout << "Layer:" << std::endl;
    // std::cout << layer;
    // End debug
    std::vector<double> results;
    double result_iter;
    for (unsigned int i = 0; i < layer.y_vals.size(); i++)
    {
        // std::cout << "Linear iter: " << i << std::endl;
        result_iter = newton_linear(x, nx, layer.x_vals, layer.data[i]);
        results.push_back(result_iter);
    }
    // Debug
    // std::cout << "Inter after cycle in 2d:" << std::endl;
    // End debug
    double result = newton_linear(y, ny, layer.y_vals, results);
    return result;
}

double newton_trilinear(double x, double y, double z, int nx, int ny, int nz, Table &table)
{
    // Debug
    // std::cout << "\tTrilinear:" << std::endl;
    // std::cout << "Table:" << std::endl;
    // std::cout << table;
    // End debug
    std::vector<double> results;
    double result_iter;
    for (unsigned long int i = 0; i < table.layers.size(); i++)
    {
        result_iter = newton_bilinear(x, y, nx, ny, table.layers[i]);
        results.push_back(result_iter);
    }
    // Debug
    // std::cout << "Inter after cycle in 3d:" << std::endl;
    // End debug
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

void compute_vector_configuration(std::vector<double> &in_values, std::vector<double> &out_values, std::vector<int> &out_indices,double x, int n)
{
    n += 1;
    int rows = in_values.size();
    int best_start_index = 0;
    double min_diff = std::numeric_limits<double>::max();
    bool found_in_range = false;

    for (int i = 0; i <= rows - n; ++i)
    {
        double left_value = in_values[i];
        double right_value = in_values[i + n - 1];

        if (left_value <= x && x <= right_value)
        {
            double diff = std::abs((right_value - left_value) / 2 + left_value - x);
            if (!found_in_range || diff < min_diff)
            {
                min_diff = diff;
                best_start_index = i;
                found_in_range = true;
            }
        }
        else if (!found_in_range)
        {
            double diff = x < left_value ? left_value - x : x - right_value;
            if (diff < min_diff)
            {
                min_diff = diff;
                best_start_index = i;
            }
        }
    }
    out_values.clear();
    for (int i = 0; i < n; i++)
    {
        out_values.push_back(in_values[best_start_index + i]);
        out_indices.push_back(best_start_index + i);
    }
}

void compute_table_configuration(Table &input_table, Table &output_table, double x, double y, double z, int nx, int ny, int nz)
{
    std::vector<int> z_indices;
    std::vector<double> z_config;
    compute_vector_configuration(input_table.z_vals, z_config, z_indices, z, nz);

    for (int z_index : z_indices)
    {
        Layer selected_layer = input_table.layers[z_index];

        std::vector<double> x_config, y_config;
        std::vector<int> x_indices, y_indices;
        compute_vector_configuration(selected_layer.x_vals, x_config, x_indices, x, nx);
        compute_vector_configuration(selected_layer.y_vals, y_config, y_indices, y, ny);

        Layer new_layer;
        new_layer.z = selected_layer.z;
        new_layer.x_vals = x_config;
        new_layer.y_vals = y_config;

        new_layer.data.resize(y_config.size());
        for (size_t i = 0; i < y_config.size(); ++i)
        {
            new_layer.data[i].resize(x_config.size());
            for (size_t j = 0; j < x_config.size(); ++j)
            {
                int x_index = std::find(selected_layer.x_vals.begin(), selected_layer.x_vals.end(), x_config[j]) - selected_layer.x_vals.begin();
                int y_index = std::find(selected_layer.y_vals.begin(), selected_layer.y_vals.end(), y_config[i]) - selected_layer.y_vals.begin();
                new_layer.data[i][j] = selected_layer.data[y_index][x_index];
            }
        }
        output_table.addLayer(new_layer);
        output_table.z_vals.push_back(new_layer.z);
    }
}