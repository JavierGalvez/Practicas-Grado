/**
  * @file PruebaCronologia.cpp
  * @brief Ejemplo de uso de la clase Cronologia
  *
  */

#include <iostream>
#include <map>
#include "Cronologia.h"

int main(){
  Cronologia c;

  std::map<int,FechaHistorica> m;
  FechaHistorica fecha(2017);
  fecha.insert("Guardians of the Galaxy Vol. 2");
  fecha.insert("Star Wars: Episode VIII");

  m.insert(std::pair<int,FechaHistorica>(fecha.year(),fecha));

  Cronologia c1(m);
  std::cout << c1 << std::endl;
  // 2017#Guardians of the Galaxy Vol. 2#Star Wars: Episode VIII

  c = c1;
  FechaHistorica fecha1(2016);
  fecha1.insert("Finding Dory");
  c.insert(fecha1);

  if(c.find(2016) != c.end()){
    std::cout << "La fecha histórica almacenada para el año 2016 en la cronologia 'c' es la siguiente: " << std::endl;
    std::cout << c.at(2016) << std::endl << std::endl;
  }
  else
    std::cout << "No se ha encontrado el año 2016 en la cronologia 'c'" << std::endl;
  // La fecha historica almacenada para el año 2016 en la cronologia 'c' es la siguiente:
  // 2016#Finding Dory

  Cronologia c2(c);
  c2.erase(2016);
  std::cout << c2 << std::endl;
  // 2017#Guardians of the Galaxy Vol. 2#Star Wars: Episode VIII

  c2.clear();
  std::cout << "El tamaño de la cronologia 'c2' es: " << c2.size() << std::endl;
  // El tamaño de la cronologia 'c2' es: 0

}
