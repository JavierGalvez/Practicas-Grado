/**
   @file testarteASCII.cpp
   @brief lee imagenes/gio.pgm y la convierte en ascii con los caracteres "@%#*+=-:. "
   @author MP-DGIM - Grupo A

**/
#include<iostream>
#include<imagen.h>
#include<fstream>
#include<cstring>

using namespace std;

int main(int nargs, char** args){

	if(nargs != 4){
		cerr << "Error en el número de argumentos" << endl;
		return 1;
	}

	const int MAX=4500;
	char arteASCII[MAX+1]; // 4500 + el \0
 	Imagen origen;

 	 //Lectura
  	const int MAX_NOMBRE = 200;
  	char fichero[MAX_NOMBRE], gris[MAX_NOMBRE], salida[MAX_NOMBRE];
  	int lineas_grises;

  	strcpy(fichero,args[1]);
  	if (!origen.leerImagen(fichero)){
    	cerr << "error leyendo "<< fichero << endl;
    	return 1;
  	}
  	else{
    	//Si existe el archivo seguimos
    	cout << "Imagen " << fichero << " leida correctamente" << endl;
    	strcpy(gris,args[2]);
    	strcpy(salida,args[3]);

   	 	ifstream fentrada;
   		fentrada.open(gris);
    	//Comprobamos que se abra bien
		if (fentrada){
     	 	fentrada >> lineas_grises;
     	 	//Para cada linea de grises hacemos un arteAscii
     	 	for (int i = 0; i < lineas_grises; i++){
      			fentrada >> gris;

      			if(origen.aArteASCII(gris, arteASCII, MAX)){
         		 	//Abrimos un stream para escribir a final del archivo
      	  			ofstream fsalida;
      	  			fsalida.open(salida, ios::app);
         	 		//Si se ha creado correctamente
      	 			if(fsalida){
      	   				 fsalida << "La imagen en arte ASCII (" << i << ") es:" << endl;
      	    			fsalida << arteASCII << endl;
      	  			}
      	  			else{
      	    			cerr << "Fallo con el fichero de salida" << endl;
   						fsalida.close();
   						return 1;
      	  			}
      	  			fsalida.close();
      			}
      			else{
      			  cerr << "La conversión no ha sido posible" << endl;
      			  return 1;
      			}
      		}
      		fentrada.close();
    	}
    	else{
      		cerr << "Error de apertura del fichero. \n";
      		return 1;
    	}
  	}

}
