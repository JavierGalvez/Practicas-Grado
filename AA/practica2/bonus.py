# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

# Funcion para leer los datos
def readData(file_x, file_y):
	# Leemos los ficheros	
	datax = np.load(file_x)
	datay = np.load(file_y)
	y = []
	x = []
	
	# Solo guardamos los datos cuya clase sea la 1 o la 5
	for i in range(0,datay.size):
		if datay[i] == 4 or datay[i] == 8:
			if datay[i] == 4:
				y.append(1)
			else:
				y.append(-1)
			x.append(np.array([1, datax[i][0], datax[i][1]]))
			
	x = np.array(x, np.float64)
	y = np.array(y, np.float64)
	
	return x, y

# Lectura de los datos de entrenamiento
x, y = readData('datos/X_train.npy', 'datos/y_train.npy')
# Lectura de los datos para el test
x_test, y_test = readData('datos/X_test.npy', 'datos/y_test.npy')

# Algoritmo pseudoinversa	
def pseudoinverse(x, y):
    w = np.dot(np.linalg.pinv(x), y)
    return w

# Cálculo del error
def Err(X, Y, w):
    err = 0
    for x, y in zip(X, Y):
        if np.sign(np.dot(w.T,x)) != y:
            err += 1
    return err / len(X)

# POCKET-PLA
def PLA_pocket(datos, label, max_iter, vini):
    w = vini
    pocket = np.copy(w)
    change = True
    iters = max_iter
    for i in range(max_iter):
        change = False
        order = np.random.permutation(len(datos))
        for j in order:
            if np.sign(np.dot(w.T, x[j])) != y[j]:
                w += y[j]*x[j]
                change = True

        if Err(datos, label, w) < Err(datos, label, pocket):
            pocket = np.copy(w)

        if change == False:
            iters = i
            break
    return pocket

print ('\nBONUS: Clasificación de Dígitos\n')

w = PLA_pocket(x, y, 200, pseudoinverse(x, y))

print("Gráfica Pocket-PLA con los datos de entrenamiento")

# Plot Pocket-PLA train
fig, ax = plt.subplots()
scatter = ax.scatter(x[:, 1], x[:, 2], c=y)
a = np.linspace(0, 0.6)
graph_pocket, = ax.plot(a, (-w[0]-w[1]*a)/w[2])
ax.legend((graph_pocket, *scatter.legend_elements()[0]), ('Pocket-PLA', '8', '4'), loc=1)
ax.set_title("Pocket-PLA train")
ax.set_ylim(-7.5, 0)
ax.set_xlabel("Intensidad")
ax.set_ylabel("Simetría")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

print("Gráfica Pocket-PLA con los datos de test")

# Plot Pocket-PLA test
fig, ax = plt.subplots()
scatter = ax.scatter(x_test[:, 1], x_test[:, 2], c=y_test)
a = np.linspace(0, 0.6)
graph_pocket, = ax.plot(a, (-w[0]-w[1]*a)/w[2])
ax.legend((graph_pocket, *scatter.legend_elements()[0]), ('Pocket-PLA', '8', '4'), loc=1)
ax.set_title("Pocket-PLA test")
ax.set_ylim(-7.5, 0)
ax.set_xlabel("Intensidad")
ax.set_ylabel("Simetría")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

print("Ein:", Err(x, y, w))
print("Etest:", Err(x_test, y_test, w))

# Función para calcular la cota de Eout
def cota(X, Y, w, Err, delta):
    return Err(X, Y, w) + np.sqrt(1/(2*len(X)) * np.log(2/delta))

input("\n--- Pulsar tecla para continuar ---\n")

print("Cota basada en Ein:")
print("Eout <=", cota(x, y, w, Err, 0.05))
print("\nCota basada en Etest:")
print("Eout <=", cota(x_test, y_test, w, Err, 0.05))
