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

void Table::append(const std::vector<double> &row)
{
    if (static_cast<int>(row.size()) != cols && cols != 0)
    {
        throw std::runtime_error("Row size does not match the number of columns in the table.");
    }
    else if (cols == 0 && rows == 0)
    {
        cols = row.size();
    }
    data.push_back(row);
    rows++;
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