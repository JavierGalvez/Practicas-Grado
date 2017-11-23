/**
  * @file PruebaEstadistica.cpp
  * @brief Ejemplo de uso de los métodos sobre datos estadísticos de la clase Cronologia
  *
  */

#include <fstream>
#include <iostream>
#include "Cronologia.h"

int main(int argc, char * argv[]){
  if (argc!=2){
    std::cout << "Error al introducir los parámetros" << std::endl;
    return 0;
  }

  std::ifstream fi (argv[1]);
  if (!fi){
    return 0;
  }

  Cronologia c;
  fi >> c;

  std::cout << "Número total de años con eventos registrados: " << c.size() << std::endl;
  std::cout << "Número total de eventos: " << c.totalEvents() << std::endl;
  std::cout << "El mayor número de eventos registrados en un año es: " << c.maxEvents() << std::endl;
  std::cout << "La media de eventos registrados por año es: " << c.averageEvents() << std::endl;

}
