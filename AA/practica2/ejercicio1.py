# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt


# Fijamos la semilla
np.random.seed(1)


def simula_unif(N, dim, rango):
	return np.random.uniform(rango[0],rango[1],(N,dim))

def simula_gaus(N, dim, sigma):
    media = 0    
    out = np.zeros((N,dim),np.float64)        
    for i in range(N):
        # Para cada columna dim se emplea un sigma determinado. Es decir, para 
        # la primera columna se usará una N(0,sqrt(5)) y para la segunda N(0,sqrt(7))
        out[i,:] = np.random.normal(loc=media, scale=np.sqrt(sigma), size=dim)
        
    return out


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


print ('\nEJERCICIO SOBRE LA COMPLEJIDAD DE H Y EL RUIDO\n')
print ('Ejercicio 1\n')

print("Gráfica simula_unif(50, 2, [-50, 50])")

nube = simula_unif(50, 2, [-50, 50])
a, b = simula_recta([-50, 50])
plt.scatter(nube[:, 0], nube[:, 1])
x = np.linspace(-50, 50)
plt.plot(x, a*x+b, 'k')
plt.title("simula_unif(50, 2, [-50, 50])")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

print("Gráfica simula_gaus(50, 2, [5, 7])")

nube = simula_gaus(50, 2, [5, 7])
a, b = simula_recta([-6, 7])
plt.scatter(nube[:, 0], nube[:, 1])
x = np.linspace(-6, 7)
plt.plot(x, a*x+b, 'k')
plt.ylim(-7, 7)
plt.title("simula_gaus(50, 2, [5, 7])")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

#------------------------------Ejercicio 2 -------------------------------------#
print ('Ejercicio 2\n')

print("Gráfica simula_unif(100, 2, [-50, 50]) con etiquetas sign(y-ax-b)")

np.random.seed(123)
nube = simula_unif(100, 2, [-50, 50])
a, b = simula_recta([-50, 50])
etiquetas = [ np.sign(y - a * x - b) for x, y in nube]

# Plot etiquetas sin ruido
fig, ax = plt.subplots()
scatter = ax.scatter(nube[:, 0], nube[:, 1], c=etiquetas)
x = np.linspace(-50, 50)
ax.plot(x, a*x+b, 'k')
ax.set_xlim(-55, 55)
ax.set_ylim(-55, 55)
ax.set_title("simula_unif(100, 2, [-50, 50])")
ax.legend(*scatter.legend_elements(), loc=1)
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

print("Introducimos ruido en las etiquetas")

count = np.unique(etiquetas, return_counts=True)
positivas = 0
negativas = 0

# Ruido
for i in range(len(etiquetas)):
    if etiquetas[i] == 1 and positivas < int(count[1][1]*0.1):
        etiquetas[i] *= -1
        positivas += 1
    elif etiquetas[i] == -1 and negativas < int(count[1][0]*0.1):
        etiquetas[i] *= -1
        negativas += 1

# Plot con nuevas etiquetas
fig, ax = plt.subplots()
scatter = ax.scatter(nube[:, 0], nube[:, 1], c=etiquetas)
x = np.linspace(-50, 50)
ax.plot(x, a*x+b, 'k')
ax.set_xlim(-55, 55)
ax.set_ylim(-55, 55)
ax.set_title("simula_unif(100, 2, [-50, 50])")
ax.legend(*scatter.legend_elements(), loc=1)
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

print("Ejercicio 2.c\n")

xx, yy = np.meshgrid(np.arange(-50, 50), np.arange(-50, 50))
# Fronteras
fronteras = [np.power(xx-10, 2) + np.power(yy-20, 2) - 400,
    0.5*np.power(xx+10, 2) + np.power(yy-20, 2) - 400,
    0.5*np.power(xx-10, 2) - np.power(yy+20, 2) - 400,
    yy - 20*np.power(xx,2) - 5*xx + 3]
funciones = ["f(x,y) = (x - 10)^2 + (y - 20)^2 - 400",
             "f(x,y) = 0.5(x + 10)^2 + (y - 20)^2 - 400",
             "f(x,y) = 0.5(x - 10)^2 - (y + 20)^2 - 400",
             "f(x,y) = y - 20x^2 - 5x + 3"]


for frontera, funcion in zip(fronteras, funciones):
    print("frontera =", funcion)
    fig, ax = plt.subplots()
    contour = ax.contourf(xx, yy, frontera, levels=0, cmap="RdBu_r")
    proxy = [plt.Rectangle((0,0),1,1, fc=c.get_facecolor()[0]) for c in contour.collections]
    scatter = ax.scatter(nube[:, 0], nube[:, 1], c=etiquetas)
    ax.set_xlim(xx.min(), xx.max())
    ax.set_ylim(yy.min(), yy.max())
    ax.legend((*proxy, *scatter.legend_elements()[0]), ("región negativa", "región positiva", *scatter.legend_elements()[1]), loc=1)
    ax.set_title(funcion)
    plt.show()
    input("\n--- Pulsar tecla para continuar ---\n")
