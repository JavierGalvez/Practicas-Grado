#include "lista.h"
#include <cstring>

Lista::Lista(){
	lista = NULL;
}

Lista::~Lista(){
	destruir();
}

void Lista::destruir(){
	Celda * aux = lista;
	while(lista != NULL){
		lista = aux->getSiguiente();
		delete aux;
		aux = lista;
	}
}

void Lista::insertarPrincipio(const Imagen &img){
	Celda * aux = new Celda;
	aux->setImagen(img);
	aux->setSiguiente(lista);
	lista = aux;
}

void Lista::insertarFinal(const Imagen &img){
	if (lista == NULL){
		lista = new Celda;
		lista->setImagen(img);
		lista->setSiguiente(NULL);
	}
	else{
		Celda * aux = lista;
		while(aux->getSiguiente() != NULL){
			aux = aux->getSiguiente();
		}
		Celda * aux2 = new Celda;
		aux2->setImagen(img);
		aux2->setSiguiente(NULL);
		aux->setSiguiente(aux2);
	}
}

int Lista::longitud() const{
	int longitud = 0;
	Celda * aux = lista;
	while (aux->getSiguiente() != NULL){
		longitud++;
		aux = aux->getSiguiente();
	}
	return longitud;
}

Imagen * Lista::get(int pos) const{
	Celda * aux = lista;
	for(int i = 0; i < pos && aux->getSiguiente() != NULL; i++){
		aux = aux->getSiguiente();
	}
	return aux->getImagen();
}
