/**
  * @file VectorDinamico.h
  * @brief Fichero cabecera de la clase template VectorDinamico
  *
  */

#ifndef _VECTOR_DINAMICO_
#define _VECTOR_DINAMICO_


/**
  * @brief Clase template VectorDinamico
  *
  * Una instancia @e c del tipo de dato @c VectorDinamico es un objeto con 3 campos,
  * dos enteros, uno con el números de elementos almacenados y otro con la capacidad
  * máxima de elementos a almacenar, y un puntero 1-dimensional del tipo que se indique
  *
  * Lo podemos representar de la siguiente forma:
  *
  * {dato[0], dato[1], ..., dato[n-1]}
  * con dato[i] siendo el valor almacenado en la posición i del puntero datos
  *
  * Un ejemplo de su uso:
  * @include PruebaVector.cpp
  *
  * @author Javier Gálvez Obispo
  *
  */

template <class T>
  class VectorDinamico{
  private:


    /**
      * @page repVectorDinamico Rep de la clase template VectorDinamico
      *
      * @section invVectorDinamico Invariante de la representación
      *
      * Un objeto válido @e v debe cumplir:
      * - @c v.n >= 0
      * - @c v.c >= v.n
      * - @c v.datos apunta a una zona de memoria con capacidad para albergar
      *   @c c valores de tipo que se indique
      *
      * @section faVectorDinamico Función de abstracción
      *
      * Un objeto válido @e rep representa al vector de tamaño @e n
      *
      * {dato[0], dato[1], ..., dato[n-1]}
      *
      */

    int n;    /**< Número de elementos del vector */
    int c;    /**< Número máximo de elementos que puede alcanzar el vector */
    T * datos;    /**< Apunta a los elementos del vector v */

  public:


    /**
      * @brief Constructor por defecto de la clase
      * Crea un objeto de la clase con n 0, c 0 y el vector nulo
      */

    VectorDinamico();

      /**
        * @brief Constructor de la clase
        * @param m indica el número de componentes inicial reservados para el vector
        * @return Crea un VectorDinamico con m elementos
        */


    VectorDinamico(int m);

      /**
        * @brief Constructor de copia de la clase
        * @param v VectorDinamico del que se copian los datos
        * @return Crea un VectorDinamico con los datos de v
        * @pre v debe ser del mismo tipo de VectorDinamico<T> que se desea crear
        */


    VectorDinamico(const VectorDinamico<T>& v);

      /**
        * @brief Destructor de la clase
        * Hace un delete del vector un pone a 0 n y c
        */


    ~VectorDinamico();

      /**
        * @brief Método que devuelve el número de elementos
        * @return int con el valor de n
        */


    int size() const;

      /**
        * @brief Método que devuelve el número de elementos máximo a almacenar
        * @return int con el valor de c
        */


    int capacity() const;

      /**
        * @brief Método que permite modificar el tamaño del vector
        * @param m nuevo tamaño del vector
        * @post Los valores almacenados no se pierden excepto si se salen
        *  del nuevo rango del vector
        */


    void resize(int m);

      /**
        * @brief Método que añade un elemento al final del vector
        * @param d elemento a añadir
        */


    void push(const T& d);

      /**
        * @brief Método que modifica un elemento del vector
        * @param i posición del vector que se quiere modificar
        * @param d elemento a añadir
        * @pre 0 <= i < size()
        */


    void insert(const int i,const T& d);

      /**
        * @brief Acceso a un elemento
        * @param i la posición del vector donde está el elemento
        * @return La referencia al elemento
        * @pre 0 <= i < size()
        */


    T& operator[](int i);

      /**
        * @brief Acceso a un elemento de un vector constante
        * @param i la posición del vector donde está el elemento.
        * @return La referencia al elemento.
        * @pre 0 <= i < size()
        */


    const T& operator[](int i) const;

      /**
        * @brief Operación de asignación
        * @param v VectorDinamico del que se copian los datos
        * @return La referencia al elemento
        * @pre v debe ser del mismo tipo de VectorDinamico<T>
        */


    VectorDinamico<T>& operator=(const VectorDinamico<T>& v);
  };

#include "VectorDinamico.cpp"
#endif  /* _VECTOR_DINAMICO_ */
