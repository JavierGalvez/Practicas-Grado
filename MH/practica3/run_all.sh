#!/bin/bash

declare -i k
for alg in es bmb ils-ls ils-es; do
    for seed in 11264 16438 75645 79856 96867; do
        for dataset in iris rand newthyroid ecoli; do
            for r in 10 20; do
                if [ "$dataset" == "ecoli" ]
                then
                    k=8
                else
                    k=3
                fi
                echo -e '\n'$dataset $r $k $seed $alg'\n'
                ./test $dataset $r $k $seed $alg
            done
        done
    done
done
