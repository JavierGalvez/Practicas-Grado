#include "genetic.h"
#include "algorithms.h"
#include "extern.h"

#include <algorithm>

void replace(std::vector<Chromosome>& p, std::vector<Chromosome>& new_chromosomes){
    sort(new_chromosomes.begin(), new_chromosomes.end(), compare);
    sort(p.begin(), p.end(), compare);

    // worst new chromosome better than worst chromosome
    if(new_chromosomes[1].f < p[p.size()-1].f){
        p[p.size()-1] = new_chromosomes[1];
    }
    // best new chromosome better than second worst chromosome
    if(new_chromosomes[0].f < p[p.size()-2].f){
        p[p.size()-2] = new_chromosomes[0];
    // best new chromosome worse than second worst but better than worst and
    // and worst new chromosome worse than worst in population
    } else if(new_chromosomes[0].f < p[p.size()-1].f && 
              new_chromosomes[1].f > p[p.size()-1].f){
        p[p.size()-1] = new_chromosomes[0];
    }
}

Chromosome ageun(int n, float pc, float pm, int max_evals){
    std::vector<Chromosome> p, pSelect, new_chromosomes;
    generate_population(p, n);

    int evals_done = 0;
    float prob_mutations = pm * data.size();

    evals_done += evaluate(p);
    while(evals_done < max_evals){
        select(p, pSelect, 2);
        new_chromosomes = uniform_crossover(pSelect, 2);
        mutation_prob(new_chromosomes, prob_mutations);
        replace(p, new_chromosomes);
        evals_done += evaluate(p);
    }

    sort(p.begin(), p.end(), compare);
    return p[0];
}

Chromosome agesf(int n, float pc, float pm, int max_evals){
    std::vector<Chromosome> p, pSelect, new_chromosomes;
    generate_population(p, n);

    int evals_done = 0;
    float prob_mutations = pm * data.size();

    evals_done += evaluate(p);
    while(evals_done < max_evals){
        select(p, pSelect, 2);
        new_chromosomes = segment_crossover(pSelect, 2);
        mutation_prob(new_chromosomes, prob_mutations);
        replace(p, new_chromosomes);
        evals_done += evaluate(p);
    }

    sort(p.begin(), p.end(), compare);
    return p[0];
}
