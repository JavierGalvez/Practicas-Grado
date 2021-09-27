#include "solution.h"
#include "extern.h"
#include "solution.h"

#include <vector>

void generate_random_solution(Solution& sol){
    bool empty_cluster = true;

    do{
        sol.s.clear();
        empty_cluster = false;
        int count[k] = {0};

        for(int i=0; i<data.size(); ++i){
            int c = rand() % k;
            sol.s.push_back(c);
            count[c]++;
        }

        for(int i=0; i<k; ++i){
            if(count[i]==0){
                empty_cluster = true;
                break;
            }
        }

    } while(empty_cluster);
    sol.f = score(sol.s);
}


bool compare(Solution s1, Solution s2) { return (s1.f < s2.f); }
