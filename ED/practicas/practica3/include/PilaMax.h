/**
  * @file PilaMax.h
  * @brief Fichero cabecera para elegir que mstack (PilaMax) utilizar
  *
  */

#define CUAL_COMPILA 2
#if CUAL_COMPILA==1
#include  <PilaMaxVD.h>
#else
#include <PilaMaxCola.h>
#endif
