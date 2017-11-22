/**
  * @file PilaMaxCola.cpp
  * @brief Implementación del T.D.A mstack (PilaMaxCola) usando el T.D.A Cola
  *
  */

#include<cassert>

template<class T>
mstack<T>::mstack(){}

template<class T>
mstack<T>::~mstack(){}

template<class T>
bool mstack<T>::greater(const T& val){
  return val > queue.back().max;
}

template<class T>
bool mstack<T>::empty() const{
  return queue.empty();
}

template<class T>
int mstack<T>::size() const{
  return queue.size();
}

template<class T>
void mstack<T>::push(const T& val){
  pair aux;
  aux.val = val;
  aux.max = val;
  if(!empty() && !greater(val))
    aux.max = queue.back().max;
  queue.push(aux);
}

template<class T>
void mstack<T>::pop(){
  T aux;
  for(int i=0;i<size()-1;i++){
    aux = queue.front().val;
    push(aux);
    queue.pop();
  }
  queue.pop();
}

template<class T>
T& mstack<T>::top(){
  assert(!empty());
  return queue.back().val;
}

template<class T>
const T& mstack<T>::top() const{
  assert(!empty());
  return queue.back().val;
}

template<class T>
int mstack<T>::maximum() const{
  assert(!empty());
  return queue.back().max;
}
