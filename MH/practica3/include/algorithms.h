#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include "solution.h"

int local_search(Solution& sol, int max_evals);
Solution es(double mu, double phi, int max_evals, Solution sol=Solution());
Solution bmb(int iters=10, int ls_max_evals=10000);
Solution ils_ls(int iters=10, int ls_max_evals=10000);
Solution ils_es(int iters, int es_max_evals);

#endif
