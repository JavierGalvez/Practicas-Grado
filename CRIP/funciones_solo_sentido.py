# Javier Gálvez Obispo

import random
import hashlib
from aritmetica_modular import *

def knapsack_llave_privada(n, cota):
    """Genera una llave privada para la función mochila (knapsack).

    Input: n, tamaño de la secuencia.
           cota, máxima diferencia entre a_i y a_(i+1).
    Output: secuencia, secuencia super-creciente de números positivos.
            n, entero positivo tal que n > sum(secuencia).
            u, entero positivo tal que gcd(n, u) = 1.
    """

    secuencia = []
    suma = 0
    for _ in range(n):
        k = random.randint(suma+1, suma+cota+1)
        secuencia.append(k)
        suma += k
    
    n = random.randint(suma+1, suma+cota+1)
    u = random.randint(2, n-2)
    while mcd(u, n)[0] != 1:
        u = random.randint(2, n-2)

    return secuencia, n, u

def knapsack_llave_publica(llave_privada):
    """Genera una llave pública para la función mochila (knapsack) a partir de una
    llave privada dada.

    Input: llave privada para la función mochila (knapsack) (secuencia, n, u)
    Output: secuencia (a*_1, ..., a*_k) obtenida de hacer a*_i = ua_i mod n
    """

    secuencia, n, u = llave_privada
    return [(s*u) % n for s in secuencia]

def knapsack_cifrar(mensaje, llave_publica):
    """Cifra un mensaje utilizando la función mochila (knapsack).

    Input: mensaje, secuencia de bits con la misma longitud que la llave pública
           llave_publica para la función mochila (knapsack) (a*_1, ..., a*_k)
    Output: mensaje cifrado con la función f(x1, ..., xk) = sum(x_i * a*_i) i=1..k
    """

    return sum(m*k for m, k in zip(mensaje, llave_publica))

def knapsack_descifrar(mensaje_cifrado, llave_privada):
    """Descifra un mensaje cifrado por la función mochila (knapsack) utilizando
    el algoritmo voraz para resolver el problema de la mochila.

    Input: mensaje cifrado.
           llave_privada de la función mochila (knapsack).
    Output: mensaje descifrado, secuencia de bits original.
    """

    secuencia, n, u = llave_privada
    inv_u = inverso(u, n)
    val = (mensaje_cifrado*inv_u) % n

    usados = set()
    posibles = secuencia[:]
    while val != 0:
        posibles = [x for x in posibles if x <= val and x not in usados]

        # Si ya no quedan valores menores que val => no hay solución
        if len(posibles) == 0:
            return None

        elegido = max(posibles)

        val -= elegido
        usados.add(elegido)

    return [int(s in usados) for s in secuencia]

def siguiente_primo(n):
    """Obtiene el primer número primo p >= n"""

    p = n if n % 2 == 1 else n+1
    while not es_primo(p):
        p += 2
    return p

