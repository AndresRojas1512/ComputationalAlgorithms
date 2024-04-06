#include "interpolatemd.h"

double newton_linear(Matrix &newton_table, double x, int nx)
{
    newton_init_vectors(newton_table);
    newton_compute_vectors(newton_table, nx);
    newton_compute_values(newton_table, nx);
    double result = newton_interpolate(newton_table, x, nx);
    return result;
}

// double newton_bilinear(double x, double y, int nx)
// {
//     double result;
//     return result;
// }

// double newton_trilinear()
// {
//     double result;
//     return result;
// }
