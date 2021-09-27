#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include "chromosome.h"

Chromosome aggun(int n=50, float pc=0.7, float pm=0.001, int max_evals=100000);
Chromosome aggsf(int n=50, float pc=0.7, float pm=0.001, int max_evals=100000);

Chromosome ageun(int n=50, float pc=1.0, float pm=0.001, int max_evals=100000);
Chromosome agesf(int n=50, float pc=1.0, float pm=0.001, int max_evals=100000);

Chromosome am_all(int n=10, float pc=0.7, float pm=0.001, int max_evals=100000);
Chromosome am_random(int n=10, float pc=0.7, float pm=0.001, int max_evals=100000);
Chromosome am_best(int n=10, float pc=0.7, float pm=0.001, int max_evals=100000);
int local_search(Chromosome& c, int max_fails);

#endif
