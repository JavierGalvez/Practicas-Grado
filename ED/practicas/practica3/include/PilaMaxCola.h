/**
  * @file PilaMaxCola.h
  * @brief Fichero cabecera del T.D.A mstack (PilaMaxCola) usando el T.D.A Cola
  *
  */

#ifndef __PILAMAXCOLA_H__
#define __PILAMAXCOLA_H__

#include "Cola.h"

/**
  * @brief T.D.A mstack
  *
  * Una instancia @e c del tipo de dato @c mstack es un objeto con 1 campo,
  * una Cola de parejas que almacenan un valor y el máximo cuando se introdujo dicho valor
  *
  * Lo podemos representar de la siguiente forma:
  *
  * @verbatim
  * top => <val,max>   (LIFO)
  *        <val,max>
  *        <val,max>
  *        <val,max>
  *        <val,max> @endverbatim
  *
  * Un ejemplo de su uso:
  * @include pruebaPilaMax.cpp
  *
  * @author Javier Gálvez Obispo
  *
  */

template <class T>
class mstack{
  private:

    /**
      * @page repmstack Rep del T.D.A mstack
      *
      * @section invmstack Invariante de la representación
      *
      * Un objeto válido @e s debe cumplir:
      * - @c Los elementos que se introducen tienen definida la operación >
      *
      * @section famstack Función de abstracción
      *
      * Un objeto válido @e rep representa a la pila de tamaño @e n
      *
      * @verbatim
      * top => <val,max>   (LIFO)
      *        <val,max>
      *        <val,max>
      *        <val,max>
      *        <val,max> @endverbatim
      */

    /**
      * @brief Struct para las parejas de la pila
      */

    struct pair{
      T val;    /**< Valor almacenado en la pila */
      T max;    /**< Máximo a la hora de introducir el elemento */
    };

    Cola<pair> queue;   /**< Cola que simula la utilización de una pila */


    /**
      * @brief Método que cálcula el máximo de la cola, sólo te utiliza al introducir un elemento.
      * @return Devuelve un bool con la respuesta
      */

    bool greater(const T& val);

  public:


    /**
      * @brief Constructor por defecto de la clase
      * Crea una pila vacia
      */

    mstack();


    /**
      * @brief Destructor de la clase
      */

    ~mstack();


    /**
      * @brief Método que devuelve si la pila está vacía o no
      * @return Devuelve un bool con la respuesta
      */

    bool empty() const;


    /**
      * @brief Método que devuelve el número de elementos de la pila
      * @return int con el tamaño de pila
      */

    int size() const;


    /**
      * @brief Método que añade un elemento a la pila
      * @param val elemento a añadir
      */

    void push(const T& val);


    /**
      * @brief Método elemina el elemento en lo alto de la pila
      * @pre La pila no puede estar vacía
      */

    void pop();


    /**
      * @brief Acceso al elemento en lo alto de la pila
      * @return La referencia a dicho elemento
      * @pre La pila no puede estar vacía
      */

    T& top();


    /**
      * @brief Acceso constante al elemento en lo alto de la pila
      * @return La referencia constante a dicho elemento
      * @pre La pila no puede estar vacía
      */

    const T& top() const;


    /**
      * @brief Acceso al máximo de la pila
      * @return int con el valor del máximo
      */

    int maximum() const;
};

#include "../src/PilaMaxCola.cpp"
#endif
