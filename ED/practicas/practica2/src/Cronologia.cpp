/**
  * @file Cronologia.cpp
  * @brief Implementación del TDA Cronologia
  *
  */

#include "Cronologia.h"
#include<iostream>
#include<sstream>
#include<string>

void Cronologia::sort(){
  for(int i=0;i!=eventos.size()-1;i++)
    for(int j=0;j<eventos.size()-i-1;j++)
      if(eventos[j].getYear() > eventos[j+1].getYear()){
        FechaHistorica aux;
        aux = eventos[j];
        eventos[j] = eventos[j+1];
        eventos[j+1] = aux;
      }
}

Cronologia::Cronologia(){}

Cronologia::Cronologia(const VectorDinamico<FechaHistorica>& v){
  eventos = v;
}

Cronologia::Cronologia(const Cronologia& c){
  eventos = c.eventos;
}

void Cronologia::add(const FechaHistorica& f){
  eventos.push(f);
  sort();
}

Cronologia::~Cronologia(){}

bool Cronologia::find(const int yy, FechaHistorica& f){
  bool encontrado = false;
  int mid;
  int first = 0;
  int last = eventos.size()-1;
  while((first<=last) && !encontrado){
    mid = (first+last)/2;
    if(eventos[mid].getYear() == yy){
      encontrado = true;
      f = eventos[mid];
    }
    else if (eventos[mid].getYear() < yy)
      first = mid + 1;
    else
      last = mid - 1;
  }
  return encontrado;
}

bool Cronologia::find(const std::string str, Cronologia& c){
  bool encontrado = false;
  for(int i=0;i!=eventos.size();i++){
    FechaHistorica aux;
    if(eventos[i].find(str,aux)){
      c.add(aux);
      encontrado = true;
      }
    }
  return encontrado;
}

std::ostream& operator<<(std::ostream& os, const Cronologia& c){
  for(int i=0;i!=c.eventos.size();i++)
    os << c.eventos[i] << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Cronologia& c){
  while(is.good()){
      std::string str;
      std::getline(is,str);
      std::istringstream iss(str);
      FechaHistorica aux;
      iss >> aux;
      c.add(aux);
  }
  return is;
}
