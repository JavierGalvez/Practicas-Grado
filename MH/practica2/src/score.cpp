#include "extern.h"
#include "score.h"

#include <math.h>
#include <numeric>
#include <stdlib.h>
#include <algorithm>

const double euclidean_distance(const std::vector<double>& x, const std::vector<double>& y){
    double distance = 0;
    for(int i=0; i<x.size(); ++i)
        distance += (x[i]-y[i])*(x[i]-y[i]);
    return std::sqrt(distance);
}

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

const double C(const std::vector<int>& S){
    int n = data.size(), m = data[0].size();
    int n_c[k] = {0};
    double inner_distance[k] = {0};
    std::vector<std::vector<double> > centroids(k, std::vector<double>(m, 0));

    for(int i=0; i<n; ++i){
        n_c[S[i]]++;
        for(int j=0; j<m; ++j){
            centroids[S[i]][j] += data[i][j];
        }
    }

    for(int i=0; i<k; ++i)
        for(int j=0; j<m; ++j)
            centroids[i][j] /= n_c[i];

    for(int i=0; i<n; ++i)
        inner_distance[S[i]] += euclidean_distance(data[i], centroids[S[i]]);

    double c = 0.0;
    for(int i=0; i<k; ++i){
        c += inner_distance[i] / n_c[i];
    }

    return c / k; 
}

const int infeasibility(const std::vector<int>& S){
    int infe = 0;
    for(int i=0; i<S.size(); ++i){
        for(int j=i+1; j<S.size(); ++j){
            if(restrictions[i][j] == -1 && S[i] == S[j])
                infe += 1;
            else if(restrictions[i][j] == 1 && S[i] != S[j])
                infe += 1;
        }
    }
    return infe;
}

const double score(const std::vector<int>& S){
    return C(S) + infeasibility(S) * lambda;
}

