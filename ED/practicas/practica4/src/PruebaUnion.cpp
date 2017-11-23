/**
  * @file PruebaUnion.cpp
  * @brief Ejemplo de uso del método operator+ de la clase Cronologia
  *
  */

#include <fstream>
#include <iostream>
#include "Cronologia.h"

int main(int argc, char * argv[]){
  if (argc!=4){
    std::cout << "Error al introducir los parámetros" << std::endl;
    return 0;
  }

  std::ifstream fi (argv[1]);
  if (!fi) return 0;

  Cronologia c1;
  fi >> c1;

  fi.close();
  fi.open(argv[2]);
  if(!fi) return 0;

  Cronologia c2;
  fi >> c2;

  std::ofstream fo (argv[3]);
  if(!fo) return 0;
  fo << c1 + c2;

}
