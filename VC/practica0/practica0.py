# -*- coding: utf-8 -*-
# Javier Gálvez Obispo

import cv2
from matplotlib import pyplot as plt

path = "imagenes/"

#%% Ejercicio 1

# flagColor => 0 grises, 1 color
def leeimagen(filename, flagColor):
    img = cv2.imread(filename, flagColor)
    cv2.imshow(filename, img)
    cv2.waitKey(0)
    cv2.destroyWindow(filename)
   
    
leeimagen(path + "orapple.jpg", 1) # ejemplo imagen con color
leeimagen(path + "messi.jpg", 0) # ejemplo imagen de grises

#%% Ejercicio 2

def pintaI(im):
    # Trasladamos y escalamos la imagen al rango [0, 1]
    img_normalizada = cv2.normalize(im, None, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_32F)
    cv2.imshow("Imagen", img_normalizada)
    cv2.waitKey(0)
    cv2.destroyWindow("Imagen")
    
# Leemos y pintamos la imagen
img = cv2.imread(path + "orapple.jpg", 1)
pintaI(img)

#%% Ejercicio 3

""""
Utilizamos matplotlib para simplificar el problema
En el caso de usar opencv hay que escalar las imágenes para que tengan el mismo tamaño y
hacer que todas las imágenes tengan el mismo número de canales para así poder concatenar las matrices
"""

def pintaMI(*vim):
    for i, (img, titulo) in enumerate(vim, start=1):
        plt.subplot(1, len(vim), i)
        # cv2.cvtColor(img, cv2.COLOR_BGR2RGB) convierte las imágenes BGR a RGB y las imágenes grises las deja igual
        plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        plt.axis("off")
        plt.title(titulo) # Ejercicio 5
    plt.show()

# Leemos las imágenes y las pintamos
img1 = cv2.imread(path + "orapple.jpg", 1)
img2 = cv2.imread(path + "messi.jpg", 0)
pintaMI((img1, "orapple"), (img2, "messi"))

#%% Ejercicio 4

def modificarI(img, pixels):
    for px, py in pixels:
        # Cuando la imagen tiene 3 canales / color
        if len(img.shape) == 3:
            for i in range(img[0][0].size):
                img.itemset((px, py, i), 0)
        # Cuando la imagen tiene 1 canal / grises
        else:
            img.itemset((px, py), 0)

# Leemos las imágenes
img_color = cv2.imread(path + "orapple.jpg", 1)
img_gris = cv2.imread(path + "orapple.jpg", 0)

# Las modificamos
pixeles_a_cambiar = [(x, y) for y in range(100) for x in range(100)]
modificarI(img_color, pixeles_a_cambiar)
modificarI(img_gris, pixeles_a_cambiar)

# Y pintamos
pintaMI((img_color, "Orapple color modificada"), (img_gris, "Orapple gris modificada"))
