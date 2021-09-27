#include "algorithms.h"
#include "extern.h"
#include "tools.h"

#include <vector>
#include <algorithm>

Solution bbbc(int n, int max_evals, float crunch, bool use_ls){
    std::normal_distribution<double> distribution(0.0, 1.0);

    Solution S;
    generate_random_solution(S);

    std::vector<std::vector<double> > CoM = S.centroids;

    std::vector<Solution> population;
    Solution best_solution = S;
    int evals = 0, iter = 1;

    int max_fails = 0.1 * data.size();
    int n_best = n * crunch;

    while(evals < max_evals){
        // Big Bang
        population.clear();
        do{
            Solution new_solution; new_solution.centroids = CoM;
            for(int i=0; i<k; ++i){
                for(int j=0; j<data[0].size(); ++j){
                new_solution.centroids[i][j] += 
                    distribution(random_engine) *
                    (bounds[j].second - bounds[j].first)
                    / iter;
                }
            }
            keep_bounds(new_solution);
            update_clusters(new_solution);
            new_solution.f = score(new_solution, false); evals++;
            if(!std::isnan(new_solution.f)){
                population.push_back(new_solution);
            }
        } while(population.size() != n);

        std::sort(population.begin(), population.end(), compare);

        // Big Crunch
        std::vector<std::vector<double> > new_CoM(k, std::vector<double>(data[0].size(), 0));
        double sum = 0;
        for(int h=0; h<n_best; ++h){
            if(iter % 10 == 0 && use_ls){
                evals += local_search(population[h], 10000);
            }
            sum += 1 / population[h].f;
            for(int i=0; i<k; ++i){
                for(int j=0; j<data[0].size(); ++j){
                    new_CoM[i][j] += population[h].centroids[i][j] / population[h].f;
                }
            }
        }

        for(int i=0; i<k; ++i){
            for(int j=0; j<data[0].size(); ++j){
                new_CoM[i][j] /= sum;
            }
        }

        CoM = new_CoM;


        if(use_ls)
            std::sort(population.begin(), population.end(), compare);
        if(population[0].f < best_solution.f){
            best_solution = population[0];
        }
        iter++;
    }

    return best_solution;
}

