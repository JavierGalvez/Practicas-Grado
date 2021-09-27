#include "extern.h"
#include "score.h"
#include "algorithms.h"

#include <algorithm>
#include <random>
#include <utility>

int local_search(Solution& S, int max_evals){
    int evals = 0;

    double new_score;

    bool upgrade = true;
    while(evals < max_evals && upgrade){
        upgrade = false;

        std::vector<std::pair<int, int> > pairs;
        for(int i=0; i<data.size(); ++i){
            for(int j=0; j<k; ++j){
                if(S.clusters[i] != j)
                    pairs.push_back(std::pair<int, int>(i, j));
            }
        }
        std::shuffle(pairs.begin(), pairs.end(), random_engine);

        for(auto it=pairs.begin(); it!=pairs.end(); ++it){
            int old_cluster = S.clusters[it->first];
            std::vector<std::vector<double> > old_centroids = S.centroids;
            S.clusters[it->first] = it->second;
            if(find(S.clusters.begin(), S.clusters.end(), old_cluster) != S.clusters.end()){
                new_score = score(S); evals++;
                if(new_score < S.f){
                    S.f = new_score;
                    upgrade = true;
                }
            }

            if(upgrade) break;
            else{
                S.clusters[it->first] = old_cluster;
                S.centroids = old_centroids;
            }
        }
    }

    return evals;
}

