# Fichero incluidos
data/    : carpeta con los conjuntos de datos y restricciones utilizados\
include/ : carpeta con los archivos .h\
obj/     : carpeta donde se almacenan los .o \
output/  : carpeta donde se almacenarán las salidas de los algoritmos\
src/     : carpeta con el código fuente\

### Ficheros en include/ ###

algorithms.h : definición de los algoritmos de la práctica\
chromosome.h : definición del struct Chromosome utilizado para representar soluciones\
genetic.h    : definición de los operadores de los algoritmos genéticos\
score.h      : definición de la función objetivo\
global.h     : variables globales del problema\
extener.h    : archivo auxiliar para el uso de las variables globales\

### Ficheros en src/ ###

main.cpp         : programa principal de la práctica, para ver como ejecutarlo leer la documentación\
agg.cpp          : implementación de los algoritmos genéticos generacionales\
age.cpp          : implementación de los algoritmos genéticos estacionarios\
am.cpp           : implementación de los algoritmos meméticos\
genetic.cpp      : implementación de los operadores de los algoritmos genéticos\
local_search.cpp : implementación de la búsqueda local suave utilizada en los algoritmos meméticos\
score.cpp        : implementación de la función objetivo\