def ejercicio2(numero_identidad, n):
    """Calcula f^(-1)(n) siendo f: Zp -> Zp, x -> alpha^x donde
    p es un número primo >= numero_identidad tal que (p-1)/2 también es primo y
    alpha es un elemento primitivo de Z*p.

    Input: numero_identidad: valor mínimo que puede tomar p.
           n: número del que se quiere obtener el inverso.
    Output: p, alpha, x tal que alpha^x mod p = n.
    """

    # Obtenemos un p primo tal que (p-1)/2 también es primo
    p = siguiente_primo(numero_identidad)
    while not es_primo((p-1) // 2):
        p = siguiente_primo(p+2)

    # alpha alteatorio hasta que jacobi (a / p) = -1
    alpha = random.randint(2, p-2)
    while jacobi(alpha, p) != -1:
        alpha = random.randint(2, p-2)

    """
    # Otra forma de obtener el generador alpha
    divs = [2, (p-1) // 2)]
    for i in range(2, p-1):
        if all(pow(i, d, p) != 1 for d in divs):
            alpha = i
            break
    """
    
    x = paso_enano_gigante(alpha, n, p)
    return p, alpha, x

def obtener_pq(n, x, y):
    """Calcula p, q tal que p*q = n conociendo x, y tal que x^2 = y^2 mod n
    
    Input: n, producto de dos números primos desconocidos
           x, y tal que x^2 = y^2 mod n
    Output: p, q tal que p*q = n
    """

    p = mcd((x-y)%n, n)[0]
    q = n // p
    return sorted([p, q])

def merkle_damgard(v_inicial, mensaje, n, a0, a1):
    """Implementación de una función resumen usando la construcción de Merkle-Damgard
    y tomando la función h(b, x) = x^2 * a0^b * a1^(1-b) como función de compresión.

    Input: v_inicial, vector inicial.
           mensaje, secuencia de bits de la que se obtiene el resumen.
           n, un número primo lo suficientemente grande.
           a0, a1 dos cuadrados arbitrarios módulo n.
    """

    # Función de compresión
    def h(b, x):
        val = pow(x, 2, n)
        if b == 1:
            val = (val*a0) % n
        else:
            val = (val*a1) % n
        return val

    # h(b2, h(b1, h(b0, x)))
    x = v_inicial
    for b in mensaje:
        x = h(b, x)

    return x

def rsa_generar_llaves(numero_identidad, fecha):
    """Genera las llaves pública y privada para un sistema RSA dados los valores 
    mínimos que pueden tomar p y q

    Input: numero_identidad, valor mínimo que puede tomar p
           fecha, valor mínimo que puede tomar q
    Output: (n, e), llave pública del sistema RSA
            d, llave privada del sistema RSA
    """

    p = siguiente_primo(numero_identidad)
    q = siguiente_primo(fecha)

    n = p * q
    phi_n = (p-1)*(q-1)

    # e tal que gcd(e, phi(n)) = 1
    e = random.randint(2, n-2)
    while mcd(e, phi_n)[0] != 1:
        e = random.randint(2, n-2)
    
    d = inverso(e, phi_n)

    return n, e, d

def rsa_cifrar(m, n, e):
    """Cifra un mensaje utilizando la función RSA f(x) = x^e
    
    Input: m, mensaje a cifrar.
           (n, e), llave pública RSA
    Output: mensaje cifrado m^e mod n.
    """

    return pow(m, e, n)

def rsa_descifrar(c, n, d):
    """Descifra un mensaje cifrado con RSA

    Input: c, mensaje cifrado.
           (n, d) llave privada RSA 
    Output: mensaje descifrado c^d mod n.
    """

    return pow(c, d, n)

def rsa_obtener_pq(n, e, d):
    """Calcula p y q tal que p*q = n conociendo las llaves pública y privada de un
    sistema RSA

    -- Explicación del método aplicado --
    Se quiere encontrar un par x, y tal que x^2 = y^2 mod n para aplicar la misma idea
    utilizada en el ejercicio 3 con la que se obtienen los factores de n.
    Puesto que n no es primo x^2 - 1 = 0 tiene más de dos soluciones en Zn.
    Utilizamos el mismo método utilizado en Miller-Rabin para encontrar un número y
    distinto de +-1 que cumpla con y^2 = 1.

    Input: (n, e), d llaves pública y privada del sistema RSA
    Output: p, q tal que p*q = n
    """

    # Escribir d*e - 1 como 2^a * b siendo b impar
    b = d*e - 1
    a = 0
    while b % 2 == 0:
        b = b // 2
        a += 1

    p = None
    while p is None:
        x = random.randint(1, n-1)

        # Si gcd(x, n) != 1 entonces hemos encontrado un factor de n
        if mcd(x, n)[0] == 1:
            y = pow(x, b, n)

            # Si y = +-1 mod n falla y se prueba con otro x
            if y not in (1, n-1):
                while y not in (1, n-1):
                    z = y
                    y = pow(y, 2, n)

                # Si y = 1 mod n, hemos encontrado los factores
                # Si y = -1, falla y se prueba con otro x
                if y == 1:
                    p = mcd(n, z-1)[0]
        else:
            p = mcd(x, n)[0]

    q = n // p
    return sorted([p, q])

def resumen_sha1(mensaje):
    """Obtiene el resumen de un mensaje utilizando SHA1"""

    sha1 = hashlib.sha1()
    sha1.update(str.encode(mensaje))
    
    return int(sha1.hexdigest(), 16)

def rsa_verificar_firma(mensaje, firma, n, e):
    """Verifica una firma hecha con RSA
    
    Input: (mensaje, firma) mensaje junto a su firma
           (n, e) llave pública del sistema RSA
    Output: True si la firma es válida, False en caso contrario
    """

    resumen = resumen_sha1(mensaje)
    return pow(firma, e, n) == (resumen % n)

def list_to_str(l):
    return "".join(map(str, l))

if __name__ == "__main__":
    # Ejercicio 1
    print("## Ejercicio 1 ##")
    # llave_privada = [[1, 3, 7, 15, 31, 63, 127, 255], 557, 323]  # ejemplo Notes on cryptography
    llave_privada = knapsack_llave_privada(8, 30)
    llave_publica = knapsack_llave_publica(llave_privada)

    print("Llave privada:", llave_privada)
    print("Llave pública:", llave_publica)

    mensaje = [0, 1, 1, 0, 0, 1, 0, 1]  # e en 8-bit ASCII
    mensaje_cifrado = knapsack_cifrar(mensaje, llave_publica)
    mensaje_descifrado = knapsack_descifrar(mensaje_cifrado, llave_privada)

    print("Mensaje:\t\t", list_to_str(mensaje))
    print("Mensaje cifrado:\t",mensaje_cifrado)
    print("Mensaje descifrado:\t",list_to_str(mensaje_descifrado))

    # Ejercicio 2
    print("\n## Ejercicio 2 ##")
    numero_identidad = 75930561
    fecha = 19981223
    p, alpha, x = ejercicio2(numero_identidad, fecha)
    print("numero de identidad =", numero_identidad, "\nfecha =", fecha)
    print("p =", p, "| alpha =", alpha, "| x =", x, "| alpha^x mod p =", pow(alpha, x, p))

    # Ejercicio 3
    print("\n## Ejercicio 3 ##")
    n = 48478872564493742276963
    x = 12
    y = 37659670402359614687722
    p, q = obtener_pq(n, x, y)
    print("p =", p, "| q =", q) 
    print("Comprobaciones:")
    print("p primo =", es_primo(p), "| q primo =", es_primo(q), "| (p*q == n) =", p*q == n)
    print("Raices 144 en Zn usando raicesmod_pq (practica 1) =", raicesmod_pq(144, p, q))
    
    # Ejercicio 4
    print("\n## Ejercicio 4 ##")
    n = 48478872564493742276963
    a0 = pow(random.randint(1, n-1), 2, n)
    a1 = pow(random.randint(1, n-1), 2, n)
    mensaje = [random.randint(0, 1) for _ in range(100)]
    print("Mensaje:", list_to_str(mensaje))
    print("Resumen:", merkle_damgard(1, mensaje, n, a0, a1))

    # Ejercicio 5
    print("\n## Ejercicio 5 ##")
    c = 1234567890
    n, e, d = rsa_generar_llaves(numero_identidad, fecha)
    m = rsa_descifrar(c, n, d)
    print("x^e =\t", c)
    print("x   =\t", m)
    print("x^e =\t", rsa_cifrar(m, n, e))
    
    # Ejercicio 6
    print("\n## Ejercicio 6 ##")
    n = 50000000385000000551
    e = 5
    d = 10000000074000000101
    p, q = rsa_obtener_pq(n, e, d)
    print("n =", n)
    print("p =", p, "| q =", q) 
    print("Comprobaciones:")
    print("p primo =", es_primo(p), "| q primo =", es_primo(q), "| (p*q == n) =", p*q == n)

    # Ejercicio 7
    print("\n## Ejercicio 7 ##")
    # Firma RSA
    mensaje = "Prueba de verificación de una firma RSA utilizando SHA1 como función resumen"
    print("Mensaje:\t", list_to_str(mensaje))

    # Generar llaves RSA
    n, e, d = rsa_generar_llaves(numero_identidad, fecha)

    # Obtener resumen del mensaje
    resumen = resumen_sha1(mensaje)
    print("Resumen:\t", resumen)

    # Firmar el resumen / cifrar con la llave privada
    firma = rsa_cifrar(resumen, n, d)
    print("Firma:\t\t", firma)

    # Verificar la firma
    verificacion = rsa_verificar_firma(mensaje, firma, n, e)
    print("Verificación:\t", verificacion)