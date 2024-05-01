#include "point.h"

Point::Point() : x(0), y(0)
{
}

Point::Point(double x_param, double y_param, double weight_param) : x(x_param), y(y_param), z(0), weight(weight_param)
{
}

Point::Point(double x_param, double y_param, double z_param ,double weight_param) : x(x_param), y(y_param), z(z_param), weight(weight_param)
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

void Point::set_z(double z_param)
{
    this->z = z_param;
}

void Point::set_weight(double weight_param)
{
    this->weight = weight_param;
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

double Point::get_z()
{
    return z;
}

double Point::get_weight()
{
    return weight;
}

std::ostream &operator<<(std::ostream &out, Point &point)
{
    out << "Point: (" << point.x << ", " << point.y << ", " << point.z << "), weight: " << point.weight;
    return out;
}