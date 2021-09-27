#include "extern.h"
#include "score.h"
#include "algorithms.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <limits>

int local_search(Chromosome& c, int max_fails){
    int fails = 0, evals = 0;
    int shuffle_seed = seed;

    std::vector<int> order(c.s.size());
    std::iota(order.begin(), order.end(), 0);

    int best_cluster;
    double best_score, new_score;

    std::shuffle(order.begin(), order.end(), random_engine);

    for(auto it=order.begin(); it!=order.end(); ++it){
        best_score = std::numeric_limits<double>::max();
        int old_cluster = c.s[(*it)];
        for(int i=0; i<k; ++i){
            if(i != old_cluster){
                c.s[(*it)] = i;
                if(find(c.s.begin(), c.s.end(), old_cluster) != c.s.end()){
                    new_score = score(c.s);
                    evals++;
                    if(new_score < best_score){
                        best_score = new_score;
                        best_cluster = i;
                    }
                }
            }
        }

        if(best_score < c.f){
            c.s[(*it)] = best_cluster;
            c.f = best_score;
        } else {
            c.s[(*it)] = old_cluster;
            fails++;
        }

        if(fails >= max_fails) break;
    }

    return evals;
}
