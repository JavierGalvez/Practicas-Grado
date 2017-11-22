/**
  * @file PilaMaxVD.cpp
  * @brief Implementación del T.D.A mstack (PilaMaxVD) usando el T.D.A VectorDinamico
  *
  */

#include <cassert>

template<class T>
mstack<T>::mstack(){}

template<class T>
mstack<T>::~mstack(){}

template<class T>
bool mstack<T>::greater(const T& val){
  return val > vector[size()-1].max;
}

template<class T>
bool mstack<T>::empty() const{
  return size() == 0;
}

template<class T>
int mstack<T>::size() const{
  return vector.size();
}

template<class T>
void mstack<T>::push(const T& val){
  pair aux;
  aux.val = val;
  aux.max = val;
  if(!empty() && !greater(val))
    aux.max = vector[size()-1].max;
  vector.push(aux);
}

template<class T>
void mstack<T>::pop(){
  if(!empty()){
    vector.resize(size()-1);
  }
}

template<class T>
T& mstack<T>::top(){
  assert(!empty());
  return vector[size()-1].val;
}

template<class T>
const T& mstack<T>::top() const{
  assert(!empty());
  return vector[size()-1].val;
}

template<class T>
int mstack<T>::maximum() const{
  assert(!empty());
  return vector[size()-1].max;
}
