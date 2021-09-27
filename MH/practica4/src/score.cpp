#include "extern.h"
#include "score.h"

const double calc_lambda(void){
    double max_dist = 0.0, dist;
    int num_rest = 0;
    for(int i=0; i<data.size(); ++i){
        for(int j=i+1; j<data.size(); ++j){
            dist = euclidean_distance(data[i], data[j]);
            if(max_dist < dist) max_dist = dist; 
            if(restrictions[i][j] != 0) num_rest++;
        }
    }

    return max_dist / num_rest;
}

const double C(Solution& S){
    int n = data.size(), m = data[0].size();
    int n_c[k] = {0};
    double inner_distance[k] = {0};

    for(int i=0; i<n; ++i){
        int cluster = S.clusters[i];
        n_c[cluster]++;
        inner_distance[cluster] += euclidean_distance(data[i], S.centroids[cluster]);
    }

    double c = 0.0;
    for(int i=0; i<k; ++i){
        c += inner_distance[i] / n_c[i];
    }

    return c / k; 
}

const int infeasibility(Solution& S){
    int infe = 0;
    for(int i=0; i<data.size(); ++i){
        for(int j=i+1; j<data.size(); ++j){
            if(restrictions[i][j] == -1 && S.clusters[i] == S.clusters[j])
                infe += 1;
            else if(restrictions[i][j] == 1 && S.clusters[i] != S.clusters[j])
                infe += 1;
        }
    }
    return infe;
}

const double score(Solution& S, bool recalculate_centroids){
    if(recalculate_centroids) calc_centroids(S);
    return C(S) + infeasibility(S) * lambda;
}

