#include "genetic.h"
#include "algorithms.h"
#include "extern.h"

#include <algorithm>

Chromosome aggun(int n, float pc, float pm, int max_evals){
    std::vector<Chromosome> p, pSelect, new_chromosomes;
    generate_population(p, n);

    int evals_done = 0;
    int n_crossovers = pc * n/2;
    int n_mutations = pm * n * data.size();

    evals_done += evaluate(p);
    while(evals_done < max_evals){
        select(p, pSelect, n);
        new_chromosomes = uniform_crossover(pSelect, n_crossovers);
        for(int i=0; i<n_crossovers; ++i)
            pSelect[i] = new_chromosomes[i];
        mutation(pSelect, n_mutations);
        elitism(p, pSelect);
        p = pSelect;
        evals_done += evaluate(p);
    }

    sort(p.begin(), p.end(), compare);
    return p[0];
}

Chromosome aggsf(int n, float pc, float pm, int max_evals){
    std::vector<Chromosome> p, pSelect, new_chromosomes;
    generate_population(p, n);

    int evals_done = 0;
    int n_crossovers = pc * n/2;
    int n_mutations = pm * n * data.size();

    evals_done += evaluate(p);
    while(evals_done < max_evals){
        select(p, pSelect, n);
        new_chromosomes = segment_crossover(pSelect, n_crossovers);
        for(int i=0; i<n_crossovers; ++i)
            pSelect[i] = new_chromosomes[i];
        mutation(pSelect, n_mutations);
        elitism(p, pSelect);
        p = pSelect;
        evals_done += evaluate(p);
    }

    sort(p.begin(), p.end(), compare);
    return p[0];
}
