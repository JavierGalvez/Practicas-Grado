/**
  * @file FechaHistorica.cpp
  * @brief Implementación del TDA FechaHistorica
  *
  */

#include <iostream>
#include <set>
#include <stdlib.h>   // atoi
#include "FechaHistorica.h"



FechaHistorica::FechaHistorica(int year){
  datos.first = year;
}

FechaHistorica::FechaHistorica(const int year, const std::set<std::string>& s){
  datos.first = year;
  datos.second = s;
}

FechaHistorica::FechaHistorica(const std::pair<int,std::set<std::string> >& p){
  datos.first = p.first;
  datos.second = p.second;
}

FechaHistorica::FechaHistorica(const FechaHistorica& f){
  datos.first = f.datos.first;
  datos.second = f.datos.second;
}

FechaHistorica::~FechaHistorica(){}

int FechaHistorica::year() const{
  return datos.first;
}

std::pair<FechaHistorica::iterator,bool> FechaHistorica::insert(const std::string& str){
  return datos.second.insert(str);
}

void FechaHistorica::erase(std::string& str){
  datos.second.erase(str);
}

void FechaHistorica::erase(iterator it){
  datos.second.erase(it);
}

void FechaHistorica::clear(){
  datos.second.clear();
}

std::pair<FechaHistorica,bool> FechaHistorica::find(const std::string& str) const{
  std::pair<FechaHistorica,bool> ret;
  ret.second = false;
  FechaHistorica aux(datos.first);
  FechaHistorica::const_iterator it;
  for(it=begin(); it!=end(); ++it)
    if((*it).find(str) != -1){
      aux.insert((*it));
      ret.second = true;
    }
  ret.first = aux;
  return ret;
}

int FechaHistorica::size() const{
  return datos.second.size();
}

FechaHistorica& FechaHistorica::operator=(const FechaHistorica& f){
  datos.first = f.datos.first;
  datos.second = f.datos.second;
  return *this;
}

FechaHistorica& FechaHistorica::operator+(const FechaHistorica& f){
  if(datos.first == f.datos.first){
    FechaHistorica::iterator it;
    for(it=f.begin(); it!=f.end(); ++it)
      datos.second.insert((*it));
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const FechaHistorica& f){
  FechaHistorica::iterator it;
  os << f.datos.first;
  for(it=f.begin(); it!=f.end(); ++it){
    os << '#';
    os << (*it);
  }
  return os;
}
std::istream& operator>>(std::istream& is, FechaHistorica& f){
  std::string str;
  std::getline(is, str, '#');
  f.datos.first = atoi(str.c_str());
  f.clear();
  while(std::getline(is, str, '#')){
    f.insert(str);
  }
  return is;
}
