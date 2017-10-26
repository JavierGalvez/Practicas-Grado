/**
  * @file FechaHistorica.h
  * @brief Fichero cabecera del TDA FechaHistorica
  *
  */

#ifndef _FECHA_HISTORICA_
#define _FECHA_HISTORICA_

#include "VectorDinamico.h"
#include<iostream>


/**
  *  @brief T.D.A. FechaHistorica
  *
  * Una instancia @e c del tipo de datos abstracto @c FechaHistorica es un objeto
  * con dos campos, un entero y un VectorDinamico
  * El entero es el año en el que ocurrieron los eventos almacenados en el VectorDinamico
  *
  * Un ejemplo de su uso:
  * @include PruebaFecha.cpp
  *
  * @author Javier Gálvez Obispo
  *
  */

class FechaHistorica {
private:


  /**
    * @page repFechaHistoricaRep del TDA FechaHistorica
    *
    * @section invFechaHistorica Invariante de la representación
    *
    * No fijamos ningún límite a los años @n
    * Los años antes de Cristo los tratamos como años negativos
    *
    * @section faFechaHistorica Función de abstracción
    *
    * Un objeto válido @e rep del TDA FechaHistorica representa al valor @n
    * @n
    * Año @n
    * Evento_1 @n
    * ... @n
    * ... @n
    * Evento_N @n
    *
    *
    */

  int aa;    /**< Año */
  VectorDinamico<std::string> eventos;    /**< VectorDinamico de string de Eventos Históricos */

public:

  /**
    * @brief Constructor por defecto de la clase, necesario para evitar errores.
    * Crea un objeto de la clase con año 0 y con el VectorDinamico nulo.
    */

  FechaHistorica();


  /**
    * @brief Constructor de la clase
    * @param yy año de los eventos
    * @param v VectorDinamico con los eventos
    * @return Crea un objeto de la clase con año yy utilizando los eventos de v
    */

  FechaHistorica(const int yy,const VectorDinamico<std::string>& v);


  /**
    * @brief Constructor de copia de la clase
    * @param f FechaHistorica de la cual se copian los datos
    * @return Crea un nuevo objeto con los datos de f
    */

  FechaHistorica(const FechaHistorica &f);

  /**
    * @brief Destructor de la clase
    */

  ~FechaHistorica();

  /**
    * @brief Método para obtener el año de la FechaHistorica
    * @return int con el valor del campo aa
    */

  int getYear();


  /**
    * @brief Método para añadir un evento
    * @param str string con el evento a añadir
    */

  void add(const std::string& str);


  /**
    * @brief Método para buscar eventos dada una palabra clave
    * @param str string con la palabra clave a buscar
    * @param f FechaHistorica donde guardamos todos los eventos de this que contienen el string str
    * @return Devuelve un bool indicando si se ha encontrado algún evento con la palabra clave
    * @post En caso de que no se encuentre f no se modifica
    */

  bool find(const std::string str, FechaHistorica& f);


  /**
    * @brief Operación de asignación
    * @param f FechaHistorica de la cual se copian los datos
    * @return La referencia al elemento
    */

  FechaHistorica& operator=(const FechaHistorica &f);


  /**
    * @brief Salida de una FechaHistorica a ostream
    * @param os stream de salida
    * @param f FechaHistorica a escribir
    * @post Se muestra la FechaHistorica en formato "año#evento1#evento2#...#eventoN"
    */

  friend std::ostream& operator<<(std::ostream& os, const FechaHistorica& f);


  /**
    * @brief Entrada de una FechaHistorica desde istream
    * @param is stream de entrada
    * @param f FechaHistorica que recibe el valor
    * @pre La entrada tiene el formato "año#evento1#evento2#...#eventoN"
    */

  friend std::istream& operator>>(std::istream& is, FechaHistorica& f);
};

#endif  /* _FECHA_HISTORICA_ */
