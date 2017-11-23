/**
  * @file Cronologia.cpp
  * @brief Implementación del TDA Cronologia
  *
  */

#include <iostream>
#include <map>
#include <sstream>
#include "Cronologia.h"
#include "FechaHistorica.h"


Cronologia::Cronologia(){}

Cronologia::Cronologia(const std::map<int,FechaHistorica>& m){
  datos = m;
}

Cronologia::Cronologia(const Cronologia& c){
  datos = c.datos;
}

Cronologia::~Cronologia(){}

std::pair<Cronologia::iterator,bool> Cronologia::insert(const FechaHistorica& f){
  std::pair<Cronologia::iterator,bool> ret;
  ret = datos.insert(std::pair<int,FechaHistorica>(f.year(),f));
  return ret;
}

void Cronologia::erase(const int year){
  datos.erase(year);
}

void Cronologia::clear(){
  datos.clear();
}

Cronologia::iterator Cronologia::find(const int year){
  return datos.find(year);
}

std::pair<Cronologia,bool> Cronologia::find(const std::string& str){
  std::pair<Cronologia,bool> ret;
  ret.second = false;
  Cronologia aux;
  Cronologia::iterator it;
  for(it=begin(); it!=end(); ++it)
    if(it->second.find(str).second){
      aux.insert(it->second);
      ret.second = true;
    }
  ret.first = aux;
  return ret;
}

int Cronologia::size() const{
  return datos.size();
}

Cronologia Cronologia::interval(const int inf, const int sup){
  Cronologia c;
  Cronologia::iterator itlow = datos.lower_bound(inf);
  Cronologia::iterator itup = datos.upper_bound(sup);
  Cronologia::iterator it;
  for(it=itlow; it!=itup; ++it)
    c.insert(it->second);
  return c;
}

int Cronologia::totalEvents(){
  int total = 0;
  Cronologia::iterator it;
  for(it=begin(); it!=end(); ++it)
    total += it->second.size();
  return total;
}

int Cronologia::maxEvents(){
  Cronologia::iterator it;
  int max = 0;
  for(it=begin(); it!=end(); ++it)
    if(max < it->second.size())
      max = it->second.size();
  return max;
}

double Cronologia::averageEvents(){
  return totalEvents() / size();
}

FechaHistorica& Cronologia::at(const int year){
  return datos.at(year);
}

const FechaHistorica& Cronologia::at(const int year) const{
  return datos.at(year);
}

FechaHistorica& Cronologia::operator[](const int year){
  return datos.at(year);
}

const FechaHistorica& Cronologia::operator[](const int year) const{
  return datos.at(year);
}

Cronologia& Cronologia::operator=(const Cronologia& c){
  datos = c.datos;
  return *this;
}

Cronologia& Cronologia::operator+(const Cronologia& c){
  Cronologia::const_iterator it;
  for(it=c.begin(); it!=c.end(); ++it){
    Cronologia::iterator aux = datos.find(it->first);
    if(aux == end())
      insert(it->second);
    else
      datos.at(it->first) + it->second;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Cronologia& c){
  Cronologia::const_iterator it;
  for(it=c.begin(); it!=c.end(); ++it){
    os << it->second << std::endl;
  }
  return os;
}

std::istream& operator>>(std::istream& is, Cronologia& c){
  c.clear();
  std::string str;
  FechaHistorica aux;
  while(std::getline(is, str)){
    std::istringstream iss(str);
    iss >> aux;
    c.insert(aux);
  }
  return is;
}
