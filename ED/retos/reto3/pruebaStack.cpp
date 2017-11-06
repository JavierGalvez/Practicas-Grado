#include <iostream>
#include "stack.h"

int main (){
  stack<float> mystack;

  if(mystack.empty())
    std::cout << "Empty" << std::endl;

  mystack.push(10);
  mystack.push(20);

  std::cout << "\nTamaño de la pila: " << mystack.size() << std::endl;
  std::cout << "mystack.top() = " << mystack.top() << std::endl;

  mystack.pop();

  std::cout << "\nTamaño de la pila: " << mystack.size() << std::endl;
  std::cout << "mystack.top() = " << mystack.top() << std::endl;

  mystack.top() -= 5;
  std::cout << "\nmystack.top() = " << mystack.top() << std::endl;

  mystack.pop();
  if(mystack.empty())
    std::cout << "\nEmpty" << std::endl;

  mystack.pop();

  for(int i=1; i!=20; i++) mystack.push(i);

  std::cout << "\nTamaño de la pila: " << mystack.size() << std::endl;
  std::cout << "=== Popping ===" << std::endl;
  while(!mystack.empty()){
    std::cout << mystack.top() << std::endl;
    mystack.pop();
  }
  std::cout << "Tamaño de la pila: " << mystack.size() << std::endl;

  return 0;
}
