/**
   @file testarteASCII.cpp
   @brief lee imagenes/gio.pgm y la convierte en ascii con los caracteres "@%#*+=-:. "
   @author MP-DGIM - Grupo A

**/
#include<iostream>
#include<imagen.h>

using namespace std;

int main(){
	 const int MAX=4500;
    char grises[] = "@#%xo;:,. ";
    char arteASCII[MAX+1]; // 4500 + el \0
    char imagen1[]="data/gio.pgm";
    Imagen origen;

    // Leer la imagen gio.pgm
    if (!origen.leerImagen(imagen1)){
	   cerr << "error leyendo "<< imagen1 << endl;
	   return 1;
    }

    cout << "\nLa imagen en arte ASCII es:\n";
    if(origen.aArteASCII(grises, arteASCII, MAX))
        cout << arteASCII;
    else
        cout << "La conversión no ha sido posible" << endl;

    cout << "Ahora Forzamos que no quepa. Debe aparecer un mensaje de error\n";
    if(origen.aArteASCII(grises, arteASCII, MAX/10))
        cout << arteASCII;
    else
        cout << "La conversión no ha sido posible" << endl;
}
