# Reto 3: TDA lineales

El reto 3 tiene un planteamiento muy sencillo. Se trata de implementar la clase Pila
a partir de la clase Lista. La idea es que disponeis de la clase lista con toda la
implementación ya hecha y teneis que construir la clase pila a partir de esa implementación 
sin tener que implementar nuevo código, es decir que la implementación
de  las  funciones  se  hará  simplemente  llamando  a  funciones  ya  implementadas  de
las listas. P.ej la función quitar de la pila se podría construir a partir de la función
borrar de las listas, sin mas que activarla como p.borrar(p.begin()), supuesto que p
es de tipo lista (que se comporta como una pila)
