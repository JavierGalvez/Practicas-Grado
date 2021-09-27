import numpy as np
import matplotlib.pyplot as plt

def pcd(q1, q2, l1, l2):
    x = l1*np.cos(q1) + l2*np.cos(q1+q2)
    y = l1*np.sin(q1) + l2*np.sin(q1+q2)
    return (x, y)

def dibujar_trayectoria_pcd(q1s, q2s, l1, l2):
    # Calculamos todos los puntos y los pintamos
    puntos = [pcd(q1, q2, l1, l2) for q1, q2 in zip(q1s, q2s)]
    plt.plot(*zip(*puntos))

    dibujar_robot(q1s[-1], q2s[-1], l1, l2)

    # Centrar el origen de coordenadas
    rango = np.arange(-l1-l2-1, l1+l2+2)
    plt.xticks(rango)
    plt.yticks(rango)

    plt.show()

def dibujar_robot(q1, q2, l1, l2):
    x0, y0 = 0, 0                       # Posición de la articulación 1
    x1, y1 = pcd(q1, 0, l1, 0)          # Posición de la articulación 2
    x2, y2 = pcd(q1, q2, l1, l2)        # Posición del extremo del robot

    x, y = [x0, x1, x2], [y0, y1, y2]   # Coordenadas de la trayectoria
    plt.plot(x, y, 'k')                 # Traza la trayectoria
    plt.plot(x0, y0, 'k.')              # Dibuja la articulación 1
    plt.plot(x1, y1, 'k.')              # Dibuja la articulación 2

def animacion_trayectoria_pcd(q1s, q2s, l1, l2):
    n = min(len(q1s), len(q2s))
    for i in range(1, n):
        plt.clf()
        dibujar_trayectoria_pcd(q1s[0:i], q2s[0:i], l1, l2)
        plt.pause(0.001)

if __name__ == "__main__":
    n = 100
    l1 = l2 = 2

    q1s = [np.pi / 4] * n
    q2s = np.linspace(0, np.pi/2, n)
    dibujar_trayectoria_pcd(q1s, q2s, l1, l2)

    q1s = np.linspace(np.pi/4, np.pi/2, n)
    q2s = np.linspace(0, np.pi/2, n)
    dibujar_trayectoria_pcd(q1s, q2s, l1, l2)
    
    q1s = [i*np.pi / n for i in range(n+1)]
    q2s = q1s[:n//2+1] + q1s[n//2-1::-1]
    animacion_trayectoria_pcd(q1s, q2s, l1, l2)