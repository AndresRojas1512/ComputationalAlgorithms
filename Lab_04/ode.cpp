#include "ode.h"

double ODESolution(double x)
{
    const double e = std::exp(1.0);
    double numerator = -(std::exp(0.5) + 1);
    double denominator = boost::math::erf_inv(1.0 / std::sqrt(2.0));

    double term1 = numerator / denominator;
    double term2 = boost::math::erf_inv(x / std::sqrt(2.0));
    double result = (term1 * term2 + 1) / std::exp(x * x / 2.0) + x;

    return result;
}

void GetApproximateODE(Slae &slae, const std::vector<double> &xs, int n, const std::vector<Func>& funcs, const std::vector<Func>& coeffFuncs)
{
    // Ignore the first function
    std::vector<Func> coeffFuncsValid;
    for (unsigned int i = 1; i < coeffFuncs.size(); i++)
        coeffFuncsValid.push_back(coeffFuncs[i]);

    std::vector<std::vector<double>> A;
    std::vector<double> B;

    for (auto &func_01 : coeffFuncsValid)
    {
        std::vector<double> cur_row;
        for (auto &func_02 : coeffFuncsValid)
        {
            double cumulative_sum = 0.0;
            for (auto &x : xs)
            {
                cumulative_sum += func_01(x) * func_02(x);
            }
            cur_row.push_back(cumulative_sum);
        }
        A.push_back(cur_row);
    }

    Func firstFunc = coeffFuncs[0];
    for (auto &func : coeffFuncsValid)
    {
        double cumulative_sum = 0.0;
        for (auto &x : xs)
        {
            cumulative_sum -= firstFunc(x) * func(x);
        }
        B.push_back(cumulative_sum);
    }

    // Get the full Slae in A
    for (unsigned int i = 0; i < A.size(); i++)
    {
        A[i].push_back(B[i]);
    }
    slae.fill_by_matrix(A);
}
