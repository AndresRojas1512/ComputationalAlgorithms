#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Layer
{
    public:
        int z;
        std::vector<double> x_vals;
        std::vector<double> y_vals;
        std::vector<std::vector<double>> data;
        friend std::ostream &operator<<(std::ostream &out, Layer &layer);
};

class Table
{
    public:
        std::vector<double> z_vals;
        std::vector<Layer> layers;

        void addLayer(const Layer& layer);
        void init_zs();
        friend std::ostream &operator<<(std::ostream &out, Table &table);
};

void parseCSVToTable(const std::string& filePath, Table& table);

void vector_print(std::vector<double> &vector);

#endif