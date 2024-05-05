#ifndef SLAE_H
#define SLAE_H

#include "polynomial.h"
#include "point.h"
#include <vector>
#include <stdexcept>
#include <cmath>

const double epsilon = 1e-9;

class Slae
{
    friend std::ostream &operator<<(std::ostream &out, Slae &slae);

    private:
        int rows_n;
        int cols_n;
        std::vector<Polynomial> system;
        std::vector<double> system_solution;
    public:
        Slae() = default;
        Slae(int equations_n, int coefs_n_param);

        int get_rows_n();
        int get_cols_n();
        
        double get_solution(int index) const; // check if need them in future
        void set_solution(int index, double value); // check if need them in future
        
        void row_echelon();
        bool is_row_echelon();
        void mult_add(int i, int j, double mult_factor);
        bool close_enough(double v1, double v2);

        void compute_init(std::vector<Point> &grid);

        Polynomial &operator[](int index);
        const Polynomial &operator[](int index) const;
};

#endif