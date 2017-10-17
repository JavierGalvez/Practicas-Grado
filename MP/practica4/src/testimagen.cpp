/**
   @file testimagen.cpp
   @brief Crea una imagen degradada y hace un recorte a otra imagen
   @author MP-DGIM - Grupo A

**/
#include<iostream>
#include<imagen.h>

using namespace std;

int main(){
    Imagen origen;
    Imagen destino(150,200);
    char imagen1[]="data/degradado.pgm", imagen2[] = "data/lena.pgm", imagen3[] = "data/trozo.pgm";

	// Crear un degradado en la imagen destino
    for (int i=0; i < destino.filas()*destino.columnas(); i++)
		   destino.setPos(i, i%destino.columnas()+20);

  	// Guardar la imagen destino en el fichero degradado.pgm
  	if (destino.escribirImagen(imagen1, false)){
  		// si todo va bien
  		cout << imagen1 << " guardado correctamente \n";
  		cout << "usa: display " << imagen1 << " para ver el resultado\n";
  	} else { // si error
  		cerr << "Error guardando la imagen" <<  imagen1 << endl;
  		return 1;
  	}

  	// Leer la imagen lena.pgm
  	if (!origen.leerImagen(imagen2)){
  		cerr << "Error leyendo " << imagen2 << endl;
  		return 1;
  	}

  	// Recortar un trozo de la imagen origen
  	destino.crear(40,90);
  	for (int i=0; i < destino.filas(); i++)
  		for (int j=0; j < destino.columnas(); j++)
  			destino.set(i, j, origen.get(i+110,j+100));

  	// Guardar la imagen destino en el fichero trozo.pgm
  	if (destino.escribirImagen(imagen3, false)){
  		// si todo va bien
  		cout << imagen3 << " guardado correctamente \n";
  		cout << "usa: display " << imagen3 << " para ver el resultado\n";
  	} else { // si error
  		cerr << "Error guardando la imagen " << imagen3 << endl;
  		return 1;
  	}

  	return 0;
}
