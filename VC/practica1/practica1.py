# -*- coding: utf-8 -*-
"""
@author: Javier Gálvez Obispo
"""

import cv2
import numpy as np
from matplotlib import pyplot as plt

path = "imagenes/"

# Función para mostrar por pantalla cualquier imagen
def pintaImagen(im, titulo):
    # Trasladamos y escalamos la imagen al rango [0, 1]
    if np.min(im) < 0:
        im + abs(np.min(im))
    img_normalizada = cv2.normalize(im, None, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_32F)
    cv2.imshow(titulo, img_normalizada)
    cv2.waitKey(0)
    cv2.destroyWindow(titulo)

# Función para el cálculo de la Gaussiana 1D
def gaussiana1D(x, sigma):
    return np.exp(- np.power(x, 2) / (2 * np.power(sigma, 2)))

# Función para el cálculo de la primera derivada de la Gaussiana 1D
def deriv1_gaussiana1D(x, sigma):
    return - x / np.power(sigma, 2) * np.exp(- np.power(x, 2) / (2 * np.power(sigma, 2)))

# Función para el cálculo de la segunda derivada de la Gaussiana 1D
def deriv2_gaussiana1D(x, sigma):
    return (- 1.0 / np.power(sigma, 2) + np.power(x, 2) / np.power(sigma, 4)) * \
            np.exp(- np.power(x, 2) / (2 * np.power(sigma, 2)))
       
# Función para generar máscaras
def generar_mascara(val, deriv=0, usar_sigma=True):
    mascara = []
    
    # Asignamos la función según el parámetro
    if deriv == 0:
        func = gaussiana1D
    elif deriv == 1:
        func = deriv1_gaussiana1D
    elif deriv == 2:
        func = deriv2_gaussiana1D
    else:
        print("El valor de la derivada debe ser 0, 1 ó 2")
    
    # Si se pasa un sigma
    sigma = val
    if usar_sigma:
        mascara = func(np.arange(int(-sigma*3), (int(sigma*3)+1)), val)
        
    # Si se pasa el tamaño de la máscara que se quiere
    else:
        if val > 0 and val % 2 == 1:
            sigma = (val - 1) / 6
            mascara = func(np.arange(int(-sigma*3), (int(sigma*3)+1)), sigma)
        else:
            print("El tamaño debe ser un número positivo impar")
    
    # Discretizamos la máscara
    if deriv == 0:
        mascara = mascara / sum(mascara)
    else:
        mascara = mascara * np.power(sigma, deriv)
        
    return np.array(mascara)

# Función para añadir bordes negros/replicados a una imagen dada
def generar_bordes(img, k, replicar=False):
    # Matriz de ceros
    imagen_bordes = np.zeros((img.shape[0]+2*k, img.shape[1]+2*k))
    
    # En caso de que la imagen sea a color añadimos 3 canales
    if len(img.shape) == 3:
        imagen_bordes = np.repeat(imagen_bordes, 3, axis=1).reshape(*imagen_bordes.shape, 3)
     
    # Centramos la imagen original en la matriz de ceros
    imagen_bordes[k:img.shape[0]+k, k:img.shape[1]+k] = img

    # Cambiamos el borde de ceros si se pide replicar
    if replicar:
        # Filas
        for i in range(k, img.shape[0]+k):
            # Principio de la fila
            imagen_bordes[i, 0:k] = imagen_bordes[i][k]
            # Final de la fila
            imagen_bordes[i, img.shape[1]+k:] = imagen_bordes[i][img.shape[1]+k-1]
        # Columnas
        for i in range(k, img.shape[1]+k):
            # Principio de la columna
            imagen_bordes[0:k, i] = imagen_bordes[k][i]
            # Final de la columna
            imagen_bordes[img.shape[0]+k:, i] = imagen_bordes[img.shape[0]+k-1][i]
            
    return imagen_bordes
    
