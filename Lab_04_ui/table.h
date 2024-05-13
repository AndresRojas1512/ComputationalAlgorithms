#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <fstream>
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

    void append(const std::vector<double> &row);

    std::vector<double> &operator[](int index);
    const std::vector<double> &operator[](int index) const;

    void output();
};

#endif
