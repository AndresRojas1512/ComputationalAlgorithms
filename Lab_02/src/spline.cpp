#include "spline.h"

Spline::Spline(Point &point_left_param, Point &point_right_param, int index_param) : point_left(point_left_param), point_right(point_right_param), index(index_param), xi(0), eta(0), coefficients(4, 0)
{
}

// Getters

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

double Spline::get_xi()
{
    return xi;
}

double Spline::get_eta()
{
    return eta;
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

void Spline::set_a(double a_coef)
{
    coefficients[A_idx] = a_coef;
}

void Spline::set_b(double b_coef)
{
    coefficients[B_idx] = b_coef;
}

void Spline::set_c(double c_coef)
{
    coefficients[C_idx] = c_coef;
}

void Spline::set_d(double d_coef)
{
    coefficients[D_idx] = d_coef;
}

void Spline::set_xi(double xi_param)
{
    xi = xi_param;
}

void Spline::set_eta(double eta_param)
{
    eta = eta_param;
}

// Algorithm

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
    splines[1].set_xi(0);
    for (unsigned long int i = 1; i < splines.size(); i++)
    {
        double Di = splines[i].get_h();
        double Bi = -2 * (splines[i - 1].get_h() + splines[i].get_h());
        double Ai = splines[i - 1].get_h();
        double xi = Di / (Bi - (Ai * splines[i].get_xi()));
        splines[i + 1].set_xi(xi);
    }
}

void splines_compute_eta(std::vector<Spline> &splines)
{
    splines[1].set_eta(0);
    for (unsigned long int i = 1; i < splines.size(); i++)
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
