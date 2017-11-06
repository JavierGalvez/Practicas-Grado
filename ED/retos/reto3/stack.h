/* Javier Gálvez Obispo */

#ifndef __STACK_H__
#define __STACK_H__

#include <list>
#include <cassert>

template <class T>
class stack{
  private:
    std::list<T> list;

  public:
    stack(){}
    ~stack(){}

    bool empty() const{
      return list.empty();
    }

    int size() const{
      return list.size();
    }

    // Insertamos al principio de la lista
    void push(const T& val){
      list.push_front(val);
    }

    // Eliminamos el primer elemento de la lista
    void pop(){
      if(size() > 0)
        list.pop_front();
    }

    T& top(){
      assert(size() > 0);
      return *list.begin();
    }

    const T& top() const{
      assert(size() > 0);
      return  *list.begin();
    }
};

#endif
