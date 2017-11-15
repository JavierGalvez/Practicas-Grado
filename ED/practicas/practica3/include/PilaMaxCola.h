#ifndef __PILAMAXCOLA_H__
#define __PILAMAXCOLA_H__

#include "Cola.h"

template <class T>
class mstack{
  private:
    struct pair{
      T val;
      T max;
    };

    Cola<pair> queue;

    bool greater(const T& val);

  public:
    mstack();
    ~mstack();
    bool empty() const;
    int size() const;
    void push(const T& val);
    void pop();
    T& top();
    const T& top() const;
    int maximum() const;
};

#include "../src/PilaMaxCola.cpp"
#endif
