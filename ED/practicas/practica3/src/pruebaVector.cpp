/**
  * @file PruebaVector.cpp
  * @brief Ejemplo de uso de la clase VectorDinamico
  *
  */

#include "VectorDinamico.h"
#include<iostream>

int main(){
  VectorDinamico<int> numeros;
  VectorDinamico<int> numeros1(10);
  VectorDinamico<int> numeros2(numeros1);

  std::cout << numeros1.size() << std::endl;
  std::cout << numeros1.capacity() << std::endl;
  std::cout << std::endl;
  // 10 10

  numeros2.resize(numeros2.capacity()*2);
  std::cout << numeros2.size() << std::endl;
  std::cout << numeros2.capacity() << std::endl;
  std::cout << std::endl;
  // 10 20

  numeros2.resize(0);
  std::cout << numeros2.size() << std::endl;
  std::cout << numeros2.capacity() << std::endl;
  std::cout << std::endl;
  // 0 0

  numeros2.push(7);
  numeros2.push(2);
  numeros2.push(3);
  numeros2.push(4);
  std::cout << numeros2[0] << std::endl;
  std::cout << numeros2[1] << std::endl;
  std::cout << numeros2[2] << std::endl;
  std::cout << numeros2[3] << std::endl;
  std::cout << std::endl;
  // 7 2 3 4

  std::cout << numeros.size() << std::endl;
  std::cout << numeros.capacity() << std::endl;
  std::cout << std::endl;
  // 0 0

  numeros.push(3);
  numeros.push(1);
  std::cout << numeros[0] << std::endl;
  std::cout << numeros[1] << std::endl;
  std::cout << std::endl;
  // 3 1

  numeros1 = numeros;
  numeros1.push(7);
  numeros1[1] = 9;

  numeros = numeros1;
  std::cout << numeros[0] << std::endl;
  std::cout << numeros[1] << std::endl;
  std::cout << numeros[2] << std::endl;
  //3 9 7
}