# Función para realizar la convolución de una imagen por filas dada una máscara
def convolucion_filas(img, mascara):
    # Creamos una matriz con el mismo número de filas que la imagen original en la que
    # cada fila es igual que la máscara
    matriz_convolucion = np.tile(mascara, (img.shape[0], 1))
    
    # Si la imagen está a color añadimos 3 canales
    if len(img.shape) == 3:
        matriz_convolucion = np.repeat(matriz_convolucion, 3, axis=1).reshape(*matriz_convolucion.shape, 3)

    # Cálculamos la primera columna de la nueva imagen para poder ir concatenando las columnas
    nueva_img = np.sum(np.multiply(img[:, 0:mascara.size] , matriz_convolucion), axis=1, keepdims=True)
    
    # Cálculamos el resto de columnas y concatenamos
    for i in range(1, img.shape[1] - mascara.size + 1):
        columna = np.sum(np.multiply(img[:, i:i+mascara.size] , matriz_convolucion), axis=1, keepdims=True)
        nueva_img = np.column_stack((nueva_img, columna))
        
    return nueva_img

# Función para transponer cualquier imagen independientemente del número de canales
def transponer_imagen(img):
    if len(img.shape) == 3:
        return np.transpose(img, axes=(1, 0, 2))
    else:
        return img.T

# Función para realizar la convolución 2D de una imagen dada una máscara
def convolucion2D(img, mascara):
    # Convolución por filas
    nueva_img = convolucion_filas(img, mascara)
    
    # Convolución por columnas
    img_convolucionada = convolucion_filas(transponer_imagen(nueva_img), mascara)
    
    return transponer_imagen(img_convolucionada)

# Función para calcular la laplaciana
def calc_laplaciana(img, sigma):
    # Generar máscaras
    # Máscara de la segunda derivada de la gaussiana para las filas
    mascara_deriv2 = generar_mascara(sigma, deriv=2)
    # Máscara de la Gaussiana para las columnas
    mascara_gauss = generar_mascara(sigma)
    
    derivX = convolucion_filas(convolucion_filas(img, mascara_deriv2).T, mascara_gauss)
    derivY = convolucion_filas(convolucion_filas(img.T, mascara_deriv2).T, mascara_gauss)
    
    return (derivX.T + derivY)

# Función para calcular los niveles indicados de la pirámide Gaussiana de una imagen dada
def calc_piramide_gaussiana(img, sigma, nivel):
    # Cálculo de la máscara Gaussiana
    mascara_gauss1D = generar_mascara(sigma)
    
    piramide = []
    # Guardamos la imagen original para la representación posterior
    piramide.append(img)
    for i in range(nivel):
        # Añadimos bordes al nivel anterior y lo alisamos
        img_bordes = generar_bordes(piramide[i], 3*sigma, replicar=True)
        nueva_img = convolucion2D(img_bordes, mascara_gauss1D)
        
        # Nos quedamos con la mitad de las filas y de las columnas
        # y guardamos el nuevo nivel recién calculado
        nueva_img = nueva_img[::2, ::2]
        piramide.append(nueva_img)
        
    return np.array(piramide)
        
# Función para pintar una pirámide Gaussiana dado un array con los distintos niveles
def pintar_piramide(piramide, titulo):
    # Vemos cuál es el valor máximo para añadir rellenos blancos
    blanco = np.max(piramide[0])
    
    # Empezamos por el nivel más bajo
    resultado = piramide[-1]
    
    # Hacemos las mismas operaciones en el if else pero cambiando el número de canales
    # Igualamos el número de columnas del nivel más bajo al anterior metiendo pixeles blancos
    # y juntamos las imágenes de forma vertical
    #
    # Después de juntar todos los niveles de la pirámide de forma vertical
    # juntamos la imagen resultado con la imagen original de forma horizontal
    
    # Para imágenes con color
    if len(piramide[0].shape) == 3:
        for img in piramide[-2:0:-1]:
            relleno = np.full((resultado.shape[0], img.shape[1] - resultado.shape[1], 3), blanco)
            resultado = np.hstack((resultado, relleno))
            resultado = np.vstack((img, resultado))
            
        relleno = np.full((piramide[0].shape[0] - resultado.shape[0], resultado.shape[1], 3), blanco)
        resultado = np.vstack((resultado, relleno))
        
    # Para imágenes en grises
    else:
        for img in piramide[-2:0:-1]:
            relleno = np.full((resultado.shape[0], img.shape[1] - resultado.shape[1]), blanco)
            resultado = np.hstack((resultado, relleno))
            resultado = np.vstack((img, resultado))
            
        relleno = np.full((piramide[0].shape[0] - resultado.shape[0], resultado.shape[1]), blanco)
        resultado = np.vstack((resultado, relleno))
    
    
    pintaImagen(np.hstack((piramide[0], resultado)), titulo)

