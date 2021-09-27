#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <vector>

struct Solution{
    Solution() : f(-1) {};
    bool operator==(const Solution& c){ return (f == c.f); }
    std::vector<int> clusters;
    std::vector<std::vector<double> > centroids;
    double f;
};

bool compare(Solution s1, Solution s2);
void generate_random_solution(Solution& S);
void calc_centroids(Solution& S);
const int local_infeasibility(std::vector<int>& clusters, int x, int c);
void update_clusters(Solution& S);
std::vector<std::pair<double, double> > get_bounds(void);
void keep_bounds(Solution& S);
const double euclidean_distance(const std::vector<double>& x, const std::vector<double>& y);

#endif
