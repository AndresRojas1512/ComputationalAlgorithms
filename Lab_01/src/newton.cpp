#include "newton.h"

#define X 0
#define Y 1

void compute_divided_differences(Matrix &table, int n)
{
    for (int col = 2; col < (n + 2); col++)
    {
        for (int row = 0; row < n; row++)
        {
            double dividend = table[row + 1][col - 1] - table[row][col - 1];
            table[row][col] = dividend;
        }
    }
}
