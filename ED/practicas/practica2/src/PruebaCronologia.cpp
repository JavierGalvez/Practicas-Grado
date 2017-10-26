/**
  * @file PruebaCronologia.cpp
  * @brief Ejemplo de uso de la clase Cronologia
  *
  */

#include "Cronologia.h"
#include <fstream>
#include <iostream>

int main(int argc, char * argv[]){
  if (argc!=2){
    std::cout << "Error al introducir los parámetros" << std::endl;
    return 0;
  }

  std::ifstream f (argv[1]);
  if (!f){
    return 0;
  }

  Cronologia c;
  f >> c;

  Cronologia buscar;

  if(c.find("Sherlock",buscar)){
    std::cout << "Eventos encontrados con \"Sherlock\":" << std::endl;
    std::cout << buscar << std::endl;
    // 1900#Sherlock Holmes Baffled
    // 1905#Adventures of Sherlock Holmes; or, Held for Ransom
    // 1924#Sherlock Jr.

  }
  else
    std::cout << "No se han encontrado eventos con  \"Sherlock\"" << std::endl;

  Cronologia c2(buscar);
  FechaHistorica fecha;
  int yy = 1900;
  if(c2.find(yy,fecha)){
    std::cout << "Hay eventos registrados para el año " << yy << ": " << std::endl;
    std::cout << fecha << std::endl;
    // Hay eventos registrados para el año 1900:
    // 1900#Sherlock Holmes Baffled

  }
  else
    std::cout << "No hay eventos registrados para el año " << yy << std::endl;
}
