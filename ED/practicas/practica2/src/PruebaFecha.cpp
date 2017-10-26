/**
  * @file PruebaFecha.cpp
  * @brief Ejemplo de uso de la clase FechaHistorica
  *
  */

#include"FechaHistorica.h"
#include<iostream>

int main(){
  FechaHistorica fecha;
  VectorDinamico<std::string> v;

  v.push("Guardians of the Galaxy Vol. 2");
  v.push("Star Wars: Episode VIII");
  std::cout << v[0] << " " << v[1] << std::endl;
  std::cout << std::endl;
  // Guardians of the Galaxy Vol. 2 Star Wars: Episode VIII

  FechaHistorica fecha1(2017,v);
  FechaHistorica fecha2(fecha1);
  std::cout << fecha1 << std::endl;
  std::cout << fecha2 << std::endl;
  std::cout << std::endl;
  // 2017#Guardians of the Galaxy Vol. 2#Star Wars: Episode VIII
  // 2017#Guardians of the Galaxy Vol. 2#Star Wars: Episode VIII

  std::cout << fecha1.getYear() << std::endl;
  std::cout << std::endl;

  std::string str = "Beauty and the Beast";
  fecha2.add(str);
  std::cout << fecha1 << std::endl;
  std::cout << fecha2 << std::endl;
  std::cout << std::endl;
  // 2017#Guardians of the Galaxy Vol. 2#Star Wars: Episode VIII
  // 2017#Guardians of the Galaxy Vol. 2#Star Wars: Episode VIII#Beauty and the Beast

  FechaHistorica buscar;
  if(fecha2.find(str,buscar))
    std::cout << buscar << std::endl;
    std::cout << std::endl;
    // 2017#Beauty and the Beast

  fecha = buscar;
  std::cout << fecha << std::endl;
  std::cout << std::endl;
  // 2017#Beauty and the Beast
}
