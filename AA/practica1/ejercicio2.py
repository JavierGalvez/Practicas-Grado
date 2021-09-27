# -*- coding: utf-8 -*-

#############################
#####     LIBRERIAS     #####
#############################

import numpy as np
import matplotlib.pyplot as plt

#-------------------------------------------------------------------------------#
#---------------------- Ejercicio sobre regresión lineal -----------------------#
#-------------------------------------------------------------------------------#

#------------------------------Ejercicio 1 -------------------------------------#


# Funcion para leer los datos
def readData(file_x, file_y):
	# Leemos los ficheros	
	datax = np.load(file_x)
	datay = np.load(file_y)
	y = []
	x = []
	
	# Solo guardamos los datos cuya clase sea la 1 o la 5
	for i in range(0,datay.size):
		if datay[i] == 5 or datay[i] == 1:
			if datay[i] == 5:
				y.append(1)
			else:
				y.append(-1)
			x.append(np.array([1, datax[i][0], datax[i][1]]))
			
	x = np.array(x, np.float64)
	y = np.array(y, np.float64)
	
	return x, y
	
# Funcion para calcular el error
def Err(x,y,w):
    err = np.divide(np.power(np.linalg.norm(np.subtract(np.dot(x,w), y)), 2), y.size)
    return err
	
# Gradiente Descendente Estocastico
def sgd(x, y, lr, max_iters, tam_minibatch):
    w = np.zeros(len(x[0]))
    num_minibatch = int(np.floor(len(x)/tam_minibatch))
    idx = 0

    order = np.random.permutation(len(x))
    for i in range(max_iters):
        batch = order[idx*tam_minibatch:idx*tam_minibatch+tam_minibatch]
        w = w - lr * (2 / tam_minibatch * np.dot(np.transpose(x[batch]), np.dot(x[batch], w) - y[batch]))

        idx = (idx + 1) % num_minibatch
        if idx == 0:
            order = np.random.permutation(len(x))

    return w
	
# Algoritmo pseudoinversa	
def pseudoinverse(x, y):
    w = np.dot(np.linalg.pinv(x), y)
    return w

# Lectura de los datos de entrenamiento
x, y = readData('datos/X_train.npy', 'datos/y_train.npy')
# Lectura de los datos para el test
x_test, y_test = readData('datos/X_test.npy', 'datos/y_test.npy')

print ('EJERCICIO SOBRE REGRESION LINEAL\n')
print ('Ejercicio 1\n')

# Gradiente descendente estocastico

tam_minibatch = int(input("Introduce el tamaño del minibatch: "))
lr = float(input("Introduce el learning rate: "))
max_iter = int(input("Introduce el número de iteraciones: "))

w_sgd = sgd(x, y, lr, max_iter, tam_minibatch)

print ('\nBondad del resultado para grad. descendente estocastico:\n')
print ("Ein: ", Err(x,y,w_sgd))
print ("Eout: ", Err(x_test,y_test,w_sgd))

input("\n--- Pulsar tecla para continuar ---\n")

# Algoritmo Pseudoinversa

w_inv = pseudoinverse(x, y)

print ('\nBondad del resultado para el algoritmo de la pseudoinversa:\n')
print ("Ein: ", Err(x,y,w_inv))
print ("Eout: ", Err(x_test,y_test,w_inv))

input("\n--- Pulsar tecla para continuar ---\n")

# Plot sgd vs pseudoinversa
fig, ax = plt.subplots()
scatter = ax.scatter(x[:, 1], x[:, 2], c=y)

a = np.linspace(0, 0.6)
graf_sgd, = ax.plot(a, (-w_sgd[0]-w_sgd[1]*a)/w_sgd[2])
graf_pseudoinversa, = ax.plot(a, (-w_inv[0]-w_inv[1]*a)/w_inv[2])

plt.legend((graf_sgd, graf_pseudoinversa, *scatter.legend_elements()[0]), ('SGD', 'Pseudoinversa', '1', '5'))
plt.xlabel("Intensidad")
plt.ylabel("Simetría")
plt.title("SGD vs Pseudoinversa")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

#------------------------------Ejercicio 2 -------------------------------------#

# Simula datos en un cuadrado [-size,size]x[-size,size]
def simula_unif(N, d, size):
    return np.random.uniform(-size, size, (N, d))

# Función para asignar etiquitas
def asignar_etiquetas(x, ruido):
    y = np.array([np.sign(np.power(i[0]-0.2, 2) + np.power(i[1], 2) - 0.6) for i in x])
    for i in np.random.randint(0, len(x), int(len(x)*ruido)):
        y[i] *= -1
    return y

# EXPERIMENTO	
# a) Muestra de entrenamiento N = 1000, cuadrado [-1,1]x[-1,1]	

print ('Ejercicio 2\n')
print ('Muestra N = 1000, cuadrado [-1,1]x[-1,1]')


n = 1000
ruido = 0.1

x = simula_unif(n, 2, 1)
# Plot nube de puntos
fig, ax = plt.subplots()
scatter = ax.scatter(x[:, 0], x[:, 1])
plt.title("Nube de puntos en el cuadrado [-1, 1]x[-1, 1]")
plt.show()

# Plot nube de puntos con etiquetas
y = asignar_etiquetas(x, ruido)
fig, ax = plt.subplots()
scatter = ax.scatter(x[:, 0], x[:, 1], c=y)
plt.legend(*scatter.legend_elements(), loc='upper right')
plt.title("Nube de puntos en el cuadrado [-1, 1]x[-1, 1]")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

# vector de 1s
aux = np.array(np.full((1, n), 1)).T
# x_aux = [1, x1, x2]
x_aux = np.concatenate((aux, x), axis=1)

