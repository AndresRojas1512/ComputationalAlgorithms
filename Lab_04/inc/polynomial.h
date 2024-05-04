#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <stdexcept>

class Polynomial
{
    friend std::ostream &operator<<(std::ostream &out, Polynomial &Polynomial);

    private:
        std::vector<double> coefs;
    public:
        Polynomial() = default;
        explicit Polynomial(int n_coefs_param);

        int get_coefs_n();

        void set_coefs_n(int n);

        double &operator[](int index);
        const double &operator[](int index) const;
};

#endif