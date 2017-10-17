/**
   @file byte.h
   @brief Operaciones a nivel de bit
   @author MP-DGIM - Grupo A

**/

#ifndef _BYTE_H_
#define	_BYTE_H_


typedef unsigned char Byte; ///< Un @c Byte contiene el estado de 8 Bits

/**
@brief enciende el Bit @p pos del @c Byte @p b
@param b 	el @c Byte cuyo Bit se quiere activar
@param pos 	el Bit dentro de @p b que se quiere activar (0 más a la derecha)
*/
void onBit(Byte &b, int pos);

/**
@brief apaga el Bit @p pos del  @c Byte @p b
@param b 	el @c Byte cuyo Bit se quiere desactivar
@param pos 	el Bit dentro de @p b que se quiere desactivar (0 más a la derecha)
*/
void offBit(Byte &b, int pos);

/**
@brief devuelve el estado del Bit (encendido = true, apagado = false) en la posición @p pos
@param b 	el @c Byte que se quiere consultar
@param pos 	el Bit dentro de @ b que se quiere consultar (0 más a la derecha)
@retval true 	si el Bit en la posición @p pos está encendido
@retval false	si el Bit en la posición @p pos está apagado
*/
bool getBit(Byte b, int pos);


/**
@brief devuelve un string conteniendo una secuencia de '0's y '1's correspondiente  al estado de cada Bit
@param b el @c Byte que se quiere imprimir

Por ejemplo, si en el @c Byte @c b están encendidos los Bits en posiciones 1 y 3 (0 más a la derecha), @c ByteToString(b); devolverá el string @c "00001010"

*/

void imprimirByte(Byte b);

/**
@brief enciende todos los Bits
@param b el @c Byte que se quiere encender completamente.
*/
void onByte(Byte &b);

/**
@brief apaga todos los Bits
@param b el @c Byte que se quiere apagar completamente.
*/
void offByte(Byte &b);

/**
@brief enciende los Bits según la configuración de @p v
@param b el @c Byte sobre el que se quiere actuar
@param v vector de 8 elementos que contiene la secuencia de BitS que se quieren asignar

Asigna a @p b la configuración de Bits contenida en @p v. @p v es un vector de 8 booleanos donde @c true significa encendido y @c false significa apagado.
*/
void asignarByte(Byte &b, const bool v[]);

/**
@brief recupera la configuración de todos los Bit
@param b el @c Byte que se quiere consultar
@param v vector de 8 elementos que contendrá el estado de cada uno de los Bits de @ b

Vuelca en @p v la configuración de Bits contenida en @p b. @c true significa encendido y @c false significa apagado. El tamaño de @p v debe ser 8.
*/
void volcarByte(Byte b, bool v[]);

/**
@brief devuelve las posiciones de los Bits encendidos
@param b el @c Byte que se quiere consultar
@param posic vector de enteros (valores entre 0 a 7) que indican la posición de los Bits de @p b que están encendidos
@param cuantos número de Bits encendidos en @p b (número de elementos usados en el vector @p posic)
*/
void encendidosByte(Byte b, int posic[], int &cuantos);

#endif

