#ifndef LINKAGE_H
#define LINKAGE_H

#include <iostream>
#include <vector>

class LinkageDegree
{
    public:
        int degree;
        int hermite_points;
        int newton_degree;

        LinkageDegree(int degree_p, int h_param, int n_param);
};

class LinkagePoint
{
    public:
        int points;
        int hermite_points;
        int newton_degree;
    
        LinkagePoint(int p_param, int h_param, int n_param);
};

void linkage_degree_map(std::vector<LinkageDegree> &vector_ld, std::vector<int> degrees_std);
void linkage_degree_print(std::vector<LinkageDegree> &vector_ld);

void linkage_point_map(std::vector<LinkagePoint> &vector_lp, std::vector<int> &points_std);
void linkage_point_print(std::vector<LinkagePoint> &vector_lp);

#endif
