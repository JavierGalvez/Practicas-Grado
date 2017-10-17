#include "byte.h"
#include <iostream>

void onBit(Byte &b, int pos){
  Byte mask = (0x1 << pos);
  b = b|mask;
}

void offBit(Byte &b, int pos){
  Byte mask = ~(0x1 << pos);
  b = b&mask;
}

bool getBit(Byte b, int pos){
  Byte mask = 0x1 << pos;
  return (b&mask) != 0x0;
}

void imprimirByte(Byte b){
  for(int i=0; i<8; i++){
    std::cout << getBit(b,7-i);
  }
}

void onByte(Byte &b){
  b= ~(0x0);
}

void offByte(Byte &b){
  b = 0x0;
}

void asignarByte(Byte &b, const bool v[]){
  offByte(b);
  for(int i=0; i<8; i++){
    if(v[i]){
      onBit(b,7-i);
    }
  }
}

void volcarByte(Byte b, bool v[]){
  for(int i=0; i<8; i++){
    v[i] = getBit(b,i);
  }
}

void encendidosByte(Byte b, int posic[], int &cuantos){
  cuantos = 0;
  for(int i=0; i<8; i++){
    if(getBit(b,i) == 1){
      posic[cuantos] = i;
      cuantos++;
    }
  }
}
