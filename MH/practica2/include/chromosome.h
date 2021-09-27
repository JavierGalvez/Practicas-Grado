#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include <vector>

struct Chromosome{
    Chromosome() : f(-1) {};
    bool operator==(const Chromosome& c){ return (f == c.f); }
    std::vector<int> s;
    double f;
};
static bool compare(Chromosome c1, Chromosome c2) { return (c1.f < c2.f); }

#endif
