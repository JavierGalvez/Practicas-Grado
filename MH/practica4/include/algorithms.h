#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include "tools.h"
#include <string>

Solution bbbc(int n, int max_evals, float crunch, bool use_ls=false);
int local_search(Solution& S, int max_evals);

#endif
