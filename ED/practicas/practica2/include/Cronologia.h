/**
  * @file Cronologia.h
  * @brief Fichero cabecera del TDA Cronologia
  *
  */

#ifndef _CRONOLOGIA_
#define _CRONOLOGIA_

#include "FechaHistorica.h"
#include<iostream>


/**
  *  @brief T.D.A. Cronologia
  *
  * Una instancia @e c del tipo de datos abstracto @c Cronologia es un objeto
  * con un campo, un VectorDinamico que almacena objetos del T.D.A. FechaHistorica
  *
  * Un ejemplo de su uso:
  * @include PruebaCronologia.cpp
  *
  * @author Javier Gálvez Obispo
  *
  */

class Cronologia{
private:

  /**
    * @page repCronologiaRep del TDA Cronologia
    *
    * @section invCronologia Invariante de la representación
    *
    * El invariante está ligado al de FechaHistorica que ya hemos fijado anteriormente
    *
    * @section faCronologia Función de abstracción
    *
    * Un objeto válido @e rep del TDA Cronologia representa al valor
    *
    * Año_1 a.C/d.C N_eventos evento/s: @n
    * Fecha_Historica_1 @n
    * ... @n
    * Fecha_Historica_N @n
    * ... @n
    * ... @n
    * ... @n
    * Año_N a.C/d.C N_eventos evento/s: @n
    * Fecha_Historica_1 @n
    * ... @n
    * Fecha_Historica_M @n
    *
    */

  VectorDinamico<FechaHistorica> eventos;   /**< VectorDinamico de objetos del TDA FechaHistorica */

  void sort();    /**< Función privada para ordenar los eventos según la fecha */

public:


  /**
    * @brief Constructor por defecto de la clase, necesario para evitar errores. @n
    * Crea un objeto de la clase con el VectorDinamico nulo.
    */

  Cronologia();

      /**
        * @brief Constructor de la clase
        * @param v VectorDinamico del que se copian los datos
        * @return Crea un nuevo objeto con los datos de v
        */

  Cronologia(const VectorDinamico<FechaHistorica>& v);


    /**
      * @brief Constructor de copia de la clase
      * @param c Cronologia de la que se copian los datos
      * @return Crea un nuevo objeto con los datos de c
      */

  Cronologia(const Cronologia& c);

    /**
      * @brief Destructor de la clase
      */

  ~Cronologia();

    /**
      * @brief Método para añadir una FechaHistorica
      * @param f FechaHistorica a añadir
      */

  void add(const FechaHistorica& f);

    /**
      * @brief Método que busca una FechaHistorica dado un año
      * @param yy año que se buscar
      * @param f FechaHistorica donde se guardan los datos
      * @return Devuelve un bool indicando si se ha encontrado una
      *   FechaHistorica con ese año en la cronologia
      * @post En caso de que no se encuentre f no se modifica
      */

  bool find(const int yy, FechaHistorica& f);

    /**
      * @brief Método para buscar eventos dada una palabra clave
      * @param str string con la palabra clave a buscar
      * @param c Cronologia donde guardamos todas las FechasHistoricas de this
      *   con todos los eventos que contienen el string str
      * @return Devuelve un bool indicando si se ha encontrado algún evento con la palabra clave
      * @post En caso de que no se encuentre c no se modifica
      */

  bool find(const std::string str, Cronologia& c);

    /**
      * @brief Salida de una Cronologia a ostream
      * @param os stream de salida
      * @param c Cronologia a escribir
      * @post Se muestra la Cronologia en formato @n
      *   FechaHistorica_1 @n
      *   FechaHistorica_2 @n
      *   ... @n
      *   FechaHistorica_N @n
      */

  friend std::ostream& operator<<(std::ostream& os, const Cronologia& c);


    /**
      * @brief Entrada de una Cronologia desde istream
      * @param is stream de entrada
      * @param c Cronologia que recibe el valor
      * @pre La entrada tiene el formato @n
      *   FechaHistorica_1 @n
      *   FechaHistorica_2 @n
      *   ... @n
      *   FechaHistorica_N @n
      */

  friend std::istream& operator>>(std::istream& is, Cronologia& c);
};

#endif  /* _CRONOLOGIA_ */
