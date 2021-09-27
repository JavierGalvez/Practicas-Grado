import csv

path = "../practica4/output/"
dataset = ["iris", "rand", "newthyroid", "ecoli"]
rest = ["10", "20"]
seed = ["11264", "16438", "75645", "79856", "96867"]
alg = ["a", "b", "c", "d"]
#am_best_newthyroud_10_79856.output


rows = "8"
cols = "17"

for a in alg:
    for r in rest:
        for s in seed:
            row = [s]
            tiempos = []
            for ds in dataset:
                data_path = path + a + "_" + ds + "_" + r + "_" + s + ".output"
                with open(data_path) as f:
                    tiempos.append("{:.4}".format(float(f.readline().rstrip().split("\t")[1])))
                    for line in f:
                        row.append("{:.4f}".format(float(line.rstrip().split("\t")[1])))

            row.append("")
            row.append(s)
            for t in tiempos:
                row.append(t)
                row.append("")

            with open("./practica4/" + a + "_" + r +'.csv', 'a') as f:
                thewriter = csv.writer(f)
                thewriter.writerow(row)