w = sgd(x_aux, y, 0.01, 10000, 128)

print ('\nResultado para sgd usando (1, x1, x2) como vector de características:\n')
print ("Ein: ", Err(x_aux, y, w))

# Plot 2d
fig, ax = plt.subplots()
scatter = ax.scatter(x[:, 0], x[:, 1], c=y)

a = np.linspace(-1, 1)
graph, = ax.plot(a, (-w[0]-w[1]*a)/w[2])

legend = scatter.legend_elements()
plt.legend((graph, *legend[0]), ('SGD', *legend[1]), loc='upper right')
plt.xlim(-1.1, 1.1)
plt.ylim(-1.1, 1.1)
plt.show()
"""
# Plot 3d
fig = plt.figure()
ax3d = fig.add_subplot(111, projection='3d')
scatter = ax3d.scatter(x[:,0], x[:,1], np.zeros(len(x)), c=y)
x1, x2 = np.meshgrid(np.arange(-1, 1, 0.02), np.arange(-1, 1, 0.02))
f = w[0]+w[1]*x1+w[2]*x2
plano = ax3d.plot_surface(x1, x2, f, alpha=0.4)

plano._facecolors2d=plano._facecolors3d
legend = scatter.legend_elements()
pl = plt.Rectangle((0,0),1,1, fc=plano.get_facecolor()[0])
ax3d.legend((pl, *legend[0]), ('SGD', *legend[1]))
plt.show()
"""
input("\n--- Pulsar tecla para continuar ---\n")

# -------------------------------------------------------------------
# d) Ejecutar el experimento 1000 veces

print ('Errores Ein y Eout medios tras 1000 reps del experimento (1, x1, x2):\n')
Ein = 0
Eout = 0
for k in range(1000):
    # Train
    x_in = simula_unif(n, 2, 1)
    y_in = asignar_etiquetas(x_in, ruido)
    # x_in = [1, x1, x2]
    x_in = np.concatenate((aux,x_in), axis=1)

    # Test
    x_out = simula_unif(n, 2, 1)
    y_out = asignar_etiquetas(x_out, ruido)
    # x_out = [1, x1, x2]
    x_out = np.concatenate((aux, x_out), axis=1)
    
    # SGD
    w = sgd(x_in, y_in, 0.01, 1000, 128)

    # Errores
    Ein += Err(x_in, y_in, w)
    Eout += Err(x_out, y_out, w)

print ("Ein media: ", Ein / 1000)
print ("Eout media: ", Eout / 1000)

input("\n--- Pulsar tecla para continuar ---\n")

print ('Errores Ein y Eout medios tras 1000 reps del experimento (1, x1, x2, x1*x2, x1^2, x2^2):\n')

Ein = 0
Eout = 0
for k in range(1000):
    # Train
    x_in = simula_unif(n, 2, 1)
    y_in = asignar_etiquetas(x_in, ruido)

    x1x2 = np.array([x_in[:,0]*x_in[:,1]]).T # x1*x2
    x1_cuadrado = np.array([np.power(x_in[:,0], 2)]).T # x1^2
    x2_cuadrado = np.array([np.power(x_in[:,1], 2)]).T # x2^2
    # x_in = [1, x1, x2, x1*x2, x1^2, x2^2]
    x_in = np.concatenate((aux, x_in, x1x2, x1_cuadrado, x2_cuadrado), axis=1)

    # Test
    x_out = simula_unif(n, 2, 1)
    y_out = asignar_etiquetas(x_out, ruido)

    x1x2 = np.array([x_out[:,0]*x_out[:,1]]).T # x1*x2
    x1_cuadrado = np.array([np.power(x_out[:,0], 2)]).T # x1^2
    x2_cuadrado = np.array([np.power(x_out[:,1], 2)]).T # x2^2
    # x_out = [1, x1, x2, x1*x2, x1^2, x2^2]
    x_out = np.concatenate((aux, x_out, x1x2, x1_cuadrado, x2_cuadrado), axis=1)
    
    # SGD
    w = sgd(x_in, y_in, 0.01, 1000, 128)

    # Errores
    Ein += Err(x_in, y_in, w)
    Eout += Err(x_out, y_out, w)

print ("Ein media: ", Ein / 1000)
print ("Eout media: ", Eout / 1000)

x1, x2 = np.meshgrid(np.arange(-1, 1, 0.02), np.arange(-1, 1, 0.02))
f = w[0] + w[1]*x1 + w[2]*x2 + w[3]*x1*x2 + w[4]*np.power(x1,2) + w[5]*np.power(x2,2)

# plot 3d
fig = plt.figure()
ax3d = fig.add_subplot(111, projection='3d')
scatter = ax3d.scatter(x[:,0], x[:,1], np.zeros(len(x)), c=y)
plano = ax3d.plot_surface(x1, x2, f, alpha=0.4)

plano._facecolors2d=plano._facecolors3d
legend = scatter.legend_elements()
pl = plt.Rectangle((0,0),1,1, fc=plano.get_facecolor()[0])
ax3d.legend((pl, *legend[0]), ('SGD', *legend[1]))
plt.show()

# plot 2d
fig, ax2d = plt.subplots()
scatter = ax2d.scatter(x[:, 0], x[:, 1], c=y)
graph = ax2d.contour(x1, x2, f, [0], colors='red')

legend = scatter.legend_elements()
ax2d.legend((graph.legend_elements()[0][0], *legend[0]), ('SGD', *legend[1]), loc='upper right')
ax2d.set_xlim(-1.1, 1.1)
ax2d.set_ylim(-1.1, 1.1)
plt.show()
