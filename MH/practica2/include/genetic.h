#ifndef __GENETIC_H__
#define __GENETIC_H__

#include "chromosome.h"
#include <vector>

void generate_random_solution(std::vector<int>& s);
void generate_population(std::vector<Chromosome>& p, int& n);
int evaluate(std::vector<Chromosome>& p);
void select(std::vector<Chromosome>& p, std::vector<Chromosome>& pSelect, int n);
std::vector<Chromosome> uniform_crossover(std::vector<Chromosome>& p, int n);
void aux_uniform_crossover(Chromosome& p1, Chromosome& p2, Chromosome& h);
std::vector<Chromosome> segment_crossover(std::vector<Chromosome>& p, int n);
void aux_segment_crossover(Chromosome& p1, Chromosome& p2, Chromosome& h);
void mutation(std::vector<Chromosome>& p, int n);
void mutation_prob(std::vector<Chromosome>& p, float pm);
void elitism(std::vector<Chromosome>& p, std::vector<Chromosome>& pSelect);

#endif
