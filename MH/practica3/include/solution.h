#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <vector>

struct Solution{
    Solution() : f(-1) {};
    bool operator==(const Solution& c){ return (f == c.f); }
    std::vector<int> s;
    double f;
};

bool compare(Solution s1, Solution s2);
void generate_random_solution(Solution& s);

#endif
