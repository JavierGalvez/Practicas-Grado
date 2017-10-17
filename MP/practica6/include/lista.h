/**
   @file lista.h
   @brief Secuencias de imágenes como listas de celdas enlazadas
   @author MP-DGIM - Grupo A

**/
#ifndef __LISTA_H
#define __LISTA_H
#include "imagen.h"

/** @brief Cada celda contiene una imagen */
class Celda {
private:
	Imagen *img; /// Contenedor para la imagen
	Celda * sig; /// Puntero a la siguiente celda (se usará dentro de la Lista)
public:
	/** @brief Constructor de la clase */
	Celda();
	/** @brief Destructor de la clase */
	~Celda();
	/** @brief Inserta UNA COPIA de la imagen que se pasa por parámetro en la celda (usar operador = sobrecargado)
		 @param img La imagen cuya copia se pretende insertar  	 */	
	void setImagen(const Imagen &img);
	/** @brief Devuelve un puntero a la imagen contenida en la celda
		 @return La dirección de memoria de la imagen contenida 	 */	
	Imagen * getImagen() const;
	/** @brief Actualiza el puntero a la siguiente celda con el puntero que recibe como argumento
		 @param next Puntero a la siguiente celda 	 */	
	void setSiguiente(Celda *next);
	/** @brief Devuelve el puntero a la siguiente celda
		 @return Puntero a la siguiente celda 	 */	
	Celda * getSiguiente() const;
	
};

/** @brief Una lista enlazada de celdas según los apuntes de teoría */
class Lista {
private:
	Celda *lista;
public:
	/** @brief Constructor de la clase */
	Lista();
	/** @brief Destructor de la clase */
	~Lista();
	/** @brief Libera toda la lista */
	void destruir();
	/** @brief Inserta UNA COPIA de la imagen en la primera posición de la lista, desplazando el resto, si lo hubiese.
		 @param img La imagen cuya copia se pretende insertar  	 */	
	void insertarPrincipio(const Imagen &img);
	/** @brief Inserta UNA COPIA de la imagen en la última posición de la lista.
		 @param img La imagen cuya copia se pretende insertar  	 */	
	void insertarFinal(const Imagen &img);
	/** @brief Devuelve la longitud de la lista
		 @return El número de celdas válidas que contiene la lista 	 */	
	int longitud() const;
	/** @brief Consulta una celda de la lista
		 @param pos Posición ordinal de la celda que se quiere consultar
		 @return La dirección de memoria de la Imagen en la celda que ocupa la posición @a pos dentro de la lista. Si @a pos es mayor o igual que la longitud de la lista, entonces devuelve 0 	 */	
	Imagen * get(int pos) const;
};
#endif
