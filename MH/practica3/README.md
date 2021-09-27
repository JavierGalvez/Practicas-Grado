# Fichero incluidos
data/    : carpeta con los conjuntos de datos y restricciones utilizados\
include/ : carpeta con los archivos .h\
obj/     : carpeta donde se almacenan los .o \
output/  : carpeta donde se almacenarán las salidas de los algoritmos\
src/     : carpeta con el código fuente\

### Ficheros en include/ ###

algorithms.h : definición de los algoritmos de la práctica\
solution.h   : definición del struct Solution utilizado para representar soluciones\
score.h      : definición de la función objetivo\
global.h     : variables globales del problema\
extern.h     : archivo auxiliar para el uso de las variables globales\

### Ficheros en src/ ###

main.cpp         : programa principal de la práctica, para ver como ejecutarlo leer la documentación\
bmb.cpp          : implementación de la búsqueda multiarranque básica\
es.cpp           : implementación del enfriamiento simulado\
ils.cpp          : implementación de la búsqueda local iterativa\
local_search.cpp : implementación de la búsqueda local utilizada en los otros algoritmos\
score.cpp        : implementación de la función objetivo\
solution.cpp     : generador de soluciones aleatorias
