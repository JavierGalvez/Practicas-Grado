/**
  * @file Cronologia.h
  * @brief Fichero cabecera del TDA Cronologia
  *
  */


#ifndef __CRONOLOGIA__
#define __CRONOLOGIA__

#include <iostream>
#include <map>
#include "FechaHistorica.h"


/**
  *  @brief T.D.A. Cronologia
  *
  * Una instancia @e c del tipo de datos abstracto @c Cronologia es un objeto
  * con un campo, un map que almacena objetos del T.D.A. FechaHistorica
  *
  * Un ejemplo de su uso puede verse en PruebaCronologia.cpp:
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

    std::map<int,FechaHistorica> datos;   /**< map de objetos del TDA FechaHistorica y el año de cada FechaHistorica */

  public:


    /**
      * @brief Iterador de la clase
      */

    typedef std::map<int,FechaHistorica>::iterator iterator;


    /**
      * @brief Iterador constante de la clase
      */

    typedef std::map<int,FechaHistorica>::const_iterator const_iterator;


    /**
      * @brief Constructor por defecto de la clase
      */

    Cronologia();


    /**
      * @brief Constructor de la clase
      * @param m map<int,FechaHistorica> del que se copian los datos
      * @return Crea un nuevo objeto con los datos de m
      */

    Cronologia(const std::map<int,FechaHistorica>& m);


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
      * @return pair siendo pair::first un iterador que apunta a la FechaHistorica introducida
      *   o a la FechaHistorica con el mismo año que ya estaba en la Cronologia. Y pair::second
      *   un bool que indica si se ha introducido la nueva FechaHistorica o no.
      */

    std::pair<iterator,bool> insert(const FechaHistorica& f);


    /**
      * @brief Método que elimina una FechaHistorica de la Cronologia
      * @param year Año de la FechaHistorica que se quiere borrar
      */

    void erase(const int year);


    /**
      * @brief Método que vacía la Cronologia
      */

    void clear();


    /**
      * @brief Método que busca una FechaHistorica dado un año
      * @param year año a buscar
      * @return Cronologia::iterator a la FechaHistorica
      * @post En caso de que no se encuentre el año devuelve un Cronologia::iterator a Cronologia::end()
      */

    iterator find(const int year);


    /**
      * @brief Método para buscar eventos dada una palabra clave
      * @param str string con la palabra clave a buscar
      * @return pair siendo pair::first una nueva Cronologia con las FechasHistoricas que
      *   contienen eventos en los que se encuentra la palabra clave. Y pair::second un bool
      *   que indica si se ha encontrado al menos un evento con esa clave.

      * Un ejemplo de su uso puede verse en PruebaFiltrado.cpp:
      * @include PruebaFiltrado.cpp
      */

    std::pair<Cronologia,bool> find(const std::string& str);


    /**
      * @brief Método que devuelve el número de FechasHistoricas en la Cronologia
      */

    int size() const;


    /**
      * @brief Método que crea una Cronologia nueva con las
      *   FechasHistoricas que se encuentra en un rango
      * @param inf extremo izquierdo del intervalo
      * @param sup extremo derecho del intervalo
      * @return Devuelve una nueva Cronologia con una copia de las
      *   FechasHistoricas que se encuentra entre inf y sup
      *
      * Un ejemplo de su uso puede verse en PruebaIntervalo.cpp:
      * @include PruebaIntervalo.cpp
      */

    Cronologia interval(const int inf, const int sup);


    /**
      * @brief Método que devuelve el número de eventos en la Cronologia
      */

    int totalEvents();


    /**
      * @brief Método que devuelve el mayor número de eventos
      *   registrados en un año
      */

    int maxEvents();


    /**
      * @brief Método que devuelve la media de eventos por año
      */

    double averageEvents();


    /**
       * @brief Acceso a una FechaHistorica de la Cronologia
       * @param year indica el año de la FechaHistorica a la que se quiere acceder
       * @return La referencia a dicha FechaHistorica
       * @pre Debe existir una FechaHistorica con ese año o una excepcion out_of_range será lanzada
       */

    FechaHistorica& at(const int year);


    /**
       * @brief Acceso constante a una FechaHistorica de la Cronologia
       * @param year indica el año de la FechaHistorica a la que se quiere acceder
       * @return La referencia constante a dicha FechaHistorica
       * @pre Debe existir una FechaHistorica con ese año o una excepcion out_of_range será lanzada
       */

    const FechaHistorica& at(const int year) const;


    /**
       * @brief Acceso a una FechaHistorica de la Cronologia
       * @param year indica el año de la FechaHistorica a la que se quiere acceder
       * @return La referencia a dicha FechaHistorica
       * @pre Debe existir una FechaHistorica con ese año o una excepcion out_of_range será lanzada
       */

    FechaHistorica& operator[](const int year);


    /**
       * @brief Acceso constante a una FechaHistorica de la Cronologia
       * @param year indica el año de la FechaHistorica a la que se quiere acceder
       * @return La referencia constante a dicha FechaHistorica
       * @pre Debe existir una FechaHistorica con ese año o una excepcion out_of_range será lanzada
       */

    const FechaHistorica& operator[](const int year) const;


    /**
      * @brief Operador de asignación
      * @param c Cronologia de la que se copian los datos
      * @return Referencia a this
      */

    Cronologia& operator=(const Cronologia& c);


    /**
      * @brief Operador de suma, utilizado para la unión de Cronologias
      * @param c Cronologia con la que se hace la unión
      * @return Referencia a this
      *
      * Un ejemplo de su uso puede verse en PruebaUnion.cpp:
      * @include PruebaUnion.cpp
      */

    Cronologia& operator+(const Cronologia& c);


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


    /**
      * @brief Método que devuelve un iterator al primer elemento
      * @return Devuelve un iterator al primer elemento
      */

    iterator begin(){
      return datos.begin();
    }


    /**
      * @brief Método que devuelve un const_iterator al primer elemento
      * @return Devuelve un const_iterator al primer elemento
      */

    const_iterator begin() const{
      return datos.begin();
    }


    /**
      * @brief Método que devuelve un iterator al último elemento
      * @return Devuelve un iterator al último elemento
      */

    iterator end(){
      return datos.end();
    }


    /**
      * @brief Método que devuelve un const_iterator al último elemento
      * @return Devuelve un const_iterator al último elemento
      */

    const_iterator end() const{
      return datos.end();
    }
};

#endif