# Función para calcular los niveles indicados de la pirámide Laplaciana de una imagen dada
def calc_piramide_laplaciana(img, sigma, nivel):    
    # Cálculamos la pirámide Gaussiana de la imagen
    piramide_gauss = calc_piramide_gaussiana(img, sigma, nivel)
    piramide_laplaciana = []
    
    # Aplicamos el algoritmo
    for i in range(nivel):
        imagen_escalada = cv2.resize(piramide_gauss[i+1], piramide_gauss[i].shape[::-1], interpolation=cv2.INTER_LINEAR)     
        piramide_laplaciana.append(piramide_gauss[i] - imagen_escalada)
        
    # Guardamos el último nivel de la piramide Gaussiana para poder reconstruir la imagen original
    piramide_laplaciana.append(piramide_gauss[-1])
    
    return np.array(piramide_laplaciana)
    
# Función para reconstruir una imagen dada su pirámide Laplaciana
def reconstruir_imagen(piramide_laplaciana):
    img_reconstruida = piramide_laplaciana[-1]
    
    # Recorremos la pirámide desde el final al principio aplicando el algoritmo
    for i, img in zip(range(piramide_laplaciana.size-2, -1, -1), piramide_laplaciana[-2::-1]):
        imagen_escalada = cv2.resize(img_reconstruida, piramide_laplaciana[i].shape[::-1], interpolation=cv2.INTER_LINEAR)
        img_reconstruida = imagen_escalada + piramide_laplaciana[i]
    
    return img_reconstruida

# Función para calcular la imagen híbrida de 2 imágenes
def calc_imagen_hibrida(img_baja, sigma_baja, img_alta, sigma_alta):
    # Generamos las máscaras
    mascara_baja = generar_mascara(sigma_baja)
    
    mascara_alta = generar_mascara(sigma_alta)
    
    # Añadimos bordes replicados a las imágenes
    img_baja_borde = generar_bordes(img_baja, 3*sigma_baja, replicar=True)
    img_alta_borde = generar_bordes(img_alta, 3*sigma_alta, replicar=True)
    
    # Obtenemos las frecuencias bajas y altas de las imágenes correspondientes
    img_frecuencias_bajas = convolucion2D(img_baja_borde, mascara_baja)
    img_frecuencias_altas = img_alta - convolucion2D(img_alta_borde, mascara_alta)
    
    return img_frecuencias_bajas + img_frecuencias_altas

# Función para visualizar máscaras
def visualizar_mascara(mascara, titulo):
    eje_x = np.arange(-int((mascara.size-1)/2), int((mascara.size-1)/2)+1)
    plt.plot(eje_x, mascara)
    plt.title(titulo)
    plt.xticks(range(eje_x[0], eje_x[-1]+1))
    plt.show()

# Función para mostrar por pantalla la hibridación de una pareja    
def visualizar_hibridacion(imagen_hibrida, sigma_baja, sigma_alta):
    print("Realizamos la hibridación con:")
    print("Sigma frecuencias bajas =", sigma_baja)
    print("Sigma frecuencias altas =", sigma_alta)
    input("## Pulse tecla para continuar ##\n")
    pintaImagen(imagen_hibrida, "Hibridacion de la pareja")
    
    print("Construimos la pirámide Gaussiana para la imagen híbrida")
    input("## Pulse tecla para continuar ##\n") 
    pintar_piramide(calc_piramide_gaussiana(imagen_hibrida, 1, 4), "Piramide Gaussiana de la imagen hibrida")
    
