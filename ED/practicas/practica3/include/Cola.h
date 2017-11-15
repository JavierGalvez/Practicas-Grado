#ifndef __COLA_H__
#define __COLA_H__

template <class T>
class Cola{
  private:
    struct Celda{
      T val;
      Celda *next;

      Celda():next(0){}
    };

    Celda *first;
    Celda *last;
    int n;

  public:
    Cola();
    ~Cola();
    bool empty() const;
    int size() const;
    void push(const T& val);
    void pop();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
};

#include "../src/Cola.cpp"
#endif
