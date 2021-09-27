import numpy as np

# Generador de los centroides iniciales
def random_points(n, minimum, maximum):
    return [minimum + np.subtract(maximum, minimum) * np.random.random_sample(len(minimum)) for _ in range(n)]

# Calculo del centroide de un cluster
def calc_centroide(cluster, X):
    cent = np.zeros(len(X[0]))
    for i in cluster:
        cent += X[i]
    return cent / len(cluster)

# Calculo del aumento de infeasibility al añadir el punto x al cluster c
def calc_infeasibility(x, c, clusters, R):
    infe = 0
    for y, r in enumerate(R[x]):
        # can not link
        if r == -1 and y in clusters[c]:
            infe += 1
        # must link
        elif r == 1 and y not in clusters[c]:
            for k in range(len(clusters)):
                if k != c and y in clusters[k]:
                    infe += 1 
                    break
    return infe

def greedy(X, R, k):
    centroides = random_points(k, np.amin(X, axis=0), np.amax(X, axis=0))
    rsi = np.random.permutation(len(X))

    clusters = [[] for _ in range(k)]

    points_left = rsi.size
    change_C = True
    while change_C:
        for i in rsi:
            # Calculamos las infeasibilities para todos los clusters
            infe = [calc_infeasibility(i, j, clusters, R) for j in range(k)]

            # Nos quedamos con las asignaciones que producen menos incremento
            min_infe = np.array([j for j, k in enumerate(infe) if k == np.min(infe)])

            # Si hay más de una nos quedamos con la asociada al centroide de menor distancia
            if len(min_infe) > 1:
                # Calculamos las distancias
                dist = [[j, np.linalg.norm(np.subtract(X[i],centroides[j]))] for j in min_infe]

                # Nos quedamos con menor distancia
                min_infe = min(dist, key=lambda x: x[1])

            clusters[min_infe[0]].append(i)

            # Borramos i 
            rsi = np.delete(rsi, 0)

        # Recalculamos centroides
        centroides = [calc_centroide(clusters[i], X) for i in range(k) if len(clusters[i]) > 0]

        if points_left == rsi.size:
            change_C = False 
        points_left = rsi.size

    c = tasa_C(clusters, X)
    inf = tasa_Inf(clusters, R)
    return clusters, c, inf, f(c, inf, X, R)

def tasa_C(clusters, X):
    centroides = [ calc_centroide(c, X) for c in clusters ]

    media_intracluster = np.empty(len(clusters)) 
    for i, c in enumerate(clusters):
        media_intracluster[i] = np.sum([np.linalg.norm(np.subtract(X[j], centroides[i])) for j in c]) / len(c)

    return np.sum(media_intracluster) / len(clusters)

def tasa_Inf(clusters, R):
    infe = 0
    for k, c in enumerate(clusters):
        for x in c:
            x_restrictions = R[x][x:]
            for j, r in enumerate(x_restrictions, start=x):
                # can not link
                if r == -1 and j in c:
                    infe += 1
                # must link
                elif r == 1 and j not in c:
                    infe += 1
    return infe

def f(tasa_c, tasa_inf, X, R):
    max_dist = np.max([np.linalg.norm(np.subtract(x1,x2)) for i, x1 in enumerate(X) for x2 in X[i:]])
    # Matriz simetrica con diagonal de 1s
    num_rest = (np.count_nonzero(R) - len(R)) / 2
    return tasa_c + tasa_inf * max_dist / num_rest