#%%
print("\n\n------------ Ejercicio 1 ------------\n\n")

print("--- Apartado A ---\n")

sigma = 1

print("Mostramos por pantalla las máscaras de las distintas funciones todas con sigma = 1\n")

# Máscara Gaussiana
print("Máscara de la Gaussiana 1D")
mascara_gauss = generar_mascara(sigma, deriv=0)
visualizar_mascara(mascara_gauss, "Máscara Gaussiana 1D con sigma = 1")
input("## Pulse tecla para continuar ##\n")

# Máscara primera derivada Gaussiana
print("Máscara de la primera derivada de la Gaussiana 1D")
mascara_deriv1 = generar_mascara(sigma, deriv=1)
visualizar_mascara(mascara_deriv1, "Máscara primera derivada Gaussiana 1D con sigma = 1")
input("## Pulse tecla para continuar ##\n")

# Máscara segunda derivada Gaussiana
print("Máscara de la segunda derivada de la Gaussiana 1D")
mascara_deriv2 = generar_mascara(sigma, deriv=2)
visualizar_mascara(mascara_deriv2, "Máscara segunda derivada Gaussiana 1D con sigma = 1")
input("## Pulse tecla para continuar ##\n")

#%%
print("\n--- Apartado B ---\n")


# Leemos una imagen cualquiera de las dadas
imagen = cv2.imread(path + "dog.bmp", 0)
print("Leemos una imagen cualquiera y la mostramos por pantalla")
input("## Pulse tecla para continuar ##\n")
pintaImagen(imagen, "Imagen original")

# Convolución
print("Realizamos la convolución con una máscara Gaussiana con sigma =", sigma)
# Hay que añadir bordes a la imagen antes de llamar a la función
imagen_convolucionada = convolucion2D(generar_bordes(imagen, int(sigma*3), replicar=True), mascara_gauss)
input("## Pulse tecla para continuar ##\n")
pintaImagen(imagen_convolucionada, "Imagen convolucionada")

# Original vs convolución
print("Mostramos por pantalla la dos imágenes para poder compararlas")
print("Izquierda = imagen original \nDerecha   = imagen convolucionada")
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen, imagen_convolucionada)), "Comparativa Original vs Convolucionada")

# Nuestra función vs GaussianBlur
print("Comparamos los resultados de nuestra función de convolución con GaussianBlur")
print("Izquierda = nuestra función \nDerecha   = GaussianBlur")
imagen_gaussianblur = cv2.GaussianBlur(imagen, (mascara_gauss.size, mascara_gauss.size), sigma)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_convolucionada, imagen_gaussianblur)), "nuestra funcion vs GaussianBlur")

# Comparamos valores númericos ya que a simple vista no hay diferencia
print("Comparamos los valores obtenidos en varios pixeles cualesquiera")
print("Nuestra función:\n", imagen_convolucionada[160:164, 230:234])
print("GaussianBlur:\n", imagen_gaussianblur[160:164, 230:234])
input("## Pulse tecla para continuar ##\n")

#%%
print("\n--- Apartado C ---\n")

kernel_deriv1, kernel_deriv2 = cv2.getDerivKernels(1, 2, 7)

print("Máscara de la primera derivada de la Gaussiana 1D obtenida con getDerivKernel")
visualizar_mascara(kernel_deriv1, "Máscara primera derivada Gaussiana 1D getDerivKernel")
input("## Pulse tecla para continuar ##\n")

print("Máscara de la segunda derivada de la Gaussiana 1D obtenida con getDerivKernel")
visualizar_mascara(kernel_deriv2, "Máscara segunda derivada Gaussiana 1D getDerivKernel")
input("## Pulse tecla para continuar ##\n")

#%%
print("\n--- Apartado D ---\n")

print("Las máscaras utilizadas son la máscara Gaussiana y la máscara de la segunda derivada")

print("\nComparamos los resultados de calcular la Laplaciana con distintos bordes")
print("Izquierda = bordes negros \nDerecha   = bordes replicados")

