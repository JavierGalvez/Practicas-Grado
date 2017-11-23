/**
  * @file FechaHistorica.h
  * @brief Fichero cabecera del TDA FechaHistorica
  *
  */

#ifndef __FECHA_HISTORICA__
#define __FECHA_HISTORICA__

#include <iostream>
#include <set>


/**
  *  @brief T.D.A. FechaHistorica
  *
  * Una instancia @e c del tipo de datos abstracto @c FechaHistorica es un objeto
  * con un campo, un pair con pair::first un entero y pair::second un set<std::string>
  * El entero es el año en el que ocurrieron los eventos almacenados en el set<std::string>
  *
  * Un ejemplo de su uso:
  * @include PruebaFecha.cpp
  *
  * @author Javier Gálvez Obispo
  *
  */

class FechaHistorica{
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

    std::pair<int, std::set<std::string> > datos;   /**< pair que almacena el año y los eventos */

  public:


    /**
      * @brief Iterador de la clase
      */

    typedef std::set<std::string>::iterator iterator;


    /**
      * @brief Iterador constante de la clase
      */

    typedef std::set<std::string>::const_iterator const_iterator;


    /**
      * @brief Constructor por defecto de la clase, crea una FechaHistorica sin eventos
      * @param year año de la FechaHistorica, si no se especifica ninguno el año será 0
      */

    FechaHistorica(int year=0);


    /**
      * @brief Constructor de la clase
      * @param year año de la FechaHistorica
      * @param s set<std::string> con los eventos
      * @return Crea un objeto de la clase con año year utilizando los eventos de s
      */

    FechaHistorica(const int year, const std::set<std::string>& s);


    /**
      * @brief Constructor de la clase
      * @param p pair con pair::first año de la FechaHistorica y pair::second set<std::string> con los eventos
      * @return Crea un objeto de la clase con año pair::first utilizando los eventos de pair::second
      */

    FechaHistorica(const std::pair<int,std::set<std::string> >& p);


    /**
      * @brief Constructor de copia de la clase
      * @param f FechaHistorica de la cual se copian los datos
      * @return Crea un nuevo objeto con los datos de f
      */

    FechaHistorica(const FechaHistorica& f);


    /**
      * @brief Destructor de la clase
      */

    ~FechaHistorica();


    /**
      * @brief Método para obtener el año de la FechaHistorica
      * @return int con el valor del campo aa
      */

    int year() const;


    /**
      * @brief Método para añadir un evento
      * @param str evento a añadir
      * @return pair siendo pair::first un iterador que apunta al evento introducido
      *   o al evento con la misma etiqueta que ya estaba en la FechaHistorica. Y pair::second
      *   un bool que indica si se ha introducido el nuevo evento o no.
      */

    std::pair<iterator,bool> insert(const std::string& str);


    /**
      * @brief Método que elimina un evento de la FechaHistorica
      * @param str evento que se quiere borrar
      */

    void erase(std::string& str);


    /**
      * @brief Método que elimina todos los eventos de la FechaHistorica
      */

    void clear();


    /**
      * @brief Método para buscar eventos dada una palabra clave
      * @param str string con la palabra clave a buscar
      * @return pair siendo pair::first una nueva FechaHistorica con los eventos que
      *   contienen la palabra clave. Y pair::second un bool que indica si se ha
      *   encontrado al menos un evento con esa clave.
      */

    std::pair<FechaHistorica,bool> find(const std::string& str) const;


    /**
      * @brief Método que devuelve el número de eventos en la FechaHistorica
      */

    int size() const;


    /**
      * @brief Operación de asignación
      * @param f FechaHistorica de la cual se copian los datos
      * @return La referencia al elemento
      */

    FechaHistorica& operator=(const FechaHistorica& f);


    /**
      * @brief Operador de suma, utilizado para la unión de FechasHistoricas
      * @param f FechaHistorica con la que se hace la unión
      * @return Referencia a this
      * @pre Las FechasHistoricas deben ser del mismo año
      */

    FechaHistorica& operator+(const FechaHistorica& f);


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


    /**
      * @brief Método que devuelve un iterator al primer elemento
      * @return Devuelve un iterator al primer elemento
      */

    iterator begin(){
      return datos.second.begin();
    }


    /**
      * @brief Método que devuelve un const_iterator al primer elemento
      * @return Devuelve un const_iterator al primer elemento
      */

    const_iterator begin() const{
      return datos.second.begin();
    }


    /**
      * @brief Método que devuelve un iterator al último elemento
      * @return Devuelve un iterator al último elemento
      */

    iterator end(){
      return datos.second.end();
    }


    /**
      * @brief Método que devuelve un const_iterator al último elemento
      * @return Devuelve un const_iterator al último elemento
      */

    const_iterator end() const{
      return datos.second.end();
    }
};

#endif
