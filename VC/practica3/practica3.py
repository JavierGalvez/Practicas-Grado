# -*- coding: utf-8 -*-
"""
@author: Javier Gálvez Obispo
"""

import cv2
import numpy as np
import random
from functools import reduce

# Función para mostrar por pantalla cualquier imagen
def pintar_imagen(im, titulo=""):
    # Trasladamos y escalamos la imagen al rango [0, 1]
    if np.min(im) < 0:
        im + abs(np.min(im))
    img_normalizada = cv2.normalize(im, None, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_32F)
    cv2.imshow(titulo, img_normalizada)
    cv2.waitKey(0)
    cv2.destroyWindow(titulo)

# Función para añadir 3 canales a una imagen en grises
def gray2rgb(img):
    img_rgb = cv2.normalize(img.astype(np.uint8), None, 0, 255, cv2.NORM_MINMAX)
    return cv2.cvtColor(img_rgb, cv2.COLOR_GRAY2RGB)

# Función que devuelve la pirámide Gaussiana de una imagen dada
def piramide_gaussiana(img, niveles):
    piramide = [img]
    for _ in range(niveles-1):
        piramide.append(cv2.pyrDown(piramide[-1]))
    return piramide

# Pinta en una sola imagen todos los niveles de una pirámide Gaussiana
def pintar_piramide(piramide, titulo=""):
    filas, columnas = piramide[0].shape[:2]
    columnas_extra = int(columnas / 2)

    # Creamos la imagen que hará de marco
    if len(piramide[0].shape) == 3:
        img = np.zeros((filas, columnas + columnas_extra, 3))
    else:
        img = np.zeros((filas, columnas + columnas_extra))

    # Colocamos la primera imagen
    img[:filas, :columnas] = piramide[0]

    # Añadimos las siguientes imágenes en su lugar correspondiente
    fila = 0
    for nivel in piramide[1:]:
        filas_nivel, columnas_nivel = nivel.shape[:2]
        img[fila:fila + filas_nivel, columnas:columnas + columnas_nivel] = nivel
        fila += filas_nivel

    pintar_imagen(img, titulo)

# Función para obtener los índices de una ventana rxr con centro (x, y)
def indices_ventana(x, y, r):
    arriba    = x - r
    abajo     = x + r + 1
    izquierda = y - r
    derecha   = y + r + 1
    
    if arriba < 0: arriba = 0
    if izquierda < 0: izquierda = 0
    
    return arriba, abajo, izquierda, derecha

# Función que realiza la supresión de no-máximos de una matriz f
def supresion_no_maximos(f, rango, umbral=10):
    filas, columnas = f.shape[:2]
    maximos = []
    
    for i in range(filas):
        for j in range(columnas):
            if f[i, j] > umbral:
                # Obtenemos la ventana
                arriba, abajo, izquierda, derecha = indices_ventana(i, j, rango)
                vecindario = f[arriba:abajo, izquierda:derecha]
                
                # Si es máximo local
                maximo_local = np.amax(vecindario)
                
                if f[i, j] == maximo_local:
                    # Guardamos el punto
                    maximos.append(((i, j), maximo_local))
                    
                    # Ponemos todo el vecindario a 0 para no volver a mirarlo
                    vecindario[:] = 0
                    
    return maximos