# Laplaciana con sigma = 1 bordes negros y replicados
sigma = 1
print("\nPara sigma = 1\n")
print("Las máscaras ya han sido visualizadas en el apartado A")
print("\nMostramos por pantalla la comparación de los bordes")
imagen_ceros = calc_laplaciana(generar_bordes(imagen, 3*sigma, replicar=False), sigma)
imagen_replica = calc_laplaciana(generar_bordes(imagen, 3*sigma, replicar=True), sigma)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_ceros, imagen_replica)), "Comparacion Laplaciana sigma = 1")


# Laplaciana con sigma = 3 bordes negros y replicados
sigma = 3
print("Para sigma = 3")

# Máscara Gaussiana con sigma = 3
print("\nMáscara de la Gaussiana 1D")
mascara_gauss = generar_mascara(sigma)
visualizar_mascara(mascara_gauss, "Máscara Gaussiana 1D con sigma = 3")
input("## Pulse tecla para continuar ##\n")

# Máscara segunda derivada Gaussiana sigma = 3
print("Máscara de la segunda derivada de la Gaussiana 1D")
mascara_deriv2 = generar_mascara(sigma, deriv=2)
visualizar_mascara(mascara_deriv2, "Máscara segunda derivada Gaussiana 1D con sigma = 3")
input("## Pulse tecla para continuar ##\n")

print("Mostramos por pantalla la comparación de los bordes")
imagen_ceros = calc_laplaciana(generar_bordes(imagen, 3*sigma, replicar=False), sigma)
imagen_replica = calc_laplaciana(generar_bordes(imagen, 3*sigma, replicar=True), sigma)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_ceros, imagen_replica)), "Comparacion Laplaciana sigma = 3")
input("## Pulse tecla para continuar ##\n")


#%%
print("\n\n------------ Ejercicio 2 ------------\n\n")

print("--- Apartado A ---\n")

sigma = 1
nivel = 4

print("Generamos la pirámide Gaussiana de nivel 4 para la imagen anterior con bordes replicados")
piramide_gaussiana = calc_piramide_gaussiana(imagen, sigma, nivel)
input("## Pulse tecla para continuar ##\n")
pintar_piramide(piramide_gaussiana, "Piramide Gaussiana de nivel 4")

#%%
print("--- Apartado B ---\n")

print("Generamos la pirámide Laplaciana de nivel 4 para la imagen anterior con bordes replicados")
piramide_laplaciana = calc_piramide_laplaciana(imagen, sigma, nivel)
input("## Pulse tecla para continuar ##\n")
pintar_piramide(piramide_laplaciana, "Piramide Laplaciana de nivel 4")


print("Reconstruimos la imagen original mendiante la pirámide Laplaciana recién calculada y las comparamos")
print("Izquierda = Imagen original\nDerecha   = Imagen reconstruida")
imagen_reconstruida = reconstruir_imagen(piramide_laplaciana)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen, imagen_reconstruida)), "Imagen original vs imagen reconstruida")
input("## Pulse tecla para continuar ##\n")


#%%
print("\n\n------------ Ejercicio 3 ------------\n\n")

print("A la hora de mostrar las distintas parejas las imagenes están posicionadas de la forma:")
print("Izquierda = Imagen para las frecuencias bajas\nDerecha   = Imagen para las frecuencias altas")
input("## Pulse tecla para continuar ##\n")

# Primera pareja
# Perro + Gato
print("--- Primera pareja ---\n")
print("Mostramos la primera pareja de imágenes que vamos a hibridar")
imagen_perro = cv2.imread(path + "dog.bmp", 0)
imagen_gato = cv2.imread(path + "cat.bmp", 0)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_perro, imagen_gato)), "Primera pareja de imagenes")

sigma_baja = 5
sigma_alta = 5
imagen_hibrida = calc_imagen_hibrida(imagen_perro, sigma_baja, imagen_gato, sigma_alta)
visualizar_hibridacion(imagen_hibrida, sigma_baja, sigma_alta)

