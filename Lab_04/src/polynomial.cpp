#include "polynomial.h"

Polynomial::Polynomial(int coefs_n_param) : coefs(coefs_n_param, 0.0)
{
}

int Polynomial::get_coefs_n()
{
    return coefs.size();
}

void Polynomial::set_coefs_n(int coefs_n_param)
{
    coefs.resize(coefs_n_param, 0.0);
}

double &Polynomial::operator[](int index)
{
    if (index < 0 || index >= static_cast<int>(coefs.size()))
        throw std::out_of_range("Index out of range");
    return coefs[index];
}
const double &Polynomial::operator[](int index) const
{
    if (index < 0 || index >= static_cast<int>(coefs.size()))
        throw std::out_of_range("Index out of range");
    return coefs[index];
}

std::ostream &operator<<(std::ostream &out, Polynomial &polynomial)
{
    for (auto &coef : polynomial.coefs)
        out << coef << " ";
    return out;
}
