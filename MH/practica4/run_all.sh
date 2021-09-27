#!/bin/bash

declare -i k
for dataset in iris rand newthyroid ecoli; do
    for seed in 11264 16438 75645 79856 96867; do
        for option in a b c d; do
            for r in 10 20; do
                if [ "$dataset" == "ecoli" ]
                then
                    k=8
                else
                    k=3
                fi
                echo -e '\n'$dataset $r $k $seed $option'\n'
                ./bb-bc $dataset $r $k $seed $option
            done
        done
    done
done