# Segunda pareja 
# Marilyn + Einstein
print("--- Segunda pareja ---\n")
print("Mostramos la segunda pareja de imágenes que vamos a hibridar")
imagen_marilyn = cv2.imread(path + "marilyn.bmp", 0)
imagen_einstein = cv2.imread(path + "einstein.bmp", 0)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_marilyn, imagen_einstein)), "Segunda pareja de imagenes")

sigma_baja = 4
sigma_alta = 4
imagen_hibrida = calc_imagen_hibrida(imagen_marilyn, sigma_baja, imagen_einstein, sigma_alta)
visualizar_hibridacion(imagen_hibrida, sigma_baja, sigma_alta)

# Tercera pareja
# Submarino + Pez
print("--- Tercera pareja ---\n")
print("Mostramos la tercera pareja de imágenes que vamos a hibridar")
imagen_submarino = cv2.imread(path + "submarine.bmp", 0)
imagen_pez = cv2.imread(path + "fish.bmp", 0)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_submarino, imagen_pez)), "Tercera pareja de imagenes")

sigma_baja = 3
sigma_alta = 3
imagen_hibrida = calc_imagen_hibrida(imagen_submarino, sigma_baja, imagen_pez, sigma_alta)
visualizar_hibridacion(imagen_hibrida, sigma_baja, sigma_alta)
input("## Pulse tecla para continuar ##\n")


#%%
print("\n\n------------ Bonus 1 ------------\n\n")

print("Hacemos lo mismo que el ejercicio anterior pero ahora con color\n")

# Primera pareja
# Perro + Gato
print("--- Primera pareja ---\n")
print("Mostramos la primera pareja de imágenes que vamos a hibridar")
imagen_perro = cv2.imread(path + "dog.bmp", 1)
imagen_gato = cv2.imread(path + "cat.bmp", 1)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_perro, imagen_gato)), "Primera pareja de imagenes")

sigma_baja = 5
sigma_alta = 5
imagen_hibrida = calc_imagen_hibrida(imagen_perro, sigma_baja, imagen_gato, sigma_alta)
visualizar_hibridacion(imagen_hibrida, sigma_baja, sigma_alta)

# Segunda pareja
# Submarino + Pez
print("--- Segunda pareja ---\n")
print("Mostramos la segunda pareja de imágenes que vamos a hibridar")
imagen_submarino = cv2.imread(path + "submarine.bmp", 1)
imagen_pez = cv2.imread(path + "fish.bmp", 1)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_submarino, imagen_pez)), "Segunda pareja de imagenes")

sigma_baja = 3
sigma_alta = 3
imagen_hibrida = calc_imagen_hibrida(imagen_submarino, sigma_baja, imagen_pez, sigma_alta)
visualizar_hibridacion(imagen_hibrida, sigma_baja, sigma_alta)

# Tercera pareja 
# Moto + Bici
print("--- Tercera pareja ---\n")
print("Mostramos la tercera pareja de imágenes que vamos a hibridar")
imagen_moto = cv2.imread(path + "motorcycle.bmp", 1)
imagen_bici = cv2.imread(path + "bicycle.bmp", 1)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_moto, imagen_bici)), "Tercera pareja de imagenes")

sigma_baja = 8
sigma_alta = 4
imagen_hibrida = calc_imagen_hibrida(imagen_moto, sigma_baja, imagen_bici, sigma_alta)
visualizar_hibridacion(imagen_hibrida, sigma_baja, sigma_alta)

# Cuarta pareja
# Avión + Pájaro
print("--- Cuarta pareja ---\n")
print("Mostramos la cuarta pareja de imágenes que vamos a hibridar")
imagen_avion = cv2.imread(path + "plane.bmp", 1)
imagen_pajaro = cv2.imread(path + "bird.bmp", 1)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((imagen_avion, imagen_pajaro)), "Cuarta pareja de imagenes")

sigma_baja = 8
sigma_alta = 5
imagen_hibrida = calc_imagen_hibrida(imagen_avion, sigma_baja, imagen_pajaro, sigma_alta)
visualizar_hibridacion(imagen_hibrida, sigma_baja, sigma_alta)
input("## Pulse tecla para continuar ##\n")

