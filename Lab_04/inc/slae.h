#ifndef SLAE_H
#define SLAE_H

#include "polynomial.h"
#include <vector>
#include <stdexcept>

class Slae
{
    friend std::ostream &operator<<(std::ostream &out, Slae &slae);

    private:
        std::vector<Polynomial> system;
        std::vector<double> system_solution;
    public:
        Slae() = default;
        explicit Slae(int equations_n);
        Slae(int equations_n, int coefs_n_param);

        int get_equations_n();

        void set_equations_n(int equations_n_param);

        double get_solution(int index) const;
        void set_solution(int index, double value);

        Polynomial &operator[](int index);
        const Polynomial &operator[](int index) const;
};

#endif