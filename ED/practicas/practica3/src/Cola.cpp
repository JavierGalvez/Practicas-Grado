/**
  * @file Cola.cpp
  * @brief Implementación del T.D.A Cola
  *
  */

#include <cassert>

template <class T>
Cola<T>::Cola(): first(0), last(0), n(0){}

template <class T>
Cola<T>::~Cola(){
  Celda *aux;
  while(first != 0){
    aux = first;
    first = first->next;
    delete aux;
  }
}

template <class T>
bool Cola<T>::empty() const{
  return n == 0;
}

template <class T>
int Cola<T>::size() const{
  return n;
}

template <class T>
void Cola<T>::push(const T& val){
  Celda *aux = new Celda;
  aux->val = val;
  if(empty())
    first = last = aux;
  else{
    last->next = aux;
    last = aux;
  }
  n++;
}

template <class T>
void Cola<T>::pop(){
  if(!empty()){
    Celda *aux = first;
    first = first->next;
    delete aux;
    n--;
    if(empty())
      last = 0;
  }
}

template <class T>
T& Cola<T>::front(){
  assert(!empty());
  return first->val;
}

template <class T>
const T& Cola<T>::front() const{
  assert(!empty());
  return first->val;
}

template <class T>
T& Cola<T>::back(){
  assert(!empty());
  return last->val;
}

template <class T>
const T& Cola<T>::back() const{
  assert(!empty());
  return last->val;
}
