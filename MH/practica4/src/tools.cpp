#include "tools.h"
#include "extern.h"

#include <vector>
#include <limits>
#include <math.h>
#include <algorithm>

bool compare(Solution s1, Solution s2) { return (s1.f < s2.f); }

void generate_random_solution(Solution& S){
    bool empty_cluster = true;

    do{
        S.clusters.clear();
        empty_cluster = false;
        int count[k] = {0};

        for(int i=0; i<data.size(); ++i){
            int c = rand() % k;
            S.clusters.push_back(c);
            count[c]++;
        }

        for(int i=0; i<k; ++i){
            if(count[i]==0){
                empty_cluster = true;
                break;
            }
        }

    } while(empty_cluster);
    calc_centroids(S);
    S.f = score(S, false);
}

void calc_centroids(Solution& S){
    int n_c[k] = {0}, n = data.size(), m = data[0].size();
    std::vector<std::vector<double> > centroids(k, std::vector<double>(m, 0));

    for(int i=0; i<n; ++i){
        int cluster = S.clusters[i];
        n_c[cluster]++;
        for(int j=0; j<m; ++j){
            centroids[cluster][j] += data[i][j];
        }
    }

    for(int i=0; i<k; ++i)
        for(int j=0; j<m; ++j)
            centroids[i][j] /= n_c[i];

    S.centroids = centroids;
}

const int local_infeasibility(std::vector<int>& clusters, int x, int c){
    int infea = 0;
    for(int i=0; i<data.size(); ++i){
        if(restrictions[x][i] == -1 && clusters[i] == c)
            infea += 1;
        else if(restrictions[x][i] == 1 && (clusters[i] != c && clusters[i] != -1))
            infea += 1;
    }
    return infea;
}

void update_clusters(Solution& S){
    std::vector<int> aux(data.size(), -1);


    std::vector<int> order(data.size());
    std::iota(order.begin(), order.end(), 0);
    std::shuffle(order.begin(), order.end(), random_engine);

    for(auto it=order.begin(); it!=order.end(); ++it){
        std::vector<int> mins;
        int min = std::numeric_limits<int>::max();
        for(int c=0; c<k; ++c){
            int infea = local_infeasibility(aux, *it, c);
            if(infea < min){
                mins.clear();
                mins.push_back(c);
                min = infea;
            } else if(infea == min){
                mins.push_back(c);
            }
        }
        if(mins.size() > 1){
            std::vector<double> distances;
            for(auto i=0; i<mins.size(); ++i){ 
                distances.push_back(euclidean_distance(data[*it], S.centroids[mins[i]]));
            }
            aux[*it] = mins[std::min_element(distances.begin(), distances.end()) - distances.begin()];
        } else {
            aux[*it] = mins[0];
        }
    }

    S.clusters = aux;
}

std::vector<std::pair<double, double> > get_bounds(void){
    std::vector<std::pair<double, double> > bounds
    (
        data[0].size(), 
        std::pair<double, double>(std::numeric_limits<double>::max(), std::numeric_limits<double>::min())
    );

    for(int i=0; i<data.size(); ++i){
        for(int j=0; j<data[0].size(); ++j){
            if(data[i][j] < bounds[j].first) bounds[j].first = data[i][j];
            if(data[i][j] > bounds[j].second) bounds[j].second = data[i][j];
        }
    }

    return bounds;
}

void keep_bounds(Solution& S){
    for(int i=0; i<k; ++i){
        for(int j=0; j<data[0].size(); ++j){
            if(S.centroids[i][j] < bounds[j].first)
                S.centroids[i][j] = bounds[j].first;
            if(S.centroids[i][j] > bounds[j].second)
                S.centroids[i][j] = bounds[j].second;
        }
    }
}

const double euclidean_distance(const std::vector<double>& x, const std::vector<double>& y){
    double distance = 0;
    for(int i=0; i<x.size(); ++i)
        distance += (x[i]-y[i])*(x[i]-y[i]);
    return std::sqrt(distance);
}
