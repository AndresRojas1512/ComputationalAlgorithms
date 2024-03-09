#include "linkage.h"

// Linkage Degree
LinkageDegree::LinkageDegree(int degree_p, int h_param, int n_param) : degree(degree_p), hermite_points(h_param), newton_degree(n_param)
{
}

void linkage_degree_map(std::vector<LinkageDegree> &vector_ld, std::vector<int> degrees_std)
{
    for (long unsigned int i = 0; i < degrees_std.size(); i++)
    {
        int degree = degrees_std[i];
        int hermite_points = (degree + 1) / 3;
        int newton_degree = degree + 1;
        vector_ld.push_back(LinkageDegree(degree, hermite_points, newton_degree));
    }
}

void linkage_degree_print(std::vector<LinkageDegree> &vector_ld)
{
    for (long unsigned int i = 0; i < vector_ld.size(); i++)
    {
        std::cout << "Degree: " << vector_ld[i].degree << " | Hermite points: " << vector_ld[i].hermite_points << " | Newton Degree: " << vector_ld[i].newton_degree << std::endl;
    }
}

// Linkage point
LinkagePoint::LinkagePoint(int p_param, int h_param, int n_param) : points(p_param), hermite_points(h_param), newton_degree(n_param)
{
}

void linkage_point_map(std::vector<LinkagePoint> &vector_lp, std::vector<int> &points_std)
{
    for (long unsigned int i = 0; i < points_std.size(); i++)
    {
        int point = points_std[i];
        int hermite_points = point;
        int newton_degree = point - 1;
        vector_lp.push_back(LinkagePoint(point, hermite_points, newton_degree));
    }
}

void linkage_point_print(std::vector<LinkagePoint> &vector_lp)
{
    for (long unsigned int i = 0; i < vector_lp.size(); i++)
    {
        std::cout << "Points: " << vector_lp[i].points << " | Hermite points: " << vector_lp[i].hermite_points << " | Newton Degree: " << vector_lp[i].newton_degree << std::endl;
    }
}
