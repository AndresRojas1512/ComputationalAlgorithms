#ifndef SLAE_H
#define SLAE_H

#include "polynomial.h"
#include "point.h"
#include <vector>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

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
    Slae(const Slae &slae);

    Slae &operator=(const Slae &other);

    void compute_init_1v(std::vector<Point> &grid);
    void compute_init_2v(std::vector<Point> &grid, int n);

    void add_polynomial(Polynomial &polynomial);

    int get_rows_n();
    int get_cols_n();
    const std::vector<double> &get_system_solution() const;

    void lin_solve();
    Slae row_echelon();
    bool is_row_echelon();
    void mult_add(int i, int j, double mult_factor);
    bool close_enough(double v1, double v2);

    void fill_by_matrix(std::vector<std::vector<double>> &matrix);
    void write_solution_csv(const std::string &filename) const;


    Polynomial &operator[](int index);
    const Polynomial &operator[](int index) const;
};

std::ostream &operator<<(std::ostream &out, const std::vector<double> &system_solution);

int compute_nodes_2v(int degree);

#endif
