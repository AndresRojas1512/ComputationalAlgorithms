#include "table.h"

Table::Table(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c))
{
}

int Table::get_rows()
{
    return this->rows;
}

int Table::get_cols()
{
    return this->cols;
}

std::vector<double> &Table::operator[](int index)
{
    return data[index];
}

const std::vector<double> &Table::operator[](int index) const
{
    return data[index];
}

void Table::output()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
