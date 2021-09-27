#include "tools.h"
#include "score.h"

#include <vector>
#include <random>

extern std::vector<std::vector<double> > data;
extern std::vector<std::vector<int> > restrictions;
extern std::vector<std::pair<double, double> > bounds;
extern double lambda;
extern int k; 
extern int seed;
extern std::default_random_engine random_engine;
