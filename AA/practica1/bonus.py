import numpy as np
import matplotlib.pyplot as plt

#------------------------------Ejercicio BONUS -------------------------------------#

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

# Hessiana de f
def hessianf(w):
    return np.array([[2-8*np.power(np.pi,2)*np.sin(2*np.pi*w[0])*np.sin(2*np.pi*w[1]),
                    8*np.power(np.pi,2)*np.cos(2*np.pi*w[0])*np.cos(2*np.pi*w[1])],
                    [8*np.power(np.pi,2)*np.cos(2*np.pi*w[0])*np.cos(2*np.pi*w[1]),
                    4-8*np.power(np.pi,2)*np.sin(2*np.pi*w[0])*np.sin(2*np.pi*w[1])]])

# Gradiente descendente
def gd(w, lr, grad_fun, fun, max_iters=50):
    graf = []
    for i in range(max_iters):
        w = w - lr * gradf(w)
        graf.append(fun(w))
    return w, graf

# Método de Newton
def newton(w, grad_fun, hessian_fun, fun, max_iters=50):
    graf = []
    for i in range(max_iters):
        w = w - np.dot(np.linalg.inv(hessian_fun(w)), grad_fun(w))
        graf.append(fun(w))

    return w, graf

lr = 0.01
max_iters = 50
puntos = [np.array([2.1, -2.1]),np.array([3.0, -3.0]),np.array([1.5, 1.5]),np.array([1.0, -1.0])]

fig = plt.figure()
for i, w in enumerate(puntos, start=1):
    print ('Punto de inicio: (' + str(w[0]) + ', ' + str(w[1]) + ')\n')
    w1, newton_graf = newton(w, gradf, hessianf, f)
    _ , gd_graf     = gd(w, lr, gradf, f)
    print ('(x,y) = (', w1[0], ', ', w1[1],')\n')
    print ('Valor minimo: ',f(w1))

    ax = fig.add_subplot(2, 2, i)
    ax.plot(range(0,max_iters), newton_graf, marker='o', label='Newton')
    ax.plot(range(0,max_iters), gd_graf, marker='o', label='GD')
    ax.set_title('Punto de inicio: (' + str(w[0]) +  ', ' + str(w[1]) + ')')
    ax.set_xlabel('Iteraciones')
    ax.set_ylabel('f(x,y)')
    ax.legend()
    
    input("\n--- Pulsar tecla para continuar ---\n")

plt.show()
