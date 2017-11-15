#ifndef __PILAMAXVD_H__
#define __PILAMAXVD_H__

#include "VectorDinamico.h"

template <class T>
class mstack{
  private:
    struct pair{
      T val;
      T max;
    };

    VectorDinamico<pair> vector;

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

#include "../src/PilaMaxVD.cpp"
#endif
