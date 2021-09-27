#include "tools.h"

#include <vector>
#include <random>

std::vector<std::vector<double> > data;
std::vector<std::vector<int> > restrictions;
std::vector<std::pair<double, double> > bounds;
int k, seed; double lambda;
std::default_random_engine random_engine;

