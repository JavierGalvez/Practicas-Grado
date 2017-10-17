#include <iostream>
#include "lista.h"
#include "imagen.h"
#include <cstring>
#include <cmath>
#include <stdlib.h> //Hacer que atoi funcione
#include <stdio.h>

using namespace std;


int main(int nargs, char** args){
	
	const int MAX_NOMBRE = 150;
	char fichero1[MAX_NOMBRE], fichero2[MAX_NOMBRE], destino[MAX_NOMBRE];
	int npasos;
	
	
	if(nargs != 5){
		cerr << "Error en el número de argumentos" << endl;
		return 1;
	}

	Lista lista;

	Imagen imagen1;
	Imagen imagen2;
	strcpy(fichero1,args[1]);
	strcpy(fichero2,args[2]);
	
	if (!imagen1.leerImagen(fichero1)){
    	cerr << "error leyendo "<< fichero1 << endl;
    	return 1;
  	}
  	if (!imagen2.leerImagen(fichero2)){
    	cerr << "error leyendo "<< fichero2 << endl;
    	return 1;
  	}
	
	npasos = atoi(args[3]);
	cout << npasos << endl;
	// Hay que comprobar que sean del mismo tamaño
	for(int k = 0; k <= npasos; k++){
		Imagen img_salida = Imagen(imagen1.filas(), imagen1.columnas());
		for(int i = 0; i < imagen1.filas(); i++){
			for(int j = 0; j < imagen1.columnas(); j++){
				Byte pixel = imagen1.get(j,i) + (k * (imagen2.get(j,i) - imagen1.get(j,i)) / npasos);
				img_salida.set(j,i,pixel);
			}
		}
		lista.insertarFinal(img_salida);
	}
	
	strcpy(destino,args[4]);
	
	for(int k = 0; k <= lista.longitud(); k++){
		Imagen * aux = lista.get(k);
		char nombre[MAX_NOMBRE];
		sprintf(nombre, "%s_%d.pgm",destino,k);
		if (aux->escribirImagen(nombre, false)){
			cout << nombre << " guardado correctamente \n";
			cout << "usa: display " << nombre << " para ver el resultado\n";
		}
		else{
			cerr << "Error guardando la imagen " << nombre << endl;
			return 1;
		}
	}

	return 0;
}
