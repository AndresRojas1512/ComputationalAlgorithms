#include "spline.h"

void spline_comput_vector_indices(std::vector<Cell> &steps, int splines_n)
{
    for (int i = 0; i < splines_n; i++)
    {
        steps[i].index = i + 1;
    }
}
void spline_compute_steps(std::vector<Cell> &steps, Matrix &table_src, int splines_n)
{
    int exit_code = EXIT_SUCCESS;
    for (int i = 0; i < splines_n; i++)
    {
        double step = table_src[i + 1][X].value - table_src[i][X].value;
        steps.push_back(Cell());
    }
}

void spline_vector_print_values(const std::vector<Cell> &vector)
{
    for (const Cell &elem : vector)
    {
        // TODO
    }
    std::cout << std::endl;
}

void spline_coefs_init(Matrix &splines_coefs)
{
    int index = 1;
    for (int i = 0; i < splines_coefs.get_rows(); i++)
    {
        for (int j = 0; j < splines_coefs.get_cols(); j++)
        {
            splines_coefs[i][j] = index;
        }
    }
}