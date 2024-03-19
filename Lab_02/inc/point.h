#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
    private:
        double x;
        double y;
        int index;
    public:
        friend std::ostream &operator<<(std::ostream &out, Point &point);

        Point();
        Point(double x_param, double y_param, int index_param);

        // Getters
        double get_x();
        double get_y();
        int get_index();

        // Setters
        void set_x(double x_param);
        void set_y(double y_param);
        void set_index(int index_param);
};

#endif