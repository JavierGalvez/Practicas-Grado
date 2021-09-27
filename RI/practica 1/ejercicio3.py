import sympy as sym
from numpy import radians

def denavit_hartenbeg(params):
    t = sym.Identity(4)
    for (theta, d, a, alpha) in params:
        # Rotación Z_{i-1}
        r1 = sym.Matrix([[sym.cos(theta), -sym.sin(theta), 0, 0],
                         [sym.sin(theta), sym.cos(theta), 0, 0],
                         [0, 0, 1, 0],
                         [0, 0, 0, 1]])
        # Traslación Z_{i-1}
        t1 = sym.Matrix([[1, 0, 0, 0], [0, 1, 0, 0],
                         [0, 0, 1, d], [0, 0, 0, 1]])
        # Rotación X_i
        t2 = sym.Matrix([[1, 0, 0, a], [0, 1, 0, 0],
                         [0, 0, 1, 0], [0, 0, 0, 1]])
        # Traslación X_i
        r2 = sym.Matrix([[1, 0, 0, 0],
                         [0, sym.cos(alpha), -sym.sin(alpha), 0],
                         [0, sym.sin(alpha), sym.cos(alpha), 0],
                         [0, 0, 0, 1]])
        t = t * (r1 * t1 * t2 * r2)
        t = sym.N(t)
        t = t.nsimplify(tolerance=1e-10)
    return t

# Ejemplo diapositiva 17 tema 4
q1, l1, q2, l3, q3 = sym.symbols("q1, l1, q2, l3, q3")
ejemplo = [[q1, l1, 0, 0], 
           [radians(90), q2, 0, radians(90)],
           [0, l3 + q3, 0 , 0]]
t = denavit_hartenbeg(ejemplo)
t = sym.N(t)
t = t.nsimplify(tolerance=1e-10)
print(t)