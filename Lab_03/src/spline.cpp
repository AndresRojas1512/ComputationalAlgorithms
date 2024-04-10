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

double Spline::get_a()
{
    return coefficients[0];
}

double Spline::get_b()
{
    return coefficients[1];
}

double Spline::get_c()
{
    return coefficients[2];
}

double Spline::get_d()
{
    return coefficients[3];
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

void Spline::compute_h(double x_left, double x_right) // DONE
{
    h = x_right - x_left;
}

// Printers

void Spline::print_xi_eta()
{
    std::cout << "XI: " << xi << ", ETA: " << eta;
}

// Operator Overloading

std::ostream &operator<<(std::ostream &out, Spline &spline)
{
    out << "I:" << spline.get_index() << " " << spline.get_point_left() << "-" << spline.get_point_right() << " H:" << spline.get_h() << " XI:" << spline.get_xi() << " ETA:" << spline.get_eta() << " Coeffs:";
    for (long unsigned int i = 0; i < spline.get_coefficients().size(); i++)
    {
        out << spline.get_coefficients()[i] << " ";
    }
    out << std::endl;
    return out;
}

// Splines

void splines_init_vector(std::vector<Spline> &splines, Matrix &table_src) // DONE
{
    for (int i = 0; i < (table_src.get_rows() - 1); i++)
    {
        Point l_point(table_src[i][0].value, table_src[i][1].value, i);
        Point r_point(table_src[i + 1][0].value, table_src[i + 1][1].value, i + 1);
        splines.push_back(Spline(l_point, r_point, i + 1));
    }
}

void splines_compute_h(std::vector<Spline> &splines) // DONE
{
    for (Spline &spline : splines)
    {
        spline.compute_h(spline.get_point_left().get_x(), spline.get_point_right().get_x());
    }
}

void splines_compute_a(std::vector<Spline> &splines) // DONE
{
    for (Spline &spline : splines)
    {
        spline.set_a(spline.get_point_left().get_y());
    }
}

void splines_compute_b(std::vector<Spline> &splines) // DONE
{
    for (unsigned long int i = 0; i < (splines.size() - 1); i++)
    {
        double bi = ((splines[i].get_point_right().get_y() - splines[i].get_point_left().get_y()) / splines[i].get_h()) - 1/3 * splines[i].get_h() * (splines[i + 1].get_c() + 2 * splines[i].get_c());
        splines[i].set_b(bi);
    }
}

void splines_compute_bn(std::vector<Spline> &splines) // DONE
{
    double bn = ((splines[splines.size() - 1].get_point_right().get_y() - splines[splines.size() - 1].get_point_left().get_y()) / splines[splines.size() - 1].get_h()) - (2/3 * splines[splines.size() - 1].get_h() * splines[splines.size() - 1].get_c());
    splines[splines.size() - 1].set_b(bn);
}

void splines_compute_c(std::vector<Spline> &splines, double boundary_x0, double boundary_xN)
{
    double c1 = boundary_x0 / 2;
    double cNplus1 = boundary_xN / 2;
    // Compute c
    splines[0].set_c(c1);
    for (int i = (int)(splines.size() - 1); i >= 0; i--)
    {
        if (i == (int)(splines.size() - 1))
        {
            // Xi_i+1 (overflow)
            double Di = splines[i].get_h();
            double Bi = - ((2 * splines[i - 1].get_h()) + splines[i].get_h());
            double Ai = splines[i - 1].get_h();
            double xi_ovflow_spline = Di / (Bi - (Ai * splines[i].get_xi()));

            // Eta_i+1 (overflow)
            double Fi = 3 * (((splines[i].get_point_right().get_y() - splines[i - 1].get_point_right().get_y()) / splines[i].get_h()) - ((splines[i - 1].get_point_right().get_y() - splines[i - 1].get_point_left().get_y()) / splines[i - 1].get_h()));
            double eta_ovflow_spline = ((Fi + (Ai * splines[i].get_eta())) / (Bi - (Ai * splines[i].get_xi())));

            // Compute Ui (using overflow)
            double Ui = (xi_ovflow_spline * cNplus1) + eta_ovflow_spline;
            splines[i].set_c(Ui);
        }
        else
        {
            double Ui = (splines[i + 1].get_xi() * splines[i + 1].get_c()) + splines[i + 1].get_eta();
            splines[i].set_c(Ui);
        }
    }
}

void splines_compute_d(std::vector<Spline> &splines) // DONE
{
    for (long unsigned int i = 0; i < (splines.size() - 1); i++)
    {
        double di = (splines[i + 1].get_c() - splines[i].get_c()) / (3 * splines[i].get_h());
        splines[i].set_d(di);
    }
}

void splines_compute_dn(std::vector<Spline> &splines) // DONE
{
    double dn = - (splines[splines.size() - 1].get_c() / (3 * splines[splines.size() - 1].get_h()));
    splines[splines.size() - 1].set_d(dn);
}

void splines_compute_xi(std::vector<Spline> &splines, double boundary_condition) // DONE
{
    splines[1].set_xi(boundary_condition / 2);
    for (unsigned long int i = 1; i < (splines.size() - 1); i++)
    {
        double Di = splines[i].get_h();
        double Bi = - ((2 * splines[i - 1].get_h()) + splines[i].get_h());
        double Ai = splines[i - 1].get_h();
        double xi = Di / (Bi - (Ai * splines[i].get_xi()));
        splines[i + 1].set_xi(xi);
    }
}

void splines_compute_eta(std::vector<Spline> &splines, double boundary_condition) // DONE
{
    splines[1].set_eta(boundary_condition / 2);
    for (unsigned long int i = 1; i < (splines.size() - 1); i++)
    {
        double Fi = 3 * (((splines[i].get_point_right().get_y() - splines[i - 1].get_point_right().get_y()) / splines[i].get_h()) - ((splines[i - 1].get_point_right().get_y() - splines[i - 1].get_point_left().get_y()) / splines[i - 1].get_h()));
        double Ai = splines[i - 1].get_h();
        double Bi = - ((2 * splines[i - 1].get_h()) + splines[i].get_h());
        double eta = ((Fi + (Ai * splines[i].get_eta())) / (Bi - (Ai * splines[i].get_xi())));
        splines[i + 1].set_eta(eta);
    }
}

double Spline::spline_interpolate(double x)
{
    double y = coefficients[0] + coefficients[1] * (x - point_left.get_x()) + coefficients[2] * std::pow(x - point_left.get_x(), 2) * coefficients[3] * std::pow(x - point_left.get_x(), 3);
    return y;
}

void splines_print(std::vector<Spline> &splines)
{
    for (Spline &spline : splines)
    {
        std::cout << spline;
    }
}

void splines_print_xi_eta(std::vector<Spline> &splines)
{
    for (Spline &spline : splines)
    {
        std::cout << "I:" << spline.get_index() << ", ";
        spline.print_xi_eta();
        std::cout << std::endl;
    }
}

int spline_find(std::vector<Spline> &splines, double x, int &spline_index)
{
    int index = -1;
    for (unsigned long int i = 0; i < splines.size(); i++)
    {
        if (x >= splines[i].get_point_left().get_x() && x <= splines[i].get_point_right().get_x())
        {
            index = i;
        }
    }
    if (index == -1)
        return EXIT_FAILURE;
    else
        spline_index = index;
    return EXIT_SUCCESS;
}