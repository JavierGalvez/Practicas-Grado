# -*- coding: utf-8 -*-
# Javier Gálvez Obispo

import numpy as np
import matplotlib.pyplot as plt

from cinematico_inverso import pci
from cinematico_directo import animacion_trayectoria_pcd, pcd

def trayectoria434(qI, qD, qA, qF, t1, t2, t3):
    c10 = qI
    c11 = 0
    c12 = 0
    c20 = qD
    c30 = qF
    c31 = 0
    c32 = 0

    matriz = np.array([[1, 1, 0, 0, 0, 0, 0],
                       [3/t1, 4/t1, -1/t2, 0, 0, 0, 0],
                       [6/t1**2, 12/t1**2, 0, -2/t2**2, 0, 0, 0],
                       [0, 0, 1, 1, 1, 0, 0],
                       [0, 0, 0, 0, 0, -1, 1],
                       [0, 0, 1/t2, 2/t2, 3/t2, -3/t3, 4/t3],
                       [0, 0, 0, 2/t2**2, 6/t2**2, 6/t3**2, -12/t3**2]
                      ])
    vector = np.array([qD-qI, 0, 0, qA-qD, qA-qF, 0, 0])
    coefs = np.dot(np.linalg.inv(matriz), vector)

    f1 = [coefs[1], coefs[0], c12, c11, c10]
    f2 = [coefs[4], coefs[3], coefs[2], c20]
    f3 = [coefs[6], coefs[5], c32, c31, c30]
    return (f1, f2, f3)

def evaluar_polinomio(coefs, x):
    f = 0
    l = len(coefs)-1
    for i, c in enumerate(coefs):
        f += c * x**(l-i)
    return f

def evaluar_trayectoria(tiempos, periodo, f1s, f2s):
    q1s, q2s = [], []
    
    
    for k in range(len(f1s)):
        pasos = int(tiempos[k] / periodo)
        for i in range(pasos):
            # Cambio de variable para normalizar el tiempo
            t_hasta_seg = sum(tiempos[:k])
            tau = i*periodo + t_hasta_seg
            t = (tau - t_hasta_seg) / tiempos[k]
            
            # Segundo cambio de variable para el último segmento
            if k == len(trayectoria_q1)-1:
                t = t - 1
                
            q1s.append(evaluar_polinomio(f1s[k], t))
            q2s.append(evaluar_polinomio(f2s[k], t))
           
    # Último punto
    q1s.append(evaluar_polinomio(f1s[2], 0))
    q2s.append(evaluar_polinomio(f2s[2], 0))
    
    return q1s, q2s


l1 = l2 = 1
qI = pci(1, 0, l1, l2)
qD = pci(1, 0.1, l1, l2)
qA = pci(1.5, 0.1, l1, l2)
qF = pci(1.5, 0, l1, l2)

ti = [1, 1, 1]
trayectoria_q1 = trayectoria434(qI[0], qD[0], qA[0], qF[0], *ti)
trayectoria_q2 = trayectoria434(qI[1], qD[1], qA[1], qF[1], *ti)

periodo = 0.05

q1s, q2s = evaluar_trayectoria(ti, periodo, 
                               trayectoria_q1, trayectoria_q2)
animacion_trayectoria_pcd(q1s, q2s, l1, l2)

# Comprobación que pasa por por los puntos dados
print("Posición inicial:", pcd(q1s[0], q2s[0], l1, l2))
print("Posición al principio del segundo segmento:", 
      pcd(q1s[20], q2s[20], l1, l2))
print("Posición al principio del tercer segmento:", 
      pcd(q1s[40], q2s[40], l1, l2))
print("Posición final:", pcd(q1s[-1], q2s[-1], l1, l2))

# Cálculo de la velocidad
v_q1 = [np.polyder(f) for f in trayectoria_q1]
v_q2 = [np.polyder(f) for f in trayectoria_q2]
v_q1s, v_q2s = evaluar_trayectoria(ti, periodo, v_q1, v_q2)

# Cálculo de la aceleracián
a_q1 = [np.polyder(f) for f in v_q1]
a_q2 = [np.polyder(f) for f in v_q2]
a_q1s, a_q2s = evaluar_trayectoria(ti, periodo, a_q1, a_q2)

# Pintar gráficas
tiempo = [i*0.05 for i in range(int(sum(ti)/periodo)+1)]
plt.plot(tiempo, q1s, label="q1")
plt.plot(tiempo, q2s, label="q2")
plt.legend()
plt.show()

plt.plot(tiempo, v_q1s, label="v_q1")
plt.plot(tiempo, v_q2s, label="v_q2")
plt.legend()
plt.show()

plt.plot(tiempo, a_q1s, label="a_q1")
plt.plot(tiempo, a_q2s, label="a_q2")
plt.legend()
plt.show()