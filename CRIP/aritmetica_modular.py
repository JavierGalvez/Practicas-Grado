# Javier Gálvez Obispo

from random import randint
import timeit

# Ejercicio 1

def mcd(a, b):
    """Algoritmo extendido de Euclides para el cálculo del máximo común divisor

    Input: dos enteros positivos a, b
    Output: máximo común dividor de a, b y u, v tal que au + bv = mcd(a, b)
    """

    d = [a, b]
    u = [1, 0]
    v = [0, 1]

    while d[1] != 0:
        q = d[0] // d[1]
        d = [d[1], d[0] - d[1]*q]
        u = [u[1], u[0] - u[1]*q]
        v = [v[1], v[0] - v[1]*q]

    return d[0], u[0], v[0]

# Ejercicio 2

def inverso(a, b):
    """Calcula el inverso de a en Zb utilizando el algoritmo extendido de Euclides
    
    Input: dos enteros positivos a, b
    Output: u tal que au = 1 en Zb o None si a, b no son coprimos
    """

    d = [a, b]
    u = [1, 0]

    while d[1] != 0:
        q = d[0] // d[1]
        d = [d[1], d[0] - d[1]*q]
        u = [u[1], u[0] - u[1]*q]

    inv = u[0] % b if d[0] == 1 else None

    return inv

# Ejercicio 3

def powmod(a, n, m):
    """Calcula a^n mod m utilizando la representación binaria de n
    
    Input: tres enteros positivos a, n, m
    Output: resultado de calcular a^n mod m
    """

    binario = bin(int(n))[2:]

    p = 1
    for b in map(int, binario[::-1]):
        if b == 1:
            p = p*a % m
        a = a**2 % m

        # Agotamos el exponente
        n = (n-b) // 2
        if n == 0:
            break
    return p

# Ejercicio 4

def es_primo(p, n=10):
    """Aplica el algoritmo de Miller-Rabin n veces (por defecto n=10) a un número p
    
    Input: un entero positivo p al que se le realiza el test de Miller-Rabin y 
    opcionalmente el número de veces n que se realiza el test
    Output: True si p es probablemente primo, False si no es primo
    """

    # Escribimos p-1 como 2^u * s siendo s impar
    s = p - 1
    u = 0
    while s % 2 == 0:
        s = s // 2
        u += 1

    # Se realizan n tests de Miller-Rabin
    for _ in range(n):

        a = randint(2, p-2)
        a = powmod(a, s, p)

        # Si a = 1 o a = -1 pasa el test i
        if a not in (1, p-1):
            for _ in range(u-1):
                a = powmod(a, 2, p)

                # Pasa el test i
                if a == p-1:
                    break

                # No pasa el test i => no es primo
                elif a == 1:
                    return False

            # Llega a a^(p-1) sin encontrar -1 antes => no pasa el test 
            else:
                return False

    # Se han pasado los n test de Miller-Rabin
    return True

# Ejercicio 5

def raiz_babilonica(n):
    """Calcula la raíz cuadrada entera de un número n usando el método babilónico
    
    Input: entero positivo n
    Output: raíz cuadrada entera de n
    """

    x = n
    y = 1
    while x > y:
        x = (x+y) // 2
        y = n // x
    return x


def paso_enano_gigante(a, c, p):
    """Calcula el logaritmo en base a de c en Zp utilizando el método paso enano-paso gigante
    
    Input: tres enteros positivos a, c, p 
    Output: resultado de calcular el logaritmo en base a de c en Zp
    """

    s = raiz_babilonica(p) + 1

    # Generamos la primera lista
    L = [powmod(a, i*s, p) % p for i in range(1, s)]

    # Recorremos la segunda lista
    for i in range(s):
        val = c*powmod(a, i, p) % p
        # Si la intersección no es vacía
        if val in L:
            t = L.index(val) + 1
            return t*s - i

    return None

# Ejercicio 6

def jacobi(a, p):
    """Calcula el simbolo de Jacobi para (a / p)
    
    Input: dos enteros positivos a, p con a < p
    Output: símbolo de Jacobi de (a / p)
    """

    # Casos básicos
    if a == 0:
        return 0
    elif a == 1:
        return 1

    # Escribimos a como 2^e * b siendo b impar
    b = a
    e = 0
    while b % 2 == 0:
        b = b // 2
        e += 1

    # Propiedad (a^2 / p) = 1 con a != 0 en Zp (en este caso a = 2)
    if e % 2 == 0:
        s = 1
    # Si e no es par queda un (2/p) y vemos el simbolo
    else:
        if p % 8 in (1, 7):
            s = 1
        elif p % 8 in (3, 5):
            s = -1

    # Ley de reciprocidad cuadrática
    if p % 4 == 3 and b % 4 == 3:
        s = -s

    if b == 1:
        return s
    else:
        return s * jacobi(p % b, b)


def raicesmod(a, p):
    """Calcula las raices cuadradas de a en Zp
    
    Input: un entero positivo a y un primo p
    Output: (r, -r mod p) tal que r^2 = a mod p o None si no existe r
    """

    if jacobi(a, p) == 1:

        # n aleatorio tal que jacobi(n, p) = -1 (50%)
        n = randint(2, p - 1)
        while jacobi(n, p) != -1:
            n = randint(2, p - 1)

        # Escribimos n como 2^u * s siendo s impar
        s = p - 1
        u = 0
        while s % 2 == 0:
            s = s // 2
            u += 1

        b = powmod(n, s, p)
        r = powmod(a, (s + 1) / 2, p)
        a_s = powmod(a, s, p)

        # Recorremos las potencias pares de b hasta b^(2^u - 2)
        for k in range(2 ** (u-1)):
            if powmod(b, 2*k, p) == a_s:
                raiz = r*powmod(b, 2**u - k, p) % p
                return sorted([raiz, -raiz % p])

    return None

