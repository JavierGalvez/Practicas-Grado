# Javier Gálvez Obispo

from more_itertools import run_length
from itertools import zip_longest
from operator import xor, mul, add
from math import prod
from random import randint

# Función utilizada por la función golomb
def desplazar(secuencia, i):
    """Desplaza una secuencia i posiciones hacia la derecha"""
    return secuencia[-i:] + secuencia[:-i]

# Función utilizada por la función golomb
def hamming(s1, s2):
    """Calcula la distancia de Hamming entre dos secuencias de bits"""
    return sum(list(map(xor, s1, s2)))

def golomb(secuencia):
    """Comprueba si una secuencia de bits cumple los postulados de Golomb
    
    Input: string con la secuencia de bits
    Output: True si cumple todos los postulados, False en otro caso
    """

    # Primer postulado
    secuencia_valida = abs(secuencia.count(1) - secuencia.count(0)) <= 1


    # Segundo postulado
    if secuencia_valida:
        while secuencia[0] == secuencia[-1]:
            secuencia = desplazar(secuencia, 1)

        cuenta_rachas = dict()
        for _, longitud in run_length.encode(secuencia):
            cuenta_rachas[longitud] = cuenta_rachas.get(longitud, 0) + 1

        for i in range(1, len(cuenta_rachas)):
            if cuenta_rachas.get(i, -1) != cuenta_rachas.get(i+1, -1)*2:
                # Comprobamos si falla en las 2 rachas más largas y permitimos
                # que ambas sean de longitud 1
                secuencia_valida = i == len(cuenta_rachas)-1 \
                                   and cuenta_rachas.get(i, 0) == 1 \
                                   and cuenta_rachas.get(i+1, 0) == 1
                break

        # Tercer postulado
        if secuencia_valida:
            distancia = hamming(secuencia, desplazar(secuencia, 1))
            secuencia_valida = all(hamming(secuencia, desplazar(secuencia, i)) == distancia \
                                   for i in range(2, len(secuencia)))

    return secuencia_valida

def lfsr(coefs, semilla, k=None):
    """Función que implementa registros lineales de desplazamiento con retroalimentación

    Input: coefs, lista con los coeficientes del polinomio asociado ordedanos de c_L a c_1
           semilla, lista con la semilla que se utiliza
           k, tamaño máximo de la secuencia de salida o None para alcanzar el período máximo
    Output: secuencia de bits
    """

    salida = semilla.copy()

    n = len(semilla)

    # Si no se especifica un valor para k se llega al período máximo
    if k is None:
        estado = tuple(semilla)
        vistos = set()
        
        while estado not in vistos:
            vistos.add(estado)
            s = sum(map(mul, coefs, estado)) % 2
            salida.append(s)
            estado = tuple(salida[-n:])

        salida = salida[:-n]

    # Secuencia de longitud k
    else:
        for _ in range(k-len(semilla)):
            s = sum(map(mul, coefs, salida[-n:])) % 2
            salida.append(s)
    
    return salida

def nlfsr(monomios, semilla, k=None):
    """Función que implementa registros no lineales de desplazamiento con retroalimentación

    Input: monomios, lista con los exponentes de las variables de cada monomio
           semilla, lista con la semilla que se utiliza
           k, tamaño máximo de la secuencia de salida o None para alcanzar el período máximo
    Output: secuencia de bits
    """

    salida = semilla.copy()

    n = len(semilla)

    # Si no se especifica un valor para k se llega al período máximo
    if k is None:
        estado = tuple(semilla)
        vistos = set()
        
        while estado not in vistos:
            vistos.add(estado)
            s = sum([prod(map(pow, estado, mon)) for mon in monomios]) % 2
            salida.append(s)
            estado = tuple(salida[-n:])

        salida = salida[:-n]

    # Secuencia de longitud k
    else:
        for _ in range(k-len(semilla)):
            s = sum([prod(map(pow, salida[-n:], mon)) for mon in monomios]) % 2
            salida.append(s)

    return salida

def geffe(lfsr1, lfsr2, lfsr3, k):
    """Función que el generador de Geffe

    Input: tres parejas (coefs, semilla) que definen tres LFSRs
           k, tamaño de la secuencia de salida
    Output: secuencia de bits
    """

    # Generamos una secuencia de tamaño k con cada LFSR
    x = [lfsr(*args, k) for args in (lfsr1, lfsr2, lfsr3)]

    # Aplicamos el generador de Geffe a las secuencias obtenidas
    salida = list(map(lambda x1,x2,x3: (x1*x2 + x2*x3 + x3)%2, *x))

    return salida

