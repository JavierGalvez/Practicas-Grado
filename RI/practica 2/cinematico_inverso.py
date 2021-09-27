import numpy as np
import matplotlib.pyplot as plt

from cinematico_directo import dibujar_robot

def pci(x, y, l1, l2):
    cosq2 = (x**2 + y**2 - l1**2 - l2**2) / (2*l1*l2)
    sinq2 = np.sqrt(1-cosq2**2)

    # q1 = np.arctan(y/x) - np.arctan(l2*sinq2 / (l1 + l2*cosq2))
    # q2 = np.arctan(sinq2/cosq2)

    q1 = np.arctan2(y, x) - np.arctan2(l2*sinq2, (l1 + l2*cosq2))
    q2 = np.arctan2(sinq2, cosq2)

    q1_neg = np.arctan2(y, x) - np.arctan2(l2*(-sinq2), (l1 + l2*cosq2))
    q2_neg = np.arctan2(-sinq2, cosq2)
    
    return (q1, q2, q1_neg, q2_neg)

def dibujar_trayectoria_pci(xs, ys, l1, l2, qi_anteriores):
    # Pintamos la trayectoria
    plt.plot(xs, ys)

    # Pintamos el robot
    q1, q2, q1_neg, q2_neg = pci(xs[-1], ys[-1], l1, l2)
    
    if qi_anteriores is not None:
        variacion_q1 = abs(qi_anteriores[0]-q1)
        variacion_q1_neg = abs(qi_anteriores[0]-q1_neg)
        
        # Los dos primeros casos son para el cambio del tercer cuadrante 
        # al cuarto que se pasa de 3pi/2 a -pi/2 o el caso contrario. 
        # Entonces, la diferencia de los ángulos es muy grande aunque 
        # en realidad la variación en el espacio es pequeña
        if variacion_q1 > np.pi + np.pi/2:
            qi_usados = (q1, q2)
        elif variacion_q1_neg > np.pi + np.pi/2:
            qi_usados = (q1_neg, q2_neg)
            
        # Se compara cuál de los dos ángulos es más próximo
        elif variacion_q1 < variacion_q1_neg:
            qi_usados = (q1, q2)
        else:
            qi_usados = (q1_neg, q2_neg)
    else:
        qi_usados = (q1, q2)
    
    dibujar_robot(*qi_usados, l1, l2)

    # Centrar el origen de coordenadas
    rango = np.arange(-l1-l2-1, l1+l2+2)
    plt.xticks(rango)
    plt.yticks(rango)

    plt.show()
    
    return qi_usados

def animacion_trayectoria_pci(xs, ys, l1, l2):
    n = min(len(xs), len(ys))
    qi_anteriores = None
    for i in range(1, n):
        plt.clf()
        qi_anteriores = dibujar_trayectoria_pci(xs[0:i], ys[0:i], 
                                                l1, l2, qi_anteriores)
        plt.pause(0.001)

n = 100
l1 = l2 = 2

xs = np.linspace(2, 0, n)
ys = np.linspace(0, 2, n)
animacion_trayectoria_pci(xs, ys, l1, l2)

xs = np.linspace(1, -2, n)
ys = [1] * n
animacion_trayectoria_pci(xs, ys, l1, l2)

xs = np.linspace(1, -1, n)
ys = [0] * n
animacion_trayectoria_pci(xs, ys, l1, l2)

xs = np.linspace(-2, 2, n)
ys = np.linspace(0, 1, n)
animacion_trayectoria_pci(xs, ys, l1, l2)