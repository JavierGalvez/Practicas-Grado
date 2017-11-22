/**
  * @file pruebaCola.cpp
  * @brief Ejemplo de uso del T.D.A Cola
  *
  */

#include "Cola.h"
#include<iostream>

int main(){
  Cola<float> myqueue;

  if(myqueue.empty())
    std::cout << "Empty" << std::endl;

  myqueue.push(10);
  myqueue.push(20);

  std::cout << "Tamaño de la cola: " << myqueue.size() << std::endl;
  std::cout << "myqueue.front() = " << myqueue.front() << std::endl;
  std::cout << "myqueue.back() = " << myqueue.back() << std::endl;

  myqueue.pop();

  std::cout << "\nTamaño de la cola: " << myqueue.size() << std::endl;
  std::cout << "myqueue.front() = " << myqueue.front() << std::endl;
  std::cout << "myqueue.back() = " << myqueue.back() << std::endl;

  myqueue.front() -= 5;
  std::cout << "\nmyqueue.back() = " << myqueue.back() << std::endl;

  myqueue.pop();
  if(myqueue.empty())
    std::cout << "\nEmpty" << std::endl;

  for(int i=1; i!=20; i++) myqueue.push(i);

  std::cout << "\nTamaño de la cola: " << myqueue.size() << std::endl;
  std::cout << "=== Popping ===" << std::endl;
  while(!myqueue.empty()){
    std::cout << myqueue.front() << std::endl;
    myqueue.pop();
  }
  std::cout << "Tamaño de la cola: " << myqueue.size() << std::endl;

  return 0;
}