#%%
print("\n\n------------ Bonus 2 ------------\n\n")

print("En este apartado vamos a hibridar la cara de Lena con la cara de un gato\n")
print("Mostramos las imágenes con las que vamos a trabajar\n")
imagen_lena = cv2.imread(path + "lena.jpg", 1)
imagen_gato = cv2.imread(path + "cat.bmp", 1)

# Lena
print("Imagen completa de Lena")
input("## Pulse tecla para continuar ##\n")
pintaImagen(imagen_lena, "Imagen de Lena")

# Cara Lena
print("Mostramos la porción de la imagen que utilizamos")
cara_lena = imagen_lena[125:180, 125:175]
input("## Pulse tecla para continuar ##\n")
pintaImagen(cara_lena, "Cara de Lena")

# Gato
print("Imagen del gato")
input("## Pulse tecla para continuar ##\n")
pintaImagen(imagen_gato, "Imagen del gato")

# Cara gato
print("Mostramos la porción de la imagen que utilizamos")
cara_gato = imagen_gato[150:, 80:320]
input("## Pulse tecla para continuar ##\n")
pintaImagen(cara_gato, "Cara del gato")

# Comparar dimensiones
print("Las imágenes tienen distintas dimensiones")
print("Dimesión de la cara de Lena: ", cara_lena.shape[:-1])
print("Dimesión de la cara del gato: ", cara_gato.shape[:-1])

#%%
# Hibridamos reduciendo la cara del gato al mismo tamaño que la cara de Lena
print("\nPrimero probamos reduciendo la cara del gato al tamaño de la cara de Lena")
cara_gato_reducida = cv2.resize(cara_gato, cara_lena.shape[-2::-1], interpolation=cv2.INTER_LINEAR)
input("## Pulse tecla para continuar ##\n")
pintaImagen(cara_gato_reducida, "Cara del gato reducida")

print("Realizamos la hibridación")
sigma_baja = 2
sigma_alta = 3
imagen_hibrida1 = calc_imagen_hibrida(cara_lena, sigma_baja, cara_gato_reducida, sigma_alta)
input("## Pulse tecla para continuar ##\n")
visualizar_hibridacion(imagen_hibrida1, sigma_baja, sigma_alta)

#%%
# Hibridamos escalando la cara de Lena al mismo tamaño que la cara del gato
print("Probamos ahora a escalar la cara de Lena al tamaño de la cara del gato")
cara_lena_aumentada = cv2.resize(cara_lena, cara_gato.shape[-2::-1], interpolation=cv2.INTER_LINEAR)
input("## Pulse tecla para continuar ##\n")
pintaImagen(cara_lena_aumentada, "Cara de Lena aumentada")

print("Realizamos la hibridación")
sigma_baja = 6
sigma_alta = 6
imagen_hibrida = calc_imagen_hibrida(cara_lena_aumentada, sigma_baja, cara_gato, sigma_alta)
input("## Pulse tecla para continuar ##\n")
visualizar_hibridacion(imagen_hibrida, sigma_baja, sigma_alta)

#%%
# Hibridamos escalando las dos caras a un mismo tamaño intermedio
print("Otra opción es escalar las dos imágenes a un tamaño intermedio")
cara_lena_aumentada = cv2.resize(cara_lena, (128, 128), interpolation=cv2.INTER_LINEAR)
cara_gato_reducida = cv2.resize(cara_gato, (128, 128), interpolation=cv2.INTER_LINEAR)
input("## Pulse tecla para continuar ##\n")
pintaImagen(np.hstack((cara_lena_aumentada, cara_gato_reducida)), "Ambas imagenes escaladas")

print("Realizamos la hibridación")
sigma_baja = 4
sigma_alta = 4
imagen_hibrida2 = calc_imagen_hibrida(cara_lena_aumentada, sigma_baja, cara_gato_reducida, sigma_alta)
input("## Pulse tecla para continuar ##\n")
visualizar_hibridacion(imagen_hibrida2, sigma_baja, sigma_alta)
