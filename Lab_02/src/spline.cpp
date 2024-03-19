#include "spline.h"

Spline::Spline(Point &point_left_param, Point &point_right_param, int index_param) : point_left(point_left_param), point_right(point_right_param), index(index_param), xi(0), eta(0), coefficients(4, 0)
{
}

std::vector<double> &Spline::get_coefficients()
{
    return coefficients;
}

Point &Spline::get_point_left()
{
    return point_left;
}

Point &Spline::get_point_right()
{
    return point_right;
}

double Spline::get_h()
{
    return h;
}

double Spline::get_index()
{
    return index;
}

// Setters
void Spline::set_coefficients(std::vector<double> &coefficients_param)
{
    coefficients = coefficients_param;
}

void Spline::set_point_left(Point &point_left_param)
{
    point_left = point_left_param;
}

void Spline::set_point_right(Point &point_right_param)
{
    point_right = point_right_param;
}

void Spline::set_h(double h_param)
{
    h = h_param;
}

void Spline::set_index(int index_param)
{
    index = index_param;
}

// Algorithm

void Spline::set_a(double a_coef)
{
    coefficients[A] = a_coef;
}

void Spline::set_b(double b_coef)
{
    coefficients[B] = b_coef;
}

void Spline::set_c(double c_coef)
{
    coefficients[C] = c_coef;
}

void Spline::set_d(double d_coef)
{
    coefficients[D] = d_coef;
}

void Spline::compute_h(double x_left, double x_right)
{
    h = x_right - x_left;
}

// Operator Overloading

std::ostream &operator<<(std::ostream &out, Spline &spline)
{
    out << "I: " << spline.get_index() << " " << spline.get_point_left() << " " << spline.get_point_right() << "H: " << spline.get_h() << "; C: ";
    for (long unsigned int i = 0; i < spline.get_coefficients().size(); i++)
    {
        out << spline.get_coefficients()[i] << " ";
    }
    out << std::endl;
    return out;
}

// Splines

void splines_init_vector(std::vector<Spline> &splines, Matrix &table_src)
{
    for (int i = 0; i < (table_src.get_rows() - 1); i++)
    {
        Point l_point(table_src[i][0], table_src[i][1], i);
        Point r_point(table_src[i + 1][0], table_src[i + 1][1], i + 1);
        splines.push_back(Spline(l_point, r_point, i + 1));
    }
}

void splines_compute_h(std::vector<Spline> &splines)
{
    for (Spline &spline : splines)
    {
        spline.compute_h(spline.get_point_left().get_x(), spline.get_point_right().get_x());
    }
}

void splines_compute_a(std::vector<Spline> &splines)
{
    for (Spline &spline : splines)
    {
        spline.set_a(spline.get_point_left().get_y());
    }
}

void splines_compute_xi(std::vector<Spline> &splines)
{
    for (unsigned long int i = 2; i <= splines.size(); i++)
    {
        // TODO
    }
}

void splines_print(std::vector<Spline> &splines)
{
    for (Spline &spline : splines)
    {
        std::cout << spline;
    }
}
