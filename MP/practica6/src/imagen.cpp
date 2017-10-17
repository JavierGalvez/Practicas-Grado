#include "byte.h"
#include "imagen.h"
#include "pgm.h"
#include <cstring>

Imagen::Imagen(){
  //inicializar todo a 0.
  datos = NULL;
  nfilas = 0;
  ncolumnas = 0;
}

Imagen::Imagen(int filas, int columnas):Imagen(){
  crear(filas,columnas);
}
/*
=====================
	Copia
=====================
*/
Imagen::Imagen(const Imagen &im){
	nfilas = im.filas();
	ncolumnas = im.columnas();
	datos = new Byte * [nfilas];
	datos[0] = new Byte [nfilas*ncolumnas];
	for(int i=0; i < nfilas*ncolumnas; i++){
		setPos(i,im.getPos(i));
	}
}

void Imagen::crear(int filas, int columnas){
  destruir();
  //Comprobamos que el tamaño sea válidos
  if (filas*columnas >= 1){
	nfilas = filas;
    ncolumnas = columnas;
    datos = new Byte * [nfilas];
	datos[0] = new Byte [nfilas*ncolumnas];
    for(int i=1; i<nfilas; ++i){
      datos[i] = datos[i-1]+ncolumnas;
    }
  }
}
/*
=====================
	Destructor
=====================
*/
Imagen::~Imagen(){
  destruir();
}
void Imagen::destruir(){
  //Si hay algo en datos
  if(datos != NULL){
    delete[] datos[0];
    delete[] datos;
    datos = NULL;
  }
  nfilas = 0;
  ncolumnas = 0;
}
/*
=====================
	Asignación
=====================
*/
void Imagen::operator= (const Imagen &im){
	destruir();
	nfilas = im.filas();
	ncolumnas = im.columnas();
	datos = new Byte * [nfilas];
	datos[0] = new Byte [nfilas*ncolumnas];
	for(int i=1; i < nfilas; i++){
		datos[i] = datos[i-1] + ncolumnas;
	}
	for(int i=0; i < nfilas*ncolumnas; i++){
		setPos(i,im.getPos(i));
	}
}

int Imagen::filas() const{
  return nfilas;
}

int Imagen::columnas() const{
  return ncolumnas;
}

void Imagen::set(int y, int x, Byte v){
	if(y*x >= 0){
		datos[y][x] = v;
	}
}

Byte Imagen::get(int y, int x) const{
  Byte byte = 0x0;
  if(y*x >= 0){
  	byte = datos[y][x];
  }
  return byte;
}

void Imagen::setPos(int i, Byte v){
	if(i < nfilas*ncolumnas){
		int x = i / ncolumnas;
		int y = i % ncolumnas;
		datos[x][y] = v;
	}
	
}

Byte Imagen::getPos(int i) const{
	Byte byte = 0x0;
	if(i < nfilas*ncolumnas){
		int x = i / ncolumnas;
		int y = i % ncolumnas;
		byte = datos[x][y];
	}
	return byte;
}

bool Imagen::leerImagen(const char nombreFichero[]){
  bool exito = false;
  // Comprobamos que sea PGM BINARIO
  if(infoPGM(nombreFichero, nfilas, ncolumnas) == IMG_PGM_BINARIO){
    // Comprobamos que no supere el tamaño máximo
    crear(nfilas, ncolumnas);
    exito = leerPGMBinario(nombreFichero, datos[0], nfilas, ncolumnas);
  }
  else if (infoPGM(nombreFichero, nfilas, ncolumnas) == IMG_PGM_TEXTO){
    crear(nfilas, ncolumnas);
    exito =  leerPGMTexto1(nombreFichero, datos[0], nfilas, ncolumnas);
  }
  return exito;
}

bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario) const{
  bool exito = false;
  if(esBinario){
    exito = escribirPGMBinario(nombreFichero, datos[0], nfilas, ncolumnas);
  }
  else{
    exito = escribirPGMTexto(nombreFichero, datos[0], nfilas, ncolumnas);
  }
  return exito;
}


Imagen Imagen::plano (int k) const{
  //Usamos un puntero ya que cuando usamos el constructor copia,
  //no podemos dejar huérfano el objeto sin borrarlo.
  Imagen nueva(filas(),columnas());

  if (k < 7 && k >= 0){
    for (int i = 0; i < columnas(); i++){
      for(int j = 0; j < filas(); j++){
        //Cojo cada byte de la imagen
        Byte byte = this->get(j,i);
        //Creo un byte con todo 0s
        Byte nuevo = 0x0;
        //Miro si la posición k del byte de la imagen está encendida
        bool estado = getBit(byte,k);
        //Coloco el bit más significativo a 1 si está encencido
        if (estado)
          onByte(nuevo);
        //Asigno el nuevo byte a la posición i,j de la imágen
        nueva.set(j,i, nuevo);
      }
    }
  }
  //Devuelvo un puntero a la imágen.
  return nueva;

}


bool Imagen::aArteASCII(const char grises[], char arteASCII[], int maxlong) const{
  bool tamanio_correcto = false;

  if (filas()*(columnas()+1) < maxlong){
    tamanio_correcto = true;
    int introducidos = 0;

    for (int i = 0; i < filas() && introducidos < maxlong; i++){
      for(int j = 0; j < columnas() && introducidos < maxlong; j++){
        //Cojo cada byte de la imagen
        Byte byte = this->get(i,j);
        //Compruebo que símbolo le corresponde
        char simbolo = grises[byte*strlen(grises)/256];
        arteASCII[i*columnas() + j] = simbolo;
        introducidos += 1;
      }
      //añado el salto de carro al final de cada línea
      arteASCII[i*columnas()] = '\n';
      introducidos += 1;
    }

    //Agrego al final de la cadena el salto de línea y el caracter
    arteASCII[(filas()-1)*columnas()+columnas()] = '\n';
    arteASCII[(filas()-1)*columnas()+columnas()+1] = '\0';
  }

  return tamanio_correcto;
}
