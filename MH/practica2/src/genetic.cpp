#include "extern.h"
#include "genetic.h"

#include <stdlib.h>
#include <set>
#include <algorithm>


void generate_random_solution(std::vector<int>& s){
    bool empty_cluster = true;

    do{
        s.clear();
        empty_cluster = false;
        int count[k] = {0};

        for(int i=0; i<data.size(); ++i){
            int c = rand() % k;
            s.push_back(c);
            count[c]++;
        }

        for(int i=0; i<k; ++i){
            if(count[i]==0){
                empty_cluster = true;
                break;
            }
        }

    } while(empty_cluster);
}

void generate_population(std::vector<Chromosome>& p, int& n){
    Chromosome c;
    for(int i=0; i<n; ++i){
        generate_random_solution(c.s);
        p.push_back(c);
    }
}

int evaluate(std::vector<Chromosome>& p){
    int evaluations_done = 0;
    for(auto it=p.begin(); it!=p.end(); ++it){
        if(it->f == -1){
            it->f = score(it->s);
            evaluations_done++;
        }
    }
    return evaluations_done;
}

void select(std::vector<Chromosome>& p, std::vector<Chromosome>& pSelect, int n){
    pSelect.clear();
    int x, y;
    for(int i=0; i<n; ++i){
        x = rand() % n;
        do{
            y = rand() % n;
        } while (x == y);

        if(p[x].f < p[y].f) pSelect.push_back(p[x]);
        else pSelect.push_back(p[y]);
    }
}

std::vector<Chromosome> uniform_crossover(std::vector<Chromosome>& p, int n){
    std::vector<Chromosome> new_chromosomes;

    for(int i=0; i<n; i+=2){
        Chromosome p1=p[i], p2=p[i+1];
        Chromosome h1, h2;

        aux_uniform_crossover(p1, p2, h1);
        aux_uniform_crossover(p1, p2, h2);

        new_chromosomes.push_back(h1);
        new_chromosomes.push_back(h2);
    }

    return new_chromosomes;
}

void aux_uniform_crossover(Chromosome& p1, Chromosome& p2, Chromosome& h){
        bool empty_cluster = true;
        int genes = p1.s.size();
        do{
            std::set<int> l;
            while(l.size()<genes/2) l.insert(rand() % genes);

            int count[k] = {0};

            auto it = l.begin();
            for(int j=0; j<genes; ++j){
                if(j == (*it)){
                    h.s.push_back(p1.s[j]);
                    it++;
                } else h.s.push_back(p2.s[j]);
                count[h.s[h.s.size()-1]]++;
            }
            empty_cluster = false;
            for(int j=0; j<k; ++j){
                if(count[j] == 0){
                    empty_cluster = true;
                    h.s.clear();
                    break;
                }
            }
        } while(empty_cluster);
}

std::vector<Chromosome> segment_crossover(std::vector<Chromosome>& p, int n){
    std::vector<Chromosome> new_chromosomes;

    for(int i=0; i<n; i+=2){
        Chromosome p1=p[i], p2=p[i+1];
        Chromosome h1, h2;

        aux_segment_crossover(p1, p2, h1);
        aux_segment_crossover(p1, p2, h2);

        new_chromosomes.push_back(h1);
        new_chromosomes.push_back(h2);
    }

    return new_chromosomes;
}

void aux_segment_crossover(Chromosome& p1, Chromosome& p2, Chromosome& h){
    int genes = p1.s.size();
    bool empty_cluster = true;
    do{
        int start = rand() % genes;
        int range = rand() % genes;
        int count[k] = {0};

        int genes_p1 = 0, genes_p2 = 0;
        int not_in_segment = genes - range;

        if((start+range) > genes){
            int aux = (start + range) % genes;
            for(int i=0; i<genes; ++i){
                if(i >= start || i < aux){
                    h.s.push_back(p1.s[i]);
                } else {
                    if(genes_p1 >= (not_in_segment/2)){
                        h.s.push_back(p2.s[i]);
                        genes_p2++;
                    }
                    else if(genes_p2 >= (not_in_segment/2)){
                        h.s.push_back(p1.s[i]);
                        genes_p1++;
                    }
                    else {
                        if((rand() % 1)){
                            h.s.push_back(p1.s[i]);
                            genes_p1++;
                        }
                        else{
                            h.s.push_back(p2.s[i]);
                            genes_p2++;
                        }
                    }
                }
                count[h.s[h.s.size()-1]]++;
            }
        } else {
            for(int i=0; i<genes; ++i){
                if(i >= start && i < (start+range)){
                    h.s.push_back(p1.s[i]);
                } else {
                    if(genes_p1 >= (not_in_segment/2)){
                        h.s.push_back(p2.s[i]);
                        genes_p2;
                    }
                    else if(genes_p2 >= (not_in_segment/2)){
                        h.s.push_back(p1.s[i]);
                        genes_p2;
                    }
                    else {
                        if((rand() % 1)){
                            h.s.push_back(p1.s[i]);
                            genes_p1++;
                        }
                        else{
                            h.s.push_back(p2.s[i]);
                            genes_p2++;
                        }
                    }
                }
                count[h.s[h.s.size()-1]]++;
            }
        }
        empty_cluster = false;
        for(int j=0; j<k; ++j){
            if(count[j] == 0){
                empty_cluster = true;
                h.s.clear();
                break;
            }
        }
    } while(empty_cluster);

}

void mutation(std::vector<Chromosome>& p, int n){
    int n_chromosomes = p.size() * p[0].s.size();

    std::set<int> l;
    while(l.size()<n) l.insert(rand() % n_chromosomes);

    for(auto it=l.begin(); it!=l.end(); ++it){
        int i = (*it) / p[0].s.size();
        int j = (*it) % p[0].s.size();

        int aux = p[i].s[j], c;
        do{
            c = rand() % k;
        } while(c == aux);

        p[i].s[j] = c;
        if(find(p[i].s.begin(), p[i].s.end(), aux) == p[i].s.end())
            p[i].s[j] = aux; 
        else
            p[i].f = -1;
    }

}

#include <iostream>
void mutation_prob(std::vector<Chromosome>& p, float pm){
    for(int i=0; i<p.size(); ++i){
        double r = ((double) rand() / (RAND_MAX));
        if(r <= pm){
            int g = rand() % p[i].s.size();

            int aux = p[i].s[g], c;
            do{
                c = rand() % k;
            } while(c == aux);

            p[i].s[g] = c;
            if(find(p[i].s.begin(), p[i].s.end(), aux) == p[i].s.end())
                p[i].s[g] = aux; 
            else
                p[i].f = -1;

        }
    }
}

void elitism(std::vector<Chromosome>& p, std::vector<Chromosome>& pSelect){
    sort(p.begin(), p.end(), compare);
    sort(pSelect.begin(), pSelect.end(), compare);

    Chromosome best = p[0];
    if(find(pSelect.begin(), pSelect.end(), best) == pSelect.end()){
        pSelect[pSelect.size()-1] = best;
    }
}
