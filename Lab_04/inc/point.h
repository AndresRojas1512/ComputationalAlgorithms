#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
    private:
        double x;
        double y;
        double z;
        double weight;
    public:
        friend std::ostream &operator<<(std::ostream &out, Point &point);

        Point();
        Point(double x_param, double y_param, double weight);
        Point(double x_param, double y_param, double z_param, double weight);

        double get_x();
        double get_y();
        double get_z();
        double get_weight();

        void set_x(double x_param);
        void set_y(double y_param);
        void set_z(double z_param);
        void set_weight(double weight_param);
};

#endif