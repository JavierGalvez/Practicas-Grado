#include "algorithms.h"
#include "solution.h"

#include <limits>

Solution bmb(int iters, int ls_max_evals){
    Solution best_solution, solution;
    best_solution.f = std::numeric_limits<double>::max();

    for(int i=0; i<iters; ++i){
        generate_random_solution(solution);
        local_search(solution, ls_max_evals);
        if(solution.f < best_solution.f)
            best_solution = solution;
    }
    return best_solution;
}
