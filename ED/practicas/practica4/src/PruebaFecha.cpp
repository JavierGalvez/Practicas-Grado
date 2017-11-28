/**
  * @file PruebaFecha.cpp
  * @brief Ejemplo de uso de la clase FechaHistorica
  *
  */

#include "FechaHistorica.h"
#include <iostream>
#include <set>
#include <sstream>    // std::istringstream

int main(){
  FechaHistorica fecha(2017);

  fecha.insert("Guardians of the Galaxy Vol. 2");
  fecha.insert("Star Wars: Episode VIII");
  std::cout << fecha << std::endl;
  // 2017#Guardians of the Galaxy Vol. 2#Star Wars: Episode VIII

  std::set<std::string> s;
  std::string movie = "Finding Dory";
  s.insert(movie);
  FechaHistorica fecha1(2016, s);
  std::cout << fecha1 << std::endl;
  // 2016#Finding Dory

  fecha1.erase(movie);
  std::cout << fecha1 << std::endl;
  // 2016

  FechaHistorica::iterator it = fecha1.insert("Deadpool").first;
  std::cout << fecha1 << std::endl;
  // 2016#Deadpool

  fecha1.erase(it);
  std::cout << fecha1 << std::endl;
  // 2016

  FechaHistorica fecha2(fecha);
  std::cout << fecha2.size() << std::endl;
  // 2
  fecha2.clear();
  std::cout << fecha2.size() << std::endl;
  // 0

  std::pair<int, std::set<std::string> > p;
  p.first = fecha2.year();
  movie = "Beauty and the Beast";
  p.second.insert(movie);
  FechaHistorica fecha3(p);
  std::cout << fecha3 << std::endl;
  // 2017#Beauty and the Beast


  FechaHistorica fecha4(2017);
  fecha4 + fecha;
  std::cout << fecha4 << std::endl;
  // 2017#Guardians of the Galaxy Vol. 2#Star Wars: Episode VIII

  std::string str = "2011#The Artist#Drive#The Intouchables";
  std::istringstream iss(str);
  iss >> fecha;
  std::cout << fecha << std::endl;
  // 2011#Drive#The Artist#The Intouchables

  if(fecha.find("The").second)
    std::cout << fecha.find("The").first << std::endl;
  // 2011#The Artist#The Intouchables
}
