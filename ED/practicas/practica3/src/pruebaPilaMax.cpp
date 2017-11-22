/**
  * @file pruebaPilaMax.cpp
  * @brief Ejemplo de uso del T.D.A mstack (PilaMax)
  *
  */

#include <iostream>
#include "PilaMax.h"

int main (){
  mstack<double> mystack;

  if(mystack.empty())
    std::cout << "Empty" << std::endl;

  mystack.push(10);
  mystack.push(20);

  std::cout << "\nMáximo = " << mystack.maximum() << std::endl;
  std::cout << "Tamaño de la pila: " << mystack.size() << std::endl;
  std::cout << "mystack.top() = " << mystack.top() << std::endl;

  mystack.pop();

  std::cout << "\nTamaño de la pila: " << mystack.size() << std::endl;
  std::cout << "mystack.top() = " << mystack.top() << std::endl;

  mystack.top() -= 5;
  std::cout << "mystack.top() = " << mystack.top() << std::endl;

  mystack.pop();
  if(mystack.empty())
    std::cout << "\nEmpty" << std::endl;

  for(int i=1; i!=20; i++) mystack.push(i);

  std::cout << "\nTamaño de la pila: " << mystack.size() << std::endl;
  std::cout << "Máximo = " << mystack.maximum() << std::endl;
  std::cout << "=== Popping ===" << std::endl;
  while(!mystack.empty()){
    std::cout << mystack.top() << std::endl;
    mystack.pop();
  }
  std::cout << "Tamaño de la pila: " << mystack.size() << std::endl;

  return 0;
}
