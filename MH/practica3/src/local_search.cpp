#include "extern.h"
#include "score.h"
#include "algorithms.h"

#include <algorithm>
#include <random>
#include <iostream>
#include <utility>

int local_search(Solution& sol, int max_evals){
    int evals = 0;
    int shuffle_seed = seed;

    double new_score;

    bool upgrade = true;
    while(evals < max_evals && upgrade){
        upgrade = false;

        std::vector<std::pair<int, int> > pairs;
        for(int i=0; i<data.size(); ++i){
            for(int j=0; j<k; ++j){
                if(sol.s[i] != j)
                    pairs.push_back(std::pair<int, int>(i, j));
            }
        }
        std::shuffle(pairs.begin(), pairs.end(), random_engine);

        for(auto it=pairs.begin(); it!=pairs.end(); ++it){
            int old_cluster = sol.s[it->first];
            sol.s[it->first] = it->second;
            if(find(sol.s.begin(), sol.s.end(), old_cluster) != sol.s.end()){
                new_score = score(sol.s); evals++;
                if(new_score < sol.f){
                    sol.f = new_score;
                    upgrade = true;
                }
            }

            if(upgrade) break;
            else sol.s[it->first] = old_cluster;
        }
    }

    return evals;
}
