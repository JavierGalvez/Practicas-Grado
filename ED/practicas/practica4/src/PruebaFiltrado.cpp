/**
  * @file PruebaFiltrado.cpp
  * @brief Ejemplo de uso del método find de la clase Cronologia
  *
  */

#include <fstream>
#include <iostream>
#include <string>
#include "Cronologia.h"

int main(int argc, char * argv[]){
  if (argc<2 or argc>4){
    std::cout << "Error al introducir los parámetros" << std::endl;
    std::cout << "Cronologia - Palabra clave (opcional) - Salida (.txt) (opcional)" << std::endl;
    return 0;
  }

  std::ifstream fi (argv[1]);
  if (!fi) return 0;

  Cronologia c;
  fi >> c;


  if(argc == 2){
    std::string key;
    std::cout << "Introduce la palabra clave: ";
    std::cin >> key;
    std::cout << c.find(key).first;
  }
  else if(argc == 3){
    std::string arg2 = argv[2];
    if(arg2.substr(arg2.length()-4, 4) == ".txt"){
      std::string key;
      std::cout << "Introduce la palabra clave: ";
      std::cin >> key;

      std::ofstream fo (argv[2]);
      if(!fo) return 0;

      fo << c.find(key).first;

    } else {
      std::cout << c.find(argv[2]).first;
    }
  }
  else if(argc == 4){
    std::string arg3 = argv[3];
    if(arg3.substr(arg3.length()-4, 4) == ".txt"){
      std::ofstream fo (argv[3]);
      if(!fo) return 0;
      fo << c.find(argv[2]).first;
    } else {
      std::cout << "Error al introducir los parámetros" << std::endl;
      std::cout << "Cronologia - Palabra clave (opcional) - Salida (.txt) (opcional)" << std::endl;
    }
  }
}
