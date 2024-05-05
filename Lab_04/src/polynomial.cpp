#include "polynomial.h"

Polynomial::Polynomial(int coefs_n_param) : coefs_n(coefs_n_param), coefs(coefs_n_param, 0.0)
{
}

int Polynomial::get_coefs_n()
{
    return coefs_n;
}

double &Polynomial::operator[](int index)
{
    if (index < 0 || index >= coefs_n)
        throw std::out_of_range("Polynomial index out of range");
    return coefs[index];
}
const double &Polynomial::operator[](int index) const
{
    if (index < 0 || index >= coefs_n)
        throw std::out_of_range("Polynomial index out of range");
    return coefs[index];
}

std::ostream &operator<<(std::ostream &out, Polynomial &polynomial)
{
    for (auto &coef : polynomial.coefs)
        out << coef << " ";
    return out;
}
