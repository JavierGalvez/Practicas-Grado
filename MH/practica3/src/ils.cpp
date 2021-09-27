#include "solution.h"
#include "extern.h"
#include "algorithms.h"

#include <random>

Solution mutation(Solution& sol, int v){
    int n = data.size(), c;
    bool empty_cluster = true;
    Solution mutated_solution;

    do{
        mutated_solution.s.clear();

        int start = rand() % n;
        int count[k] = {0};

        if((start+v) > n){
            int aux = (start + v) % n;
            for(int i=0; i<n; ++i){
                if(i >= start || i < aux) c = rand() % k;
                else c = sol.s[i];
                mutated_solution.s.push_back(c);
                count[c]++;
            }
        } else {
            for(int i=0; i<n; ++i){
                if(i >= start && i < (start+v)) c = rand() % k;
                else c = sol.s[i];
                mutated_solution.s.push_back(c);
                count[c]++;
            }
        }

        empty_cluster = false;
        for(int j=0; j<k; ++j){
            if(count[j] == 0){
                empty_cluster = true;
                break;
            }
        }
    } while(empty_cluster);
    mutated_solution.f = score(mutated_solution.s);

    return mutated_solution;
}

Solution ils_ls(int iters, int ls_max_evals){
    int v = 0.1 * data.size();
    Solution best_solution, solution;
    generate_random_solution(solution);
    best_solution = solution;

    for(int i=0; i<iters; ++i){
        local_search(solution, ls_max_evals);
        if(solution.f < best_solution.f)
            best_solution = solution;
        solution = mutation(best_solution, v);
    }
    return best_solution;
}

Solution ils_es(int iters, int es_max_evals){
    int v = 0.1 * data.size();
    Solution best_solution, solution;
    generate_random_solution(solution);
    best_solution = solution;

    for(int i=0; i<iters; ++i){
        solution = es(0.3, 0.3, es_max_evals, solution);
        if(solution.f < best_solution.f)
            best_solution = solution;
        solution = mutation(best_solution, v);
    }
    return best_solution;
}