# Función para obtener los keypoints de una imagen utilizando Harris
def harris(img, block_size=3, k_size=3, ventana_supresion=3, mostrar=False, verbose=False):
    img = img.astype(np.float32)
    
    # Pirámide Gaussiana
    niveles=3
    piramide = piramide_gaussiana(img, niveles)
    
    # Derivadas
    img_alisada = cv2.GaussianBlur(img, ksize=(0,0), sigmaX = 4.5)
    img_dx = cv2.Sobel(img_alisada, -1, 1, 0)
    img_dy = cv2.Sobel(img_alisada, -1, 0, 1)
    piramide_dx = piramide_gaussiana(img_dx, niveles)
    piramide_dy = piramide_gaussiana(img_dy, niveles)
    
    piramide_keypoints = []
    keypoints_total = []
    keypoints_niveles = []
    
    topes_nivel = [1400, 500, 100]
    
    for i, (nivel, dx, dy) in enumerate(zip(piramide, piramide_dx, piramide_dy)):
        filas, columnas = nivel.shape[:2]
        
        # Calculamos f
        vals = cv2.cornerEigenValsAndVecs(nivel, block_size, k_size)
       
        f = np.empty_like(nivel, dtype=np.float32)
        lambda_1, lambda_2 = vals[:, :, 0], vals[:, :, 1]
        numerador, denominador = (lambda_1 * lambda_2), (lambda_1 + lambda_2 + 1e-15)
        f = np.divide(numerador, denominador, where=denominador!=0.0)
        
        # Supresión de máximos
        maximos = supresion_no_maximos(f, ventana_supresion)
        # Ordenamos de mayor a menor valor de f
        maximos = sorted(maximos, key=lambda x: x[1], reverse=True)
        
        angulos = cv2.phase(dx, dy, angleInDegrees=True)
        
        # Keypoints
        keypoints = []
        # Nos quedamos con los mejores puntos
        radio = 2 ** (i+1) * block_size
        t = 2 ** i
        for (y, x), val in maximos[:topes_nivel[i]]:
            angulo = int(angulos[(y, x)])
            # Keypoint nivel
            
            keypoints.append(cv2.KeyPoint(x, y, 2, _angle = angulo))
            
            # Keypoint imagen original
            keypoints_total.append(cv2.KeyPoint(t * x, t * y, radio, _angle = angulo))
        
        keypoints_niveles.append((len(keypoints), len(maximos)))
        
        # Pirámide con Keypoints
        if mostrar:
            img_rgb = gray2rgb(nivel) # Añadimos 3 canales y pasamos la imagen a enteros
            img_keypoints =  cv2.drawKeypoints(img_rgb, keypoints, None, 
                                               flags = cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
            piramide_keypoints.append(img_keypoints)
    
    if verbose:
        print("\n--- Keypoints ---")
        for i, (n, m) in enumerate(keypoints_niveles):
            print("Keypoints en el nivel %d: %d (%d)" % (i+1, n, m))
        print("\nKeypoints totales: %d (%d)" % ((len(keypoints_total), sum(m for n, m in keypoints_niveles))))
        
        distribucion = "Distribución de los keypoints: "
        for i, (n, m) in enumerate(keypoints_niveles):
            keypoints_niveles[i] =  n / len(keypoints_total) * 100
            distribucion += "{:.2f}% "
        print(distribucion.format(*keypoints_niveles))
        input("## Pulse tecla para continuar ##\n")
    
    # Pintar imágenes
    if mostrar:
        print("Keypoints obtenidos en cada escala")
        input("## Pulse tecla para continuar ##\n")
        pintar_piramide(piramide_keypoints, "Keypoints obtenidos en cada escala")
    
        # Imagen original con todos los keypoints obtenidos
        img_rgb = gray2rgb(img) # Añadimos 3 canales y pasamos la imagen a enteros
        img_keypoints =  cv2.drawKeypoints(img_rgb, keypoints_total, None,
                                           flags = cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    
        print("Keypoints obtenidos en total")
        input("## Pulse tecla para continuar ##\n")
        pintar_imagen(img_keypoints, "Keypoints obtenidos en total")

    return keypoints_total

# Función para realizar el refinamiento de los keypoints
def refinamiento_subpixel(img, keypoints, n=3, zoom=10, mostrar=False):
    
    puntos = np.array([ p.pt for p in keypoints ])
    puntos_refinados = puntos.astype(np.float32)
    
    # Refinamos
    entorno = 3
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 50, 0.01)
    cv2.cornerSubPix(img, puntos_refinados, (entorno, entorno), (-1, -1), criteria)
    
    if mostrar:
        # Elegimos 3 puntos aleatorios en los que haya habido refinamiento
        elegidos = []
        while len(elegidos) < n:
            idx = random.randint(0, len(puntos)-1)
            if idx not in elegidos and np.any(puntos[idx] != puntos_refinados[idx]):
                elegidos.append(idx)
            
        img_rgb = gray2rgb(img)
        r = 10
        d = (entorno+2) * 2 * zoom + zoom
        centro = d // 2
        canvas = np.zeros((d, d*n, 3))
        
        for i, idx in enumerate(elegidos):
            (y, x) = puntos[idx]
            (yr, xr) = puntos_refinados[idx]
            
            # Obtenemos la ventana
            arriba, abajo, izquierda, derecha = indices_ventana(int(x), int(y), entorno+2)
            ventana = img_rgb[arriba:abajo, izquierda:derecha]
            
            # Zoom x10
            ventana = cv2.resize(ventana, None, fx=zoom, fy=zoom)
            
            # Pintamos el punto original de rojo
            original = cv2.KeyPoint(centro, centro, r, _angle = keypoints[idx].angle)
            
            ventana =  cv2.drawKeypoints(ventana, [original], None, color=(0, 0, 255),
                                               flags = cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
            
            # Pintamos el punto corregido de azul
            corregido = cv2.KeyPoint(int((centro + (yr - y) * zoom)), int((centro + (xr - x) * zoom)), 
                                     r, _angle = keypoints[idx].angle)
            
            ventana =  cv2.drawKeypoints(ventana, [corregido], None, color=(255, 0, 0),
                                               flags = cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
            
            
            canvas[:ventana.shape[0], d*i:d*i+ventana.shape[1], :] = ventana
        
        pintar_imagen(canvas, "Puntos refinados")
            
    for i in range(len(keypoints)):
        keypoints[i].pt = tuple(puntos[i])
        
    return keypoints

    
# Función para obtener las correspondencias entre 2 imágenes usando Brute Force + Cross Check
def correspondencias_crosscheck(img1, img2):
    # Keypoints y descriptores
    akaze = cv2.AKAZE_create()
    kpts1, desc1 = akaze.detectAndCompute(img1, None)
    kpts2, desc2 = akaze.detectAndCompute(img2, None)
    
    # Brute Force + Cross Check
    bruteforce = cv2.BFMatcher_create(crossCheck=True)
    matches = bruteforce.match(desc1, desc2)
        
    return kpts1, kpts2, matches

# Función para obtener las correspondencias entre 2 imágenes usando Lowe-Average-2NN
def correspondencias_lowe(img1, img2):
    # Keypoints y descriptores
    akaze = cv2.AKAZE_create()
    kpts1, desc1 = akaze.detectAndCompute(img1, None)
    kpts2, desc2 = akaze.detectAndCompute(img2, None)
    
    # Lowe - Average - 2NN
    lowe = cv2.BFMatcher_create()    
    nn_matches = lowe.knnMatch(desc1, desc2, 2)
            
    # Nos quedamos con los suficientemente buenos
    matches = []
    nn_match_ratio = 0.75
    for m, n in nn_matches:
        if m.distance < nn_match_ratio * n.distance:
            matches.append(m)
            
    return kpts1, kpts2, matches
  
# Función para pintar las correspondencias entre 2 imágenes
def pintar_correspondencias(img1, kpts1, img2, kpts2, matches, titulo):
    # Pintamos 100 correspondencias aleatorias como máximo
    ejemplos = random.sample(matches, k=min(100, len(matches)))
    
    img_matches = cv2.drawMatches(img1.astype(np.uint8), kpts1, img2.astype(np.uint8), kpts2, 
                                  ejemplos, None, flags=cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)

    pintar_imagen(img_matches, titulo)
  
    
# Función para generar un mosaico a partir de N imágenes dadas
def generar_mosaico(imgs, alto=800, ancho=1200):    
    canvas = np.zeros((alto, ancho, 3), dtype=np.float32)
    
    centro = len(imgs) // 2
        
    # Traslación al centro
    tx = (ancho - imgs[centro].shape[1]) / 2
    ty = (alto - imgs[centro].shape[0]) / 2
    h_centro = np.array([[1, 0, tx], [0, 1, ty], [0, 0, 1]])
    
    # Ponemos la imagen central en el centro del canvas
    canvas = cv2.warpPerspective(imgs[centro], h_centro, (ancho, alto), dst=canvas, 
                                 borderMode=cv2.BORDER_TRANSPARENT)
    
    # Calculamos las homografías
    homografias = {}
    for i in range(len(imgs)):
        if i != centro:
            # Para las imágenes a la izquierda de la central calculamos la homografía hacia la derecha
            # Para las imágenes a la derecha de la central calculamos la homografía hacia la izquierda
            j = i + 1 if i < centro else i - 1
            
            kpts1, kpts2, matches = correspondencias_lowe(imgs[i], imgs[j])
            # puntos = (srcPoints, dstPoints)
            puntos = np.array([(kpts1[m.queryIdx].pt, kpts2[m.trainIdx].pt) for m in matches])
            
            homografias[i] = cv2.findHomography(puntos[:, 0], puntos[:, 1], cv2.RANSAC)[0]
    
    h_izquierda = h_centro
    h_derecha = h_centro

    # Empezamos desde el centro y vamos hacia el exterior
    for i in range(1, centro+1): 
        # Izquierda
        h_izquierda = np.dot(h_izquierda, homografias[centro - i])
        canvas = cv2.warpPerspective(imgs[centro - i], h_izquierda, (ancho, alto), dst=canvas, 
                                     borderMode=cv2.BORDER_TRANSPARENT)
    
        # Derecha
        j = centro + i
        if j < len(imgs): # Cuando len(imgs) es par se hace una iteración más por la izquierda
            h_derecha = np.dot(h_derecha, homografias[j])
            canvas = cv2.warpPerspective(imgs[j], h_derecha, (ancho, alto), dst=canvas, 
                                         borderMode=cv2.BORDER_TRANSPARENT)
        
    # Quitamos todo lo que sobra de la imagen
    area_usada = np.argwhere(canvas)
    esquina_superior = area_usada.min(axis=0)
    esquina_inferior = area_usada.max(axis=0)
    canvas = canvas[esquina_superior[0]:esquina_inferior[0]+1,
                    esquina_superior[1]:esquina_inferior[1]+1]
    
    return canvas
 
# Leemos las imágenes con las que vamos a trabajar

path = "./imagenes/"

yosemite1_gris = cv2.imread(path + "yosemite1.jpg", 0)
yosemite2_gris = cv2.imread(path + "yosemite2.jpg", 0)

yosemite1_color = cv2.imread(path + "yosemite1.jpg", 1)
yosemite2_color = cv2.imread(path + "yosemite2.jpg", 1)

img_mosaico = [ cv2.imread(path + "mosaico" + str(i).zfill(3) + ".jpg") for i in range(2, 12) ]

# Apartado 1
#%%
print("\n\n------------ Ejercicio 1 ------------\n\n")

print("Resultados Yosemite1.jpg")
input("## Pulse tecla para continuar ##\n")

keypoints = harris(yosemite1_gris, mostrar=True, verbose=True)

print("Refinamiento subpixel")
input("## Pulse tecla para continuar ##\n")
refinamiento_subpixel(yosemite1_gris, keypoints, mostrar=True)


print("Resultados Yosemite2.jpg")
input("## Pulse tecla para continuar ##\n")
keypoints = harris(yosemite2_gris, mostrar=True, verbose=True)

print("Refinamiento subpixel")
input("## Pulse tecla para continuar ##\n")
refinamiento_subpixel(yosemite2_gris, keypoints, mostrar=True)

input("## Pulse tecla para continuar ##\n")

# Apartado 2
#%%
print("\n\n------------ Ejercicio 2 ------------\n\n")
print("--- Brute Force + Cross Check ---")
input("## Pulse tecla para continuar ##\n")

kpts1, kpts2, matches = correspondencias_crosscheck(yosemite1_color, yosemite2_color)
pintar_correspondencias(yosemite1_color, kpts1, yosemite2_color, kpts2, matches, "Brute Force + Cross Check")

print("--- Lowe - Average - 2NN ---")
input("## Pulse tecla para continuar ##\n")

kpts1, kpts2, matches = correspondencias_lowe(yosemite1_color, yosemite2_color)
pintar_correspondencias(yosemite1_color, kpts1, yosemite2_color, kpts2, matches, "Lowe - Average - 2NN")

input("## Pulse tecla para continuar ##\n")

# Apartado 3
#%%
print("\n\n------------ Ejercicio 3 ------------\n\n")

hstack = lambda x, y: np.hstack((x, y))

print("Imágenes utilizadas")
input("## Pulse tecla para continuar ##\n")
imgs_utilizadas = reduce(hstack, img_mosaico[:3])
pintar_imagen(imgs_utilizadas, "Imágenes utilizadas ejercicio 3") 

print("Mosaico obtenido")
input("## Pulse tecla para continuar ##\n")
mosaico = generar_mosaico(img_mosaico[:3])
pintar_imagen(mosaico, "Mosaico ejercicio 3")

input("## Pulse tecla para continuar ##\n")

# Apartado 4
#%%
print("\n\n------------ Ejercicio 4 ------------\n\n")

print("Imágenes utilizadas")
input("## Pulse tecla para continuar ##\n")
imgs_utilizadas = np.vstack((reduce(hstack, img_mosaico[:5]), reduce(hstack, img_mosaico[5:])))
pintar_imagen(imgs_utilizadas, "Imágenes utilizadas ejercicio 4") 

print("Mosaico obtenido")
input("## Pulse tecla para continuar ##\n")
mosaico = generar_mosaico(img_mosaico)
pintar_imagen(mosaico, "Mosaico ejercicio 4")