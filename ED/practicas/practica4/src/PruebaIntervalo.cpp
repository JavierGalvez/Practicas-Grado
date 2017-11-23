/**
  * @file PruebaIntervalo.cpp
  * @brief Ejemplo de uso del método interval de la clase Cronologia
  *
  */

#include <fstream>
#include <iostream>
#include <stdlib.h>   // atoi
#include "Cronologia.h"

int main(int argc, char * argv[]){
  if (argc!=5){
    std::cout << "Error al introducir los parámetros" << std::endl;
    return 0;
  }

  std::ifstream fi (argv[1]);
  if (!fi) return 0;

  Cronologia c;
  fi >> c;

  std::ofstream fo (argv[4]);
  if(!fo) return 0;

  fo << c.interval(atoi(argv[2]),atoi(argv[3]));

}