def berlekamp_massey(secuencia):
    """Implementación del algoritmo Berlekamp-Massey según se especifica en el libro
    Handbook of Applied Cryptography (6.30)

    Input: secuencia de bits 
    Output: complejidad lineal de la secuencia,
            LFSR que genera la secuencia
    """

    C = [1]
    L = 0
    m = -1
    B = [1]
    T = []
    
    for n, s_n in enumerate(secuencia):
        d = (s_n + sum([C[i] * secuencia[n-i] for i in range(1, L+1)])) % 2

        if d == 1:
            T = C.copy()
            B_aux = [0]*(n-m) + B
            C = [ c^b for c, b in zip_longest(C, B_aux, fillvalue=0)]

            if L <= n/2:
                L = n + 1 - L
                m = n
                B = T.copy()

        # print(s_n, d, T, C, L, m, B, n+1)
    
    # Generamos el polinomio asociado al LFSR 
    polinomio_lfsr = C[:0:-1]

    return L, polinomio_lfsr

# Función para pasar una lista a string
def list_to_str(l):
    return "".join(map(str, l))

if __name__ == "__main__":
    # Ejercicio 1 - Postulados de Golomb
    print("### Ejercicio 1 ###")
    secuencia = [0, 1, 0, 0, 1, 1, 0, 1]
    print("¿Cumple", list_to_str(secuencia), "los postulados de Golomb?", golomb(secuencia))
    secuencia = [1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0]
    print("¿Cumple", list_to_str(secuencia), "los postulados de Golomb?", golomb(secuencia))
    secuencia = [0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1]
    print("¿Cumple", list_to_str(secuencia), "los postulados de Golomb?", golomb(secuencia))

    # Ejercicio 2 - LFSR
    print("\n### Ejercicio 2 ###")
    print("Dependencia del periodo de la semilla con polinomios reducibles")
    print("C(x) = x^4 + x^3 + x + 1 = (x + 1)(x^3 + 1)")
    secuencia = lfsr([1, 1, 0, 1], [1, 1, 1, 1])
    print("Semilla = 1111", "=> Resultado =", list_to_str(secuencia), "| Periodo =", len(secuencia))
    secuencia = lfsr([1, 1, 0, 1], [1, 1, 0, 0])
    print("Semilla = 1100", "=> Resultado =", list_to_str(secuencia), "| Periodo =", len(secuencia))

    print("\nIndependecia del periodo de la semilla con polinomios irreducibles")
    print("C(x) = x^4 + x^3 + x^2 + x + 1")
    secuencia = lfsr([1, 1, 1, 1], [1, 1, 1, 1])
    # s15 -> s14 -> s13 -> s11 -> s7 -> s15 periodo = 5
    print("Semilla = 1111", "=> Resultado =", list_to_str(secuencia), "| Periodo =", len(secuencia))
    secuencia = lfsr([1, 1, 1, 1], [0, 1, 0, 0])
    # s4 -> s9 -> s2 -> s5 -> s10 -> s4 periodo = 5
    print("Semilla = 0100", "=> Resultado =", list_to_str(secuencia), "| Periodo =", len(secuencia))

    print("\nMaximilidad del periodo con polinomios primitivos")
    print("C(x) = x^4 + x + 1")
    secuencia = lfsr([1, 0, 0, 1], [1, 1, 1, 1])
    print("Semilla = 1111", "=> Resultado =", list_to_str(secuencia), "| Periodo =", len(secuencia))
    secuencia = lfsr([1, 0, 0, 1], [0, 1, 0, 0])
    print("Semilla = 0100", "=> Resultado =", list_to_str(secuencia), "| Periodo =", len(secuencia))

    # ((x and y) or not z) xor t
    print("\n### Ejercicio 3 ###")
    print("NLFSR = ((x AND y) OR NOT z) XOR t")
    secuencia = nlfsr([[0, 0, 0, 0], [1, 1, 1, 0], [0, 0, 1, 0], [0, 0, 0, 1]], [1, 0, 1, 1])
    print("Semilla = 1011", "=> Resultado =", list_to_str(secuencia), "| Periodo =", len(secuencia))

    print("\n### Ejercicio 4 ###")
    """
    Polinomios utilizados para el generador de Geffe:
        x^3 + x + 1   => longitud del periodo = 7
        x^4 + x + 1   => longitud del periodo = 15
        x^5 + x^2 + 1 => longitud del periodo = 31
    Longitud del periodo del generador de Geffe = mcm(7, 15, 31) = 7 * 15 * 31 = 3255
    """

    lfsr1 = ([1, 0, 1], [1, 1, 0])
    lfsr2 = ([1, 0, 0, 1], [1, 0, 1, 0])
    lfsr3 = ([1, 0, 0, 1, 0], [1, 0, 0, 1, 1])

    secuencia = geffe(lfsr1, lfsr2, lfsr3, 3255*2)
    print("Comprobación del periodo del generador de Geffe:", secuencia[:3255] == secuencia[3255:])

    # Cifrado en flujo
    mensaje = [randint(0, 1) for _ in range(30)]
    llave = geffe(lfsr1, lfsr2, lfsr3, len(mensaje))
    print("\nMensaje a cifrar:\t", list_to_str(mensaje))
    print("Llave utilizada:\t", list_to_str(llave))
    mensaje_cifrado = list(map(xor, mensaje, llave))
    print("Mensaje cifrado:\t", list_to_str(mensaje_cifrado))
    print("Mensaje descifrado:\t", list_to_str(list(map(xor, mensaje_cifrado, llave))))

    print("\n### Ejercicio 5 ###")
    print("Ejemplo Handbook of Applied Cryptography (6.33)")
    secuencia = [0, 0, 1, 1, 0, 1, 1, 1, 0]
    complejidad, polinomio = berlekamp_massey(secuencia)
    print("Secuencia:", list_to_str(secuencia), "=> Complejidad =", complejidad, "| LFSR =", polinomio)

    print("\nEjemplo apuntes Jesús")
    secuencia = [1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1]
    complejidad, polinomio = berlekamp_massey(secuencia)
    print("Secuencia:", list_to_str(secuencia), "=> Complejidad =", complejidad, "| LFSR =", polinomio)

    print("\nEjemplos utilizados en el ejercicio 2")
    s1 = lfsr([1, 0, 1], [1, 1, 0])
    s2 = lfsr([1, 0, 0, 1], [1, 0, 1, 0])
    s3 = lfsr([1, 0, 0, 1, 0], [1, 0, 0, 1, 1])

    complejidad, polinomio = berlekamp_massey(s1)
    print("Secuencia:", list_to_str(s1), "=> Complejidad =", complejidad, "| LFSR =", polinomio)

    complejidad, polinomio = berlekamp_massey(s2)
    print("Secuencia:", list_to_str(s2), "=> Complejidad =", complejidad, "| LFSR =", polinomio)

    complejidad, polinomio = berlekamp_massey(s3)
    print("Secuencia:", list_to_str(s3), "=> Complejidad =", complejidad, "| LFSR =", polinomio)

    mcm = len(s1) * len(s2)
    s1 = lfsr([1, 0, 1], [1, 1, 0], mcm)
    s2 = lfsr([1, 0, 0, 1], [1, 0, 1, 0], mcm)

    # El periodo de los lFSRs obtenidos de la suma y el producto debe tener periodo mcm(complejidad_s1, complejidad_s2)
    # La complejidad para la suma debe ser <= complejidad_s1 + complejidad_s2
    print("\nSuma de secuencias")
    suma = list(map(xor, s1, s2))
    complejidad, polinomio = berlekamp_massey(suma)
    print("Secuencia:", list_to_str(suma), "=> Complejidad =", complejidad, "| LFSR =", polinomio)
    semilla = [randint(0, 1) for _ in range(len(polinomio))]
    secuencia = lfsr(polinomio, semilla)
    print("Semilla =", list_to_str(semilla), "=> Resultado =", list_to_str(secuencia), "| Periodo =", len(secuencia))

    # La complejidad para el producto debe ser <= complejidad_s1 * complejidad_s2
    print("\nProducto de secuencias")
    producto = list(map(mul, s1, s2))
    complejidad, polinomio = berlekamp_massey(producto)
    print("Secuencia:", list_to_str(producto), "=> Complejidad =", complejidad, "| LFSR =", polinomio)
    semilla = [randint(0, 1) for _ in range(len(polinomio))]
    secuencia = lfsr(polinomio, semilla)
    print("Semilla =", list_to_str(semilla), "=> Resultado =", list_to_str(secuencia), "| Periodo =", len(secuencia))