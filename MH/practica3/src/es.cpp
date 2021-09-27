#include "algorithms.h"
#include "extern.h"
#include "solution.h"

#include <math.h>
#include <algorithm>
#include <random>
#include <iostream>

Solution es(double mu, double phi, int max_evals, Solution sol){
    Solution best_solution, solution;
    if(sol.f == -1) generate_random_solution(solution);
    else solution = sol;
    best_solution = solution;

    const double t0 = (mu * solution.f) / (- log(phi));
    const double tf = 0.001;
    double t = t0;

    const int max_neighbours = 10 * data.size();
    const int max_improvements = 0.1 * max_neighbours;
    const int M = max_evals / max_neighbours;
    const double beta = (t0 - tf) / (M * t0 * tf);

    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int improvements = 1, neighbours = 0, iters = 0;
    double new_score;
    int evals = 0;
    while(iters < M && improvements){
        improvements = 0;
        neighbours = 0;

        while(improvements < max_improvements && neighbours < max_neighbours){
            int x = rand() % data.size(), c;
            int old_cluster = solution.s[x];
            do{
                c = rand() % k;
            } while(c == old_cluster);
            solution.s[x] = c;

            if(find(solution.s.begin(), solution.s.end(), old_cluster) != solution.s.end()){
                new_score = score(solution.s); evals++;
                double delta_f = new_score - solution.f;
                if(delta_f < 0 || distribution(random_engine) < exp(-delta_f/t)){
                    solution.f = new_score; improvements++;
                    if(solution.f < best_solution.f) best_solution = solution;
                }
                else {
                    solution.s[x] = old_cluster;
                }
            } else {
                solution.s[x] = old_cluster;
            }
            neighbours++;
        }

        t = t / (1 + beta*t);
        //t = t * 0.97;
        iters++;
    }
    
    return best_solution;
}
