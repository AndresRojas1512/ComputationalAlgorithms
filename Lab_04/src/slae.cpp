#include "slae.h"

Slae::Slae(int equations_n) : system(equations_n), system_solution(equations_n)
{
}

Slae::Slae(int equations_n, int coefs_n_param) : system(equations_n, Polynomial(coefs_n_param)), system_solution(equations_n)
{
}

int Slae::get_equations_n()
{
    return system.size();
}

void Slae::set_equations_n(int equations_n_param)
{
    system.resize(equations_n_param);
}

double Slae::get_solution(int index) const
{
    if (index < 0 || index >= static_cast<int>(system_solution.size()))
        throw std::out_of_range("Solution index out of range");
    return system_solution[index];
}
void Slae::set_solution(int index, double value)
{
    if (index < 0 || index >= static_cast<int>(system_solution.size()))
        throw std::out_of_range("Solution index out of range");
    system_solution[index] = value;
}

std::ostream &operator<<(std::ostream &out, Slae &slae)
{
    for (auto &polynomial : slae.system)
        out << polynomial << std::endl;
    return out;
}

Polynomial &Slae::operator[](int index)
{
    if (index < 0 || index >= static_cast<int>(system.size()))
        throw std::out_of_range("Polynomial index out of range");
    return system[index];
}

const Polynomial &Slae::operator[](int index) const
{
    if (index < 0 || index >= static_cast<int>(system.size()))
        throw std::out_of_range("Polynomial index out of range");
    return system[index];
}
