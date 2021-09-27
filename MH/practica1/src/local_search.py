import numpy as np

def tasa_C(S, X, k):
    # puntos por cluster
    n_c = np.unique(S, return_counts=True)[1]

    # calculo de los centroides
    centroides = np.zeros((k, len(X[0])))
    for i, c in enumerate(S):
        centroides[c] += X[i]
    centroides = np.divide(centroides, n_c[:, None])

    # calculo de la media intra-cluster
    media_intracluster = np.zeros(k)
    for i, c in enumerate(S):
        media_intracluster[c] += np.linalg.norm(np.subtract(X[i], centroides[c]))
    media_intracluster = np.divide(media_intracluster, n_c)

    return np.sum(media_intracluster) / k
    
def infeasibility(S, R):
    infe = 0
    for x, c in enumerate(S):
        x_restrictions = R[x][x:]
        for y, r in enumerate(x_restrictions, start=x):
            # can not link
            if r == -1 and S[y] == c:
                infe += 1
            # must link
            elif r == 1 and S[y] != c:
                infe += 1
    return infe

def calc_lambda(X, R):
    max_dist = np.max([np.linalg.norm(np.subtract(x1,x2)) for i, x1 in enumerate(X) for x2 in X[i:]])
    # Matriz simetrica con diagonal de 1s
    num_rest = (np.count_nonzero(R) - len(R)) / 2
    return max_dist / num_rest

def f(C, infeasability, l):
    return C + infeasability * l     


def local_search(X, R, k, max_iters):
    incorrect_initial_state = True
    while incorrect_initial_state:
        S = np.random.randint(k, size=len(X))
        incorrect_initial_state = (len(np.unique(S)) != k)

    l = calc_lambda(X, R)
    f_S = f(tasa_C(S, X, k), infeasibility(S, R), l)

    n = 0
    mejora = True
    while n < max_iters and mejora:
        mejora = False
        pairs = [(i, c) for i in range(len(S)) for c in range(k) if c != S[i]]
        np.random.shuffle(pairs)
        for p in pairs:
            new_S = S.copy()
            new_S[p[0]] = p[1]
            if len(np.unique(new_S)) == k:
                new_f = f(tasa_C(new_S, X, k), infeasibility(new_S, R), l)
                n += 1
                if new_f < f_S:
                    S = new_S
                    f_S = new_f
                    mejora = True
                    break

    return S, n, tasa_C(S, X, k), infeasibility(S, R), f_S
