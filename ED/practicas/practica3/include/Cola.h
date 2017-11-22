/**
  * @file Cola.h
  * @brief Fichero cabecera del T.D.A Cola
  *
  */

#ifndef __COLA_H__
#define __COLA_H__

/**
  * @brief T.D.A Cola
  *
  * Una instancia @e c del tipo de dato @c Cola es un objeto con 3 campos,
  * un entero con el número de elementos almacenados y dos punteros first y last
  * que apuntan al primer y último elemento de la cola respectivamente.
  *
  * Lo podemos representar de la siguiente forma:
  *
  * in => back data data front => out  (FIFO)
  *
  * Un ejemplo de su uso:
  * @include pruebaCola.cpp
  *
  * @author Javier Gálvez Obispo
  *
  */

template <class T>
class Cola{
  private:

    /**
      * @page repCola Rep del T.D.A Cola
      *
      * @section invCola Invariante de la representación
      *
      * Un objeto válido @e c debe cumplir:
      * - @c c.n >= 0
      * - @c c.first apunta a una zona de memoria con capacidad para albergar
      * - @c c.last apunta a una zona de memoria con capacidad para albergar
      *
      * @section faCola Función de abstracción
      *
      * Un objeto válido @e rep representa a la cola de tamaño @e n
      *
      * in => back data data front => out  (FIFO)
      *
      */

    /**
      * @brief Struct para las celdas de la cola
      */

    struct Celda{
      T val;        /**< Valor almacenado en la celda */
      Celda *next;  /**< Puntero a la siguiente celda */

      /**
        * @brief Constructor por defecto del struct Celda
        * Crea un elemento del tipo Celda con el puntero next nulo
        */

      Celda():next(0){}
    };

    Celda *first; /**< Apunta al primer elemento de la cola */
    Celda *last;  /**< Apunta al último elemento de la cola */
    int n;        /**< Número de elementos de la cola */

  public:


    /**
      * @brief Constructor por defecto de la clase
      * Crea un objeto de la clase con los punteros nulos y n = 0
      */

    Cola();


    /**
      * @brief Destructor de la clase
      * Elimina todas las celdas
      */

    ~Cola();


    /**
      * @brief Método que devuelve si la cola está vacía o no
      * @return Devuelve un bool con la respuesta
      */

    bool empty() const;


    /**
      * @brief Método que devuelve el número de elementos de la cola
      * @return int con el valor de n
      */

    int size() const;


    /**
      * @brief Método que añade un elemento al final de la cola
      * @param val elemento a añadir
      */

    void push(const T& val);


    /**
      * @brief Método que elimina el primer elemento de la cola
      * @pre La cola no puede estar vacía
      */

    void pop();


    /**
      * @brief Acceso al primer elemento
      * @return La referencia constante a dicho elemento
      * @pre La cola no puede estar vacía
      */

    T& front();


    /**
      * @brief Acceso constante al primer elemento
      * @return La referencia constante a dicho elemento
      * @pre La cola no puede estar vacía
      */

    const T& front() const;


    /**
      * @brief Acceso al último elemento
      * @return La referencia a dicho elemento
      * @pre La cola no puede estar vacía
      */

    T& back();


    /**
      * @brief Acceso constante al último elemento
      * @return La referencia constante a dicho elemento
      * @pre La cola no puede estar vacía
      */

    const T& back() const;
};

#include "../src/Cola.cpp"
#endif
