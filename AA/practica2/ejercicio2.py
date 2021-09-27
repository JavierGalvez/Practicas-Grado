# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt


# Fijamos la semilla
np.random.seed(1)


def simula_unif(N, dim, rango):
	return np.random.uniform(rango[0],rango[1],(N,dim))

def simula_recta(intervalo):
    points = np.random.uniform(intervalo[0], intervalo[1], size=(2, 2))
    x1 = points[0,0]
    x2 = points[1,0]
    y1 = points[0,1]
    y2 = points[1,1]
    # y = a*x + b
    a = (y2-y1)/(x2-x1) # Calculo de la pendiente.
    b = y1 - a*x1       # Calculo del termino independiente.
    
    return a, b

def ajusta_PLA(datos, label, max_iter, vini):
    w = vini
    change = True
    iters = max_iter
    for i in range(max_iter):
        order = np.random.permutation(len(datos))
        change = False
        for j in order:
            if np.sign(np.dot(w.T, datos[j])) != label[j]:
                w += label[j]*datos[j]
                change = True
        if change == False:
            iters = i
            break
    return w, iters
    


# Datos del apartado 1.2.a

np.random.seed(123)
nube = simula_unif(100, 2, [-50, 50])
a, b = simula_recta([-50, 50])
etiquetas = [ np.sign(y - a * x - b) for x, y in nube]
x = np.concatenate((np.array(np.full((1, len(nube)), 1)).T, nube), axis=1)

#------------------------------Ejercicio 1 -------------------------------------#
# Apartado 1
print ('\nMODELOS LINEALES')
print("\nEjercicio 1: Algoritmo Perceptron\n")
max_iters = int(input("Introduce el máximo de iteraciones para PLA: "))

# vini vector de ceros
w, iters = ajusta_PLA(x, etiquetas, max_iters, np.zeros(len(x[0])))

# Plot PLA
print("\nIteraciones de PLA hasta converger:", iters)
print("Gráfica PLA con vini vector de ceros")
fig, ax = plt.subplots()
scatter = ax.scatter(nube[:, 0], nube[:, 1], c=etiquetas)
aux = np.linspace(-50, 50)
graph_pla, = ax.plot(aux, (-w[0]-w[1]*aux)/w[2])
ax.legend((graph_pla, *scatter.legend_elements()[0]), ('PLA', *scatter.legend_elements()[1]), loc=1)
ax.set_xlim(-55, 55)
ax.set_ylim(-55, 55)
ax.set_title("Algoritmo Perceptron para datos sin ruido")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

print("Ejecutamos PLA 10 veces con vini vector de números aleatorios entre [0, 1]")

# vini vector de números aleatorios entre [0, 1]
media_iters = 0
for i in range(10):
    media_iters += ajusta_PLA(x, etiquetas, max_iters, np.random.rand(len(x[0])))[1]

print("Media de iteraciones para converger:", media_iters/10)

input("\n--- Pulsar tecla para continuar ---\n")

# Apartado 2

count = np.unique(etiquetas, return_counts=True)
positivas = 0
negativas = 0

# Ruido
print("Introducimos ruido en las etiquetas")
for i in range(len(etiquetas)):
    if etiquetas[i] == 1 and positivas < int(count[1][1]*0.1):
        etiquetas[i] *= -1
        positivas += 1
    elif etiquetas[i] == -1 and negativas < int(count[1][0]*0.1):
        etiquetas[i] *= -1
        negativas += 1

# vini vector de ceros
w, iters = ajusta_PLA(x, etiquetas, max_iters, np.zeros(len(x[0])))

print("\nIteraciones de PLA hasta converger:", iters)
print("Gráfica PLA con vini vector de ceros")

# Plot PLA con ruido
fig, ax = plt.subplots()
scatter = ax.scatter(nube[:, 0], nube[:, 1], c=etiquetas)
aux = np.linspace(-50, 50)
graph_pla, = ax.plot(aux, (-w[0]-w[1]*aux)/w[2])
ax.legend((graph_pla, *scatter.legend_elements()[0]), ('PLA', *scatter.legend_elements()[1]), loc=1)
ax.set_xlim(-55, 55)
ax.set_ylim(-55, 55)
ax.set_title("Algoritmo Perceptron para datos con ruido")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

print("Ejecutamos PLA 10 veces con vini vector de números aleatorios entre [0, 1]")

# vini vector de números aleatorios entre [0, 1]
media_iters = 0
for i in range(10):
    media_iters += ajusta_PLA(x, etiquetas, max_iters, np.random.rand(len(x[0])))[1]

print("Media de iteraciones para converger:", media_iters/10)

input("\n--- Pulsar tecla para continuar ---\n")
#------------------------------Ejercicio 2 -------------------------------------#

# Regrensión logística gradiente descendente estocastico
def rl_sgd(x, y, vini, lr):
    w = vini
    w_anterior = vini + 999

    while(np.linalg.norm(np.subtract(w_anterior,w)) >= 0.01):
        order = np.random.permutation(len(x))
        w_anterior = np.copy(w)
        for i in order:
            grad = - np.divide(y[i]*x[i], 1 + np.exp(y[i]*np.dot(w.T, x[i])))
            w -= lr * grad
    return w

print("Ejercicio 2: Regresión Logística\n")

nube = simula_unif(100, 2, [0, 2])
a, b = simula_recta([0, 2])

etiquetas = [ np.sign(y - a * x - b) for x, y in nube]

print("Gráfica resultado de la regresión logística")

x = np.concatenate((np.array(np.full((1, len(nube)), 1)).T, nube), axis=1)

w = rl_sgd(x, etiquetas, np.zeros(len(x[0])), 0.01)

# Plot RL SGD
fig, ax = plt.subplots()
scatter = ax.scatter(nube[:, 0], nube[:, 1], c=etiquetas)
aux = np.linspace(0, 2)
graph_rl, = ax.plot(aux, (-w[0]-w[1]*aux)/w[2])
graph, = ax.plot(aux, a*aux+b)
ax.legend((graph_rl, graph, *scatter.legend_elements()[0]), ('RL', 'f(x)', *scatter.legend_elements()[1]), loc=1)
ax.set_xlim(0, 2)
ax.set_ylim(0, 2)
ax.set_title("Regresión logística con SGD")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

# Función para calcular el error de la RL
def RLErr(x, y, w):
    return np.mean(np.log(1 + np.exp(-y*np.dot(w, x.T))))

print("Estimación de Eout\n")

N = int(input("Introduce el tamaño de la muestra (>999): "))

# Nueva muestra
nube = simula_unif(N, 2, [0, 2])
etiquetas_out = [ np.sign(y - a * x - b) for x, y in nube]
nube = np.concatenate((np.array(np.full((1, len(nube)), 1)).T, nube), axis=1)


print("\nEin:", RLErr(x, np.array(etiquetas), w))
print("Eout:", RLErr(nube, np.array(etiquetas_out), w))
