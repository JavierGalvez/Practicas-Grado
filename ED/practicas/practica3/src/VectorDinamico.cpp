/**
  * @file VectorDinamico.cpp
  * @brief Implementación del T.D.A VectorDinamico
  *
  */

#include<cassert>

template<class T>
VectorDinamico<T>::VectorDinamico(){
  n = c = 0;
  datos = 0;
}

template<class T>
VectorDinamico<T>::VectorDinamico(int m){
  assert(m>=0);
  if(m>0)
    datos = new T[m];
  n = c = m;
}

template<class T>
VectorDinamico<T>::VectorDinamico(const VectorDinamico<T>& v){
  n = v.n;
  c = v.c;
  datos = new T[n];
  for(int i=0;i!=n;i++)
    datos[i] = v.datos[i];
}

template<class T>
VectorDinamico<T>::~VectorDinamico(){
  delete [] datos;
  n = c = 0;
}

template<class T>
int VectorDinamico<T>::size() const{
  return n;
}

template<class T>
int VectorDinamico<T>::capacity() const{
  return c;
}

template<class T>
void VectorDinamico<T>::resize(int m){
  assert(m>=0);
  T * aux = new T[m];
  if(n < m){
    for(int i=0;i!=n;i++)
      aux[i] = datos[i];
  }
  else{
    for(int i=0;i!=m;i++)
      aux[i] = datos[i];
    n = m;
  }
  if(datos != 0)
    delete [] datos;
  datos = aux;
  c = m;
}

template<class T>
void VectorDinamico<T>::push(const T& val){
  if(n == c){
    if(c == 0)
      resize(1);
    else
      resize(c*2);
  }
  datos[n] = val;
  n++;
}

template<class T>
void VectorDinamico<T>::insert(const int i,const T& val){
  assert(i >= 0 && i < n);
  datos[i] = val;
}

template<class T>
T& VectorDinamico<T>::operator[](int i){
  assert(i >= 0 && i < n);
  return datos[i];
}

template<class T>
const T& VectorDinamico<T>::operator[](int i) const{
  assert(i >= 0 && i < n);
  return datos[i];
}

template<class T>
VectorDinamico<T>& VectorDinamico<T>::operator=(const VectorDinamico<T>& v){
    T * aux = new T[v.n];
    for(int i=0;i!=v.n;i++)
      aux[i] = v.datos[i];
    if(datos != 0)
      delete [] datos;
    datos = aux;
    n = v.n;
    c = v.c;
    return *this;
}
