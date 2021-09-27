#ifndef __SCORE_H__
#define __SCORE_H__

const double calc_lambda(void);
const double C(Solution& S);
const int infeasibility(Solution& S);
const double score(Solution& S, bool recalculate_centroids=true);

#endif
