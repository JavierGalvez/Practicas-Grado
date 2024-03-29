/**
   @file main.cpp
   @brief Operaciones a nivel de bit
   @author MP-DGIM - Grupo A

**/

#include <iostream>
#include "byte.h"

using namespace std;

int main()
{
    Byte b;
    int posiciones[8];
    int size;
    bool inicial[] = {1,0,1,0,0,0,0,0};

    offByte(b);
    cout << "\nbyte apagado bits: ";
    imprimirByte(b); cout << endl;

	 // enciendo dos bits
    cout << "\nInicializo el byte a partir de un vector de bool ";
    asignarByte(b,inicial);
    imprimirByte(b); cout << endl;
    cout << "\nAhora enciendo los bits 0, 1 y 2 con la funcion on \n";
    onBit(b,0);
    imprimirByte(b); cout << endl;
    onBit(b,1);
    imprimirByte(b); cout << endl;
    onBit(b,2);
    imprimirByte(b); cout << endl;

    cout << "\nLos bits encendidos estan en las posiciones: ";
    encendidosByte(b,posiciones, size);
    for(int i=0; i< size; i++)
        cout << posiciones[i] << ",";

    cout << endl;

    cout << "\nTodos encendidos: ";
    onByte(b);
    imprimirByte(b); cout << endl;

    cout << "Todos apagados: ";
    offByte(b);
    imprimirByte(b); cout << endl;

    cout << "\n\nEjemplo 1 \n";
    // Completar
    onByte(b);
    imprimirByte(b); cout << endl;
    for(int i=0; i<8; i++){
      offBit(b,7-i);
      imprimirByte(b); cout << endl;
      onBit(b,7-i);
    }
 	 
    cout << "\nAhora la animacion\nEjemplo 2 \n";
    // Completar
    imprimirByte(b); cout << endl;
    for(int i=0; i<4; i++){
      offBit(b,i); offBit(b,7-i);
      imprimirByte(b); cout << endl;
    }
    for(int i=4; i<8; i++){
      onBit(b,i); onBit(b,7-i);
      imprimirByte(b); cout << endl;
    }
	 
	 
    return 0;
}
