#ifndef SPLINE_H
#define SPLINE_H

#include <iostream>
#include <vector>
#include "matrix.h"
#include "point.h"

#define A_idx 0
#define B_idx 1
#define C_idx 2
#define D_idx 3

class Spline
{
    private:
        Point point_left;
        Point point_right;
        int index;
        double h;
        double xi;
        double eta;
        std::vector<double> coefficients;
    public:
        friend std::ostream &operator<<(std::ostream &out, Spline &spline);

        Spline(Point &point_left_param, Point &point_right_param, int index_param);

        // Getters
        std::vector<double> &get_coefficients();
        Point &get_point_left();
        Point &get_point_right();
        double get_h();
        double get_index();
        double get_xi();
        double get_eta();
        double get_a();
        double get_b();
        double get_c();
        double get_d();

        // Setters
        void set_coefficients(std::vector<double> &coefficients_param);
        void set_point_left(Point &point_left_param);
        void set_point_right(Point &point_right_param);
        void set_h(double h_param);
        void set_index(int index_param);
        void set_a(double a_coef);
        void set_b(double b_coef);
        void set_c(double c_coef);
        void set_d(double d_coef);
        void set_xi(double xi_param);
        void set_eta(double eta_param);

        // Algorithm
        void compute_h(double x_left, double x_right);

        // Print
        void print_xi_eta();
};

void splines_init_vector(std::vector<Spline> &splines, Matrix &table_src);

void splines_print(std::vector<Spline> &splines);

void splines_compute_a(std::vector<Spline> &splines);

void splines_compute_b(std::vector<Spline> &splines);

void splines_compute_bn(std::vector<Spline> &splines);

void splines_compute_c(std::vector<Spline> &splines);

void splines_compute_d(std::vector<Spline> &splines);

void splines_compute_h(std::vector<Spline> &splines);

void splines_compute_xi(std::vector<Spline> &splines);

void splines_compute_eta(std::vector<Spline> &splines);

void splines_print_xi_eta(std::vector<Spline> &splines);

#endif
