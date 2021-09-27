import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d

def rotacionX(angulo):
    r = np.radians(angulo)
    return np.array([[1, 0, 0], 
                    [0, np.cos(r), -np.sin(r)], 
                    [0, np.sin(r), np.cos(r)]])

def rotacionY(angulo):
    r = np.radians(angulo)
    return np.array([[np.cos(r), 0, np.sin(r)],
                     [0, 1, 0],
                     [-np.sin(r), 0, np.cos(r)]])

def rotacionZ(angulo):
    r = np.radians(angulo)
    return np.array([[np.cos(r), -np.sin(r), 0], 
                     [np.sin(r), np.cos(r), 0],
                     [0, 0, 1]])

pxB = np.array([ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 10,
                10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 12, 13,
                14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14])
pyB = np.array([ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
                 2,  3,  4,  5,  6,  7,  8,  9, 10, 10, 10, 10,
                 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0])
pzB = np.array([ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0])
pB = np.array([pxB, pyB, pzB])

rX = rotacionX(90)
rY = rotacionY(90)
rZ = rotacionZ(90)

fig = plt.figure("Ejercicio 1")
ax = fig.add_subplot(111, projection='3d')
ax.scatter(*pB, marker='x', label='Puntos originales')
ax.scatter(*(rX @ pB), marker='x', label='Rotación $X_A$')
ax.scatter(*(rY @ pB), marker='x', label='Rotación $Y_A$')
ax.scatter(*(rZ @ pB), marker='x', label='Rotación $Z_A$')
ax.set(xlabel='$X_A$', ylabel='$Y_A$', zlabel='$Z_A$')
ax.legend()
plt.show()