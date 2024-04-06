#include "table.h"

void Table::addLayer(const Layer& layer)
{
    layers.push_back(layer);
}

void parseCSVToTable(const std::string& filePath, Table& table)
{
    std::ifstream file(filePath);
    std::string line;
    Layer currentLayer;
    bool parsingLayer = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        if (!parsingLayer)
        {
            currentLayer = Layer();
            currentLayer.z = std::stoi(line);
            parsingLayer = true;
            getline(file, line);

            std::istringstream ss(line.substr(4));
            double val;
            while (ss >> val)
            {
                currentLayer.x_vals.push_back(val);
                if (ss.peek() == ',')
                    ss.ignore();
            }
        }
        else if (!line.empty())
        {
            std::istringstream ss(line);
            double yVal;
            ss >> yVal;
            currentLayer.y_vals.push_back(yVal);
            if (ss.peek() == ',')
                ss.ignore();

            std::vector<double> rowData;
            double dataVal;
            while (ss >> dataVal)
            {
                rowData.push_back(dataVal);
                if (ss.peek() == ',')
                    ss.ignore();
            }
            currentLayer.data.push_back(rowData);
            if (currentLayer.data.size() == currentLayer.x_vals.size())
            {
                table.addLayer(currentLayer);
                parsingLayer = false;
            }
        }
    }
}

std::ostream &operator<<(std::ostream &out, Layer &layer)
{
    out << "Z: " << layer.z << std::endl;
    out << "X_VALS: ";
    for (unsigned long int i = 0; i < layer.x_vals.size(); i++)
        out << layer.x_vals[i];
    out << std::endl;
    out << "Y_VALS: ";
    for (unsigned long int i = 0; i < layer.y_vals.size(); i++)
        out << layer.y_vals[i];
    out << std::endl;
    out << "DATA: " << std::endl;
    for (unsigned long int i = 0; i < layer.data.size(); i++)
    {
        for (unsigned long int j = 0; j < layer.data[i].size(); j++)
        {
            out << layer.data[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, Table &table)
{
    for (unsigned long int i = 0; i < table.layers.size(); i++)
        out << table.layers[i] << std::endl;
    return out;
}