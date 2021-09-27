# -*- coding: utf-8 -*-

#############################
#####     LIBRERIAS     #####
#############################

import numpy as np
import matplotlib.pyplot as plt


#-------------------------------------------------------------------------------#
#------------- Ejercicio sobre la búsqueda iterativa de óptimos ----------------#
#-------------------------------------------------------------------------------#


#------------------------------Ejercicio 1 -------------------------------------#

# Fijamos la semilla

def E(w): 
    return np.power(w[0]*np.exp(w[1])-2*w[1]*np.exp(-w[0]), 2)
			 
# Derivada parcial de E respecto de u
def Eu(w):
    return 2*np.exp(-2*w[0])*(w[0]*np.exp(w[0]+w[1])-2*w[1])*(np.exp(w[0]+w[1])+2*w[1])

# Derivada parcial de E respecto de v
def Ev(w):
    return 2*np.exp(-2*w[0])*(w[0]*np.exp(w[0]+w[1])-2)*(w[0]*np.exp(w[0]+w[1])-2*w[1])
	
# Gradiente de E
def gradE(w):
    return np.array([Eu(w), Ev(w)])

# Gradiente descendiente
def gd(w, lr, grad_fun, fun, epsilon, max_iters=100000):
    for it in range(1, max_iters+1):
        w = w - lr * grad_fun(w)
        print('Valor de f en la iteracion', it, ': ', fun(w))
        if fun(w) < epsilon:
            break
    return w, it

print ('\nGRADIENTE DESCENDENTE')
print ('\nEjercicio 1\n')

num_ite = int(input('Introduce el numero de iteraciones: '))
print ('Numero de iteraciones: ', num_ite)
input("\n--- Pulsar tecla para continuar ---\n")

w, iters = gd(np.array([1.0, 1.0]), 0.1, gradE, E, np.float_power(10, -14), num_ite)
print('\nIteraciones hasta obtener un valor de E(u,v) menor que 10^(-14):', iters)
print('Coordenadas obtenidas: (', w[0], ', ', w[1],')')

input("\n--- Pulsar tecla para continuar ---\n")

#------------------------------Ejercicio 2 -------------------------------------#

def f(w):   
    return np.power(w[0]-2,2)+2*np.power(w[1]+2,2)+2*np.sin(2*np.pi*w[0])*np.sin(2*np.pi*w[1])
	
# Derivada parcial de f respecto de x
def fx(w):
    return 2*(2*np.pi*np.cos(2*np.pi*w[0])*np.sin(2*np.pi*w[1])+w[0]-2) 

# Derivada parcial de f respecto de y
def fy(w):
    return 4*(np.pi*np.sin(2*np.pi*w[0])*np.cos(2*np.pi*w[1])+w[1]+2)
	
# Gradiente de f
def gradf(w):
    return np.array([fx(w), fy(w)])
	
# a) Usar gradiente descendente para minimizar la función f, con punto inicial (1,-1)
# tasa de aprendizaje 0.01 y max 50 iteraciones. Repetir con tasa de aprend. 0.1
def gd_grafica(w, lr, grad_fun, fun, max_iters=50):
    graf = []
    for i in range(max_iters):
        w = w - lr *gradf(w)
        graf.append(fun(w))
    return graf


print ('Resultados ejercicio 2\n')
punto_inicial = np.array([1, -1])
max_iters=50
lr1 = gd_grafica(punto_inicial, 0.01, gradf, f, max_iters)
lr2 = gd_grafica(punto_inicial, 0.1, gradf, f, max_iters)
plt.plot(range(0,max_iters), lr1, marker='o', label='lr = 0.01')
plt.plot(range(0,max_iters), lr2, marker='o', label='lr = 0.1')
plt.title('Comparativa learning rates')
plt.xlabel('Iteraciones')
plt.ylabel('f(w)')
plt.legend()
plt.show()	

input("\n--- Pulsar tecla para continuar ---\n")


# b) Obtener el valor minimo y los valores de (x,y) con los
# puntos de inicio siguientes:

def gd(w, lr, grad_fun, fun, max_iters=10000):
    for i in range(max_iters):
        w = w - lr * grad_fun(w)
    return w

lr = 0.01
puntos = [np.array([2.1, -2.1]),np.array([3.0, -3.0]),np.array([1.5, 1.5]),np.array([1.0, -1.0])]
for w in puntos:
    print ('Punto de inicio: (' + str(w[0]) + ', ' + str(w[1]) + ')\n')
    w1 = gd(w, lr, gradf, f)
    print ('(x,y) = (', w1[0], ', ', w1[1],')\n')
    print ('Valor minimo: ',f(w1))
    input("\n--- Pulsar tecla para continuar ---\n")
