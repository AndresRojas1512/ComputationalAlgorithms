#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>

class Table
{
    private:
        int rows;
        int cols;
        std::vector<std::vector<double>> data;
    public:
        Table() = default;
        Table(int r, int c);

        int get_rows();
        int get_cols();

        std::vector<double> &operator[](int index);
        const std::vector<double> &operator[](int index) const;

        void output();
};

#endif