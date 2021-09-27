# Fichero incluidos
data/    : carpeta con los conjuntos de datos y restricciones utilizados\
include/ : carpeta con los archivos .h\
obj/     : carpeta donde se almacenan los .o \
output/  : carpeta donde se almacenarán las salidas de los algoritmos\
src/     : carpeta con el código fuente\

### Ficheros en include/ ###

algorithms.h : definición de los algoritmos de la práctica\
tools.h      : definición de las herramientas necesarias para la ejecución\
score.h      : definición de la función objetivo\
global.h     : variables globales del problema\
extern.h     : archivo auxiliar para el uso de las variables globales\

### Ficheros en src/ ###

main.cpp         : programa principal de la práctica, para ver como ejecutarlo leer la documentación\
bbbc.cpp         : implementación de Big Bang Big Crunch\
local_search.cpp : implementación de la búsqueda local utilizada en los otros algoritmos\
score.cpp        : implementación de la función objetivo\
tools.cpp        : implementación de las herramientas
