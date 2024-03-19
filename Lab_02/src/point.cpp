#include "point.h"

Point::Point() : x(0), y(0)
{
}

Point::Point(double x_param, double y_param, int index_param) : x(x_param), y(y_param), index(index_param)
{
}

// Setters

void Point::set_x(double x_param)
{
    this->x = x_param;
}

void Point::set_y(double y_param)
{
    this->y = y_param;
}

void Point::set_index(int index_param)
{
    this->index = index_param;
}

// Getters

double Point::get_x()
{
    return this->x;
}

double Point::get_y()
{
    return this->y;
}

int Point::get_index()
{
    return this->index;
}

std::ostream &operator<<(std::ostream &out, Point &point)
{
    out << "I: " << point.get_index() << "-[X: " << point.get_x() << ", " << "Y: " << point.get_y() << "]";
    return out;
}