def raicesmod_pq(a, p, q):
    """ Calcula las raices cuadradas de a en Zn a partir de las raices cuadradas de a 
    en Zp y Zq siendo n = pq utilizando el teorema chino de los restos.

    Input: tres enteros positivos a, p y q
    Output: todas las raíces cuadradas de a en Zn siendo n = pq
    """

    n = p * q
    
    # Calculamos las raices de a en Zp y Zq
    raices_p = raicesmod(a, p)
    raices_q = raicesmod(a, q)
    
    # Utilizamos el teorema chino de los restos
    # Primero con r y s 
    # Segundo con -r y s
    x = (raices_p[0] + inverso(p, q)*(raices_q[0] - raices_p[0])*p) % n
    y = (raices_p[1] + inverso(p, q)*(raices_q[0] - raices_p[1])*p) % n
    
    return sorted([x, -x % n, y, -y % n])
    

# Ejercicio 7

def factorizacion_fermat(n):
    """Calcula la factorización de un número n utilizando el método de Fermat
    
    Input: entero positivo n
    Output: factorización de n
    """

    x = raiz_babilonica(n)
    y = x**2 - n
    raiz_y = raiz_babilonica(y)

    while raiz_y ** 2 != y:
        x += 1
        y = x**2 - n
        raiz_y = raiz_babilonica(y)
            
    return [x-raiz_y, x+raiz_y]

def rho_pollard(n):
    """Aplica el método rho de Pollard a un número n

    Input: entero positivo n
    Output: factor de n
    """

    def f(x, c):
        return (x**2 + c) % n
    
    for c in range(1, n):
        x = y = 2
        d = 1

        while d == 1:
            x = f(x, c)
            y = f(f(y, c), c)
            d = mcd(abs(x-y), n)[0]

        if d != n:
            return d
    
    return None

if __name__ == "__main__":
    # Ejercicio 1
    d = mcd(6546463456345687980998073, 24577113246345634563456)[0]
    print("mcd(6546463456345687980998073, 24577113246345634563456) = %d" % d)

    # Ejercicio 2
    inv = inverso(6546463456345687980998073, 7645)
    print("inverso de 6546463456345687980998073 en Z_7645 = %d" % inv)

    # Ejercicio 3
    pm = powmod(765474567, 87658567856785678567857887567, 34)
    print("765474567^87658567856785678567857887567 mod 34 = %d" % pm)

    # Ejercicio 4
    primo = es_primo(123456789101119)
    print("¿Es 123456789101119 primo? %r" % primo)

    # Ejercicio 5
    log = paso_enano_gigante(3, 57, 113)
    print("log base 3 de 57 en Z_113 = %d" % log)

    # Ejercicio 6
    raices = raicesmod(86466010171441, 123456789101119)
    print("raíces de 86466010171441 en Z_123456789101119 = %r" % raices)

    raices = raicesmod_pq(4, 3, 5)
    print("raíces de 4 en Z_15 = %r" % raices)

    # Ejercicio 7
    fermat = factorizacion_fermat(455459)
    print("factorización de fermat 455459 = %d * %d" % (fermat[0], fermat[1]))

    pollard = rho_pollard(455459)
    print("factor primo de 455459: %d" % pollard)

    # Ejercicio 8
    print("Tiempos comparados con funciones de GAP")
    print("Cada función se ejecuta 10000 veces para poder medir mejor el tiempo")
    print("mcd vs Gcd:\t%f\t%f" %  (0.23462543100049515, 0.010))
    print("inverso vs GcdRepresentation:\t%f\t%f" %  (0.04494377499941038, 0.064))
    print("powmod vs PowerModInt:\t%f\t%f" %  (0.29591969899956894, 0.035))
    print("es_primo vs IsPrime:\t%f\t%f" %  (2.3378746579992367, 0.012))
    print("paso_enano_gigante vs LogModShanks:\t%f\t%f" %  (0.40063602500049456, 0.053))
    print("raices_mod vs RootsMod:\t%f\t%f" %  (0.9637303819999943, 0.093))
    print("factorizacion_fermat vs FactorsInt:\t%f\t%f" %  (0.06012636800005566, 0.087))

    """  
    print("mcd tiempo: %f" % timeit.timeit(lambda: mcd(6546463456345687980998073, 24577113246345634563456), number=10000))
    print("inverso tiempo: %f" % timeit.timeit(lambda: inverso(6546463456345687980998073, 7645), number=10000))
    print("powmod tiempo: %f" % timeit.timeit(lambda: powmod(765474567, 87658567856785678567857887567, 34), number=10000))
    print("es_primo tiempo: %f" % timeit.timeit(lambda: es_primo(123456789101119), number=10000))
    print("paso_enano_gigante tiempo: %f" % timeit.timeit(lambda: paso_enano_gigante(3, 57, 113), number=10000))
    print("raicesmod tiempo: %f" % timeit.timeit(lambda: raicesmod(86466010171441, 123456789101119), number=10000))
    print("factorizacion_fermat tiempo: %f" % timeit.timeit(lambda: factorizacion_fermat(455459), number=10000))
    """

    """
    GAP tiempos
    Gcd(6546463456345687980998073, 24577113246345634563456) = 10 milisegundos
    GcdRepresentation(6546463456345687980998073, 7645) = 64 milisegundos
    PowerModInt(765474567, 87658567856785678567857887567, 34) = 35 milisegundos
    IsPrime(123456789101119) = 12 milisegundos
    LogModShanks(57, 3, 113) = 53 milisegundos
    RootsMod(86466010171441, 123456789101119) = 93 milisegundos
    FactorsInt(455459) = 87 milisegundos
    """