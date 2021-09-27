#ifndef __SCORE_H__
#define __SCORE_H__

#include <vector>

const double C(const std::vector<int>& S);
const int infeasibility(const std::vector<int>& S);
const double calc_lambda(void);
const double score(const std::vector<int>& S);

#endif
