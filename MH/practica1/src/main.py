import numpy as np
import sys
from time import time
import greedy
import local_search as ls

# python3 src/main.py dataset restrictions clusters gr/ls seed
# python3 src/main.py iris 10 3 ls 79856

assert len(sys.argv) == 6

data_path = "data/" + sys.argv[1] + "_set.dat"
restrictions_path = "data/" + sys.argv[1] + "_set_const_" + sys.argv[2] + ".const"
output_path = "output/" + sys.argv[1] + "_" + sys.argv[2] + "_"

with open(data_path) as f:
    data = [list(map(float, line.split(','))) for line in f]

with open(restrictions_path) as f:
    restrictions = [list(map(int, line.split(','))) for line in f]

k = int(sys.argv[3])
algoritmo = sys.argv[4]
seed = int(sys.argv[5])

print("Data set file: ", data_path)
print("Restrictions file: ", restrictions_path)

np.random.seed(seed)

# GREEDY
if algoritmo == 'gr':
    start = time()
    clusters, tasa_C, tasa_Inf, f = greedy.greedy(data, restrictions, k)
    end = time()

    output = {"tasa_C" : tasa_C,
                "tasa_Inf" : tasa_Inf,
                "f" : f,
                "tiempo" : end - start}

    with open(output_path + "greedy_" + str(seed) + ".output", 'w+') as f:
        for c in clusters:
            f.write(str(c) + "\n")

        f.write("\n")
        for key, value in output.items():
            f.write(key + ": " + str(value) + "\n")
    
        f.write("\nTamaño de los clusters: \n")
        for i, c in enumerate(clusters):
            f.write(str(i) + ": " + str(len(c)) + "\n")

# LOCAL SEARCH
elif algoritmo == 'ls':
    start = time()
    clusters, iters, tasa_C, tasa_Inf, f = ls.local_search(data, restrictions, k, 100000)
    end = time()

    n_c = np.unique(clusters, return_counts=True)

    output = {"tasa_C" : tasa_C,
                "tasa_Inf" : tasa_Inf,
                "f" : f,
                "iterations" : iters, 
                "tiempo" : end - start}

    with open(output_path + "ls_" + str(seed) + ".output", 'w+') as f:
        f.write(str(clusters) + "\n\n")
        for key, value in output.items():
            f.write(key + ": " + str(value) + "\n")

        f.write("\nTamaño de los clusters: \n")
        for i in range(k):
            f.write(str(n_c[0][i]) + ": " + str(n_c[1][i]) + "\n")
