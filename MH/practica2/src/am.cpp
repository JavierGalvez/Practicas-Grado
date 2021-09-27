#include "algorithms.h"
#include "genetic.h"
#include "extern.h"

#include <random>
#include <algorithm>
#include <vector>

Chromosome am_all(int n, float pc, float pm, int max_evals){
    std::vector<Chromosome> p, pSelect, new_chromosomes;
    generate_population(p, n);

    int evals_done = 0;
    int n_crossovers = pc * n/2;
    int n_mutations = pm * n * data.size();
    int n_select = n;
    int max_fails = 0.1 * data.size();
    int generation = 1;

    evals_done += evaluate(p);
    while(evals_done < max_evals){
        if((generation % 10) == 0){
            // ls
            for(auto it=p.begin(); it!=p.end(); ++it){
                evals_done += local_search((*it), max_fails);
            }
        }
        // aggun
        select(p, pSelect, n_select);
        new_chromosomes = uniform_crossover(pSelect, n_crossovers);
        for(int i=0; i<n_crossovers; ++i)
            pSelect[i] = new_chromosomes[i];
        mutation(pSelect, n_mutations);
        elitism(p, pSelect);
        p = pSelect;
        evals_done += evaluate(p);

        generation++;
    }

    sort(p.begin(), p.end(), compare);
    return p[0];
}

Chromosome am_random(int n, float pc, float pm, int max_evals){
    std::vector<Chromosome> p, pSelect, new_chromosomes;
    generate_population(p, n);

    int evals_done = 0;
    int n_crossovers = pc * n/2;
    int n_mutations = pm * n * data.size();
    int n_select = n;
    int max_fails = 0.1 * data.size();
    int generation = 1;

    evals_done += evaluate(p);
    while(evals_done < max_evals){
        if((generation % 10) == 0){
            // ls
            for(auto it=p.begin(); it!=p.end(); ++it){
                if(((double) rand() / RAND_MAX) <= 0.1)
                    evals_done += local_search((*it), max_fails);
            }
        }
        // aggun
        select(p, pSelect, n_select);
        new_chromosomes = uniform_crossover(pSelect, n_crossovers);
        for(int i=0; i<n_crossovers; ++i)
            pSelect[i] = new_chromosomes[i];
        mutation(pSelect, n_mutations);
        elitism(p, pSelect);
        p = pSelect;
        evals_done += evaluate(p);

        generation++;
    }

    sort(p.begin(), p.end(), compare);
    return p[0];
}

Chromosome am_best(int n, float pc, float pm, int max_evals){
    std::vector<Chromosome> p, pSelect, new_chromosomes;
    generate_population(p, n);

    int evals_done = 0;
    int n_crossovers = pc * n/2;
    int n_mutations = pm * n * data.size();
    int n_select = n;
    int max_fails = 0.1 * data.size();
    int generation = 1;

    evals_done += evaluate(p);
    while(evals_done < max_evals){
        if((generation % 10) == 0){
            // ls
            sort(p.begin(), p.end(), compare);
            for(int i=0; i<0.1*n; ++i){
                evals_done += local_search(p[i], max_fails);
            }
        }
        // aggun
        select(p, pSelect, n_select);
        new_chromosomes = uniform_crossover(pSelect, n_crossovers);
        for(int i=0; i<n_crossovers; ++i)
            pSelect[i] = new_chromosomes[i];
        mutation(pSelect, n_mutations);
        elitism(p, pSelect);
        p = pSelect;
        evals_done += evaluate(p);

        generation++;
    }

    sort(p.begin(), p.end(), compare);
    return p[0];
}
