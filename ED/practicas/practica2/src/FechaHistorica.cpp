/**
  * @file FechaHistorica.cpp
  * @brief Implementación del TDA FechaHistorica
  *
  */

#include "FechaHistorica.h"
#include<iostream>
#include<string>
#include<stdlib.h>

FechaHistorica::FechaHistorica(){
  aa = 0;
}

FechaHistorica::FechaHistorica(const int yy,const VectorDinamico<std::string>& v){
  aa = yy;
  eventos = v;
}

FechaHistorica::FechaHistorica(const FechaHistorica &f){
  aa = f.aa;
  eventos = f.eventos;
}

FechaHistorica::~FechaHistorica(){}

int FechaHistorica::getYear(){
  return aa;
}

void FechaHistorica::add(const std::string& str){
  eventos.push(str);
}

bool FechaHistorica::find(const std::string str, FechaHistorica& f){
  bool encontrado = false;
  for(int i=0;i!=eventos.size();i++){
    if(eventos[i].find(str)!=-1){
      f.add(eventos[i]);
      encontrado = true;
    }
  }
  if(encontrado)
    f.aa = aa;
  return encontrado;
}

FechaHistorica& FechaHistorica::operator=(const FechaHistorica &f){
  aa = f.aa;
  eventos = f.eventos;
  return *this;
}


std::ostream& operator<<(std::ostream& os, const FechaHistorica& f){
  os << f.aa;
  for(int i=0;i!=f.eventos.size();i++){
    os << '#';
    os << f.eventos[i];
  }
  return os;
}

std::istream& operator>>(std::istream& is, FechaHistorica& f){
  std::string str;
  std::getline(is,str,'#');
  f.aa = atoi(str.c_str());
  while(is.good()){
    std::getline(is,str,'#');
    f.add(str);
  }
  return is;
}
