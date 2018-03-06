#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <ctype.h>

QuienEsQuien::QuienEsQuien(){}

QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
	*this = quienEsQuien;
}
QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
	personajes = quienEsQuien.personajes;
	atributos = quienEsQuien.atributos;
	tablero = quienEsQuien.tablero;
	arbol = quienEsQuien.arbol;
	jugada_actual = quienEsQuien.jugada_actual;
	return *this;
}
QuienEsQuien::~QuienEsQuien(){
	this->limpiar();
}

void QuienEsQuien::limpiar(){
	personajes.clear();
	atributos.clear();
	tablero.clear();
	arbol.clear();
	//jugada_actual.remove();
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
	cout << "personajes: "<< (this->personajes) << endl;
	cout << "atributos:  "<< (this->atributos)  << endl;
	cout << "tablero:    "<< endl;


	// Escribe la cabecera del tablero
	for(vector<string>::iterator it_atributos = this->atributos.begin();
		it_atributos != this->atributos.end();
		it_atributos++){
		cout << *it_atributos << "\t";
	}
	cout <<endl;

	int indice_personaje = 0;
	for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
		it_tablero_atributos!= tablero.end();
		it_tablero_atributos++){

		string personaje = this->personajes[indice_personaje];
		int indice_atributo = 0;
		for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
			it_atributos_personaje != (*it_tablero_atributos).end();
			it_atributos_personaje++){

			cout << *it_atributos_personaje<<"\t";

			indice_atributo++;
		}

		cout << personaje << endl;

		indice_personaje++;
	}

}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  *
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */
string limpiar_string(string cadena_original,string cadena_a_eliminar){
	string linea(cadena_original);

	while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
		linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
	}

	return linea;
}

istream& operator >> (istream& is, QuienEsQuien &quienEsQuien) {
	quienEsQuien.limpiar();

  	if(is.good()){
  		string linea;
    	getline(is, linea, '\n');

    	linea = limpiar_string(linea,"\r");

    	while(linea.find('\t') != string::npos ){
    		string atributo = linea.substr(0,linea.find('\t'));
			quienEsQuien.atributos.push_back(atributo);
    		linea = linea.erase(0,linea.find('\t')+1);
    	}

		assert(linea ==  "Nombre personaje");
	}

    while( is.good() ) {
    	string linea;
    	getline(is, linea, '\n');
    	linea = limpiar_string(linea,"\r");

    	//Si la linea contiene algo extrae el personaje. Si no lo es, la ignora.
    	if(linea != ""){;
	    	vector<bool> atributos_personaje;

	    	int indice_atributo=0;
	    	while(linea.find('\t') != string::npos){
	    		string valor = linea.substr(0,linea.find('\t'));

	    		assert(valor == "0" || valor == "1");

	    		bool valor_atributo = valor == "1";

	    		atributos_personaje.push_back(valor_atributo);

	    		linea = linea.erase(0,linea.find('\t')+1);
	    		indice_atributo++;
			}

			string nombre_personaje = linea;

	    	quienEsQuien.personajes.push_back(nombre_personaje);
	    	quienEsQuien.tablero.push_back(atributos_personaje);
	    }
  	}

	return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){

	//Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre
	for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
		it_atributos != quienEsQuien.atributos.end();
		it_atributos++){

		os  << *it_atributos << "\t";
	}
	os << "Nombre personaje" << endl;

	//Rellenamos con ceros y unos cada l�nea y al final ponemos el nombre del personaje.
	for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
		for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){

			os  << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
		}
		os  << quienEsQuien.personajes[indice_personaje] << endl;
	}

	return os;
}

/**
  * @brief Convierte un n�mero a un vector de bool que corresponde
  *        con su representaci�n en binario con un numero de digitos
  *        fijo.
  *
  * @param n N�mero a convertir en binario.
  * @param digitos N�mero de d�gitos de la representaci�n binaria.
  *
  * @return Vector de booleanos con la representaci�n en binario de @e n
  *      con el n�mero de elementos especificado por @e digitos.

  */
vector<bool> convertir_a_vector_bool(int n, int digitos) {
  vector<bool> ret;
  while(n) {
    if (n&1){
      ret.push_back(true);
    } else{
      ret.push_back(false);
    }
    n>>=1;
  }

  while(ret.size()<digitos){
  	ret.push_back(false);
  }

  reverse(ret.begin(),ret.end());
  return ret;
}

bintree<Pregunta> QuienEsQuien::crear_arbol(){
	//Vamos a crear un vector que tenga los personajes
	//que todavía no hemos descartado. True es que sigue en la partida
	std::vector<bool> perState(personajes.size(), true);

	//Vector que almacena las preguntas que se han hecho. True se puede preguntar
	std::vector<bool> queState(atributos.size(), true);

	//Arbol de preguntas
	bintree<Pregunta> arbol;

	//Creamos una función recursiva
	crear_recursivo(arbol, perState, queState);

	return arbol;
}

int QuienEsQuien::eligePregunta(std::vector<bool> &que){
	for(int i = 0; i < que.size(); i++){
		if (que[i] == true)
			return i;
	}
}

bool QuienEsQuien::crear_recursivo(bintree<Pregunta> &arbol,
	std::vector<bool> per, std::vector<bool> que){

	//Hacemos recursión mientras tengamos preguntas que hacer
  if(find(que.begin(), que.end(), true) == que.end())
		return true;

  //Se pueden seguir haciendo preguntas

	//Elegimos una pregunta a hacer
  int pregunta = eligePregunta(que);

	//Vectores que almacenan las posiciones de los personajes que verifican
	//y que no verfican la pregunta que se hace
  std::vector<bool> verifican(per.size(), false);
	std::vector<bool> noVerifican(per.size(), false);

	int vivos = 0;

	//Iteramos sobre los presonajes
  for(int i = 0; i < per.size(); i++){
		//Si el personaje sigue en la rama
    if(per[i]){
			//Si el personaje verifica la condición
      if(tablero[i][pregunta] == true)
				verifican[i] = true;
      else
				noVerifican[i] = true;

			vivos ++;
    }
  }

	//Desmarcamos la pregunta como pregunta que se pueda hacer
  que[pregunta] = false;

  //Hay más de un personaje hacemos recursividad
  if(vivos > 1){

		//Creamos un nodo con la pregunta
		Pregunta preguntita(atributos[pregunta], vivos);

		//Hacemos un arbol con esa pregunta
		bintree<Pregunta> arbolico(preguntita);
		arbol = arbolico;

    //La rama de la derecha son los que NO verifican la condición
    bintree<Pregunta> rama_izq;
    //La rama izquierda es la de los personajes que SI verifican
    //la condición
    bintree<Pregunta> rama_dch;

		int enVerifican = count(verifican.begin(), verifican.end(), true);
		int enNoVerfican = count(noVerifican.begin(), noVerifican.end(), true);

		if(enVerifican > 0){
    	crear_recursivo(rama_izq,verifican, que);
			arbol.insert_left(arbol.root(),rama_izq);
		}
		if(enNoVerfican > 0){
			crear_recursivo(rama_dch,noVerifican, que);
			arbol.insert_right(arbol.root(),rama_dch);
		}
  }else{

		//Posicion del ultimo personaje
		int pos = find(verifican.begin(), verifican.end(), true) - verifican.begin();
		if(pos == personajes.size())
			pos = find(noVerifican.begin(), noVerifican.end(), true) - noVerifican.begin();

    Pregunta ultPer(personajes[pos], 1);
    bintree<Pregunta> arb(ultPer);
    arbol = arb;

  } //Hemos llegado al final. Fue bonito mientras duro


}

void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
	arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){
	//Cuando iniciamos el juego lo hacemos con el nodo en la raiz
	jugada_actual = arbol.root();
	char entrada;
	//Jugamos hasta que llegemos a un nodo de tipo personaje
	while((*jugada_actual).es_pregunta()){

		//Probar el información de jugada

		/*set<string> estado = informacion_jugada(jugada_actual);
		for(auto i = estado.begin(); i != estado.end(); i++)
			cout << *i << " ";

		cout << endl;
		*/
		cout << "¿Tu personaje es " << (*jugada_actual).obtener_pregunta() << "? [y/n/i] ";
		cin >> entrada;

		entrada = tolower(entrada);

		if(entrada != 'y' and entrada != 'n' and entrada != 'i' )
			continue;

		if(entrada == 'y')
			jugada_actual = jugada_actual.left();
		else if(entrada == 'i'){
			preguntas_formuladas(jugada_actual);
			cout << "\nPosibles candidatos: " << endl;
			set<string> per = informacion_jugada(jugada_actual);
			for(set<string>::iterator i=per.begin(); i != per.end(); i++)
				cout << *i << " ";
			cout << endl;
		}
		else
			jugada_actual = jugada_actual.right();
	}
	cout << "Tu personaje era " << (*jugada_actual).obtener_personaje() << endl;
}

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){
	set<string> personajes_levantados, right, left;

	//Si tengo una pregunta
	if ((*jugada_actual).es_pregunta()){

		//Llamo a la función por la rama de la derecha
		right = informacion_jugada(jugada_actual.right());

		//Llamo a la función por la rama de la izquierda
		left = informacion_jugada(jugada_actual.left());

		//Insertto los dos conjuntos en el resultante
		personajes_levantados.insert(right.begin(), right.end());
		personajes_levantados.insert(left.begin(), left.end());

	}else
		personajes_levantados.insert((*jugada_actual).obtener_personaje());
		//Cuando llego a un personaje lo inserto en el vector que devuelvo
	return personajes_levantados;
}

void escribir_esquema_arbol(ostream& ss,
					  const bintree<Pregunta>& a,
		    		  bintree<Pregunta>::node n,
					  string& pre){
	if (n.null()){
	    ss << pre << "-- x" << endl;
	} else {
	    ss << pre << "-- " << (*n) << endl;
	    if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
			pre += "   |";
	    	escribir_esquema_arbol(ss,a, n.right(), pre);
	     	pre.replace(pre.size()-4, 4, "    ");
	      	escribir_esquema_arbol (ss,a, n.left(), pre);
	      	pre.erase(pre.size()-4, 4);
	    }
  	}
}

void QuienEsQuien::escribir_arbol_completo() const{
	string pre = "";
	escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}

void QuienEsQuien::eliminar_recursivo(bintree<Pregunta>::node nodo){
	//Estamos estudiando los dos nodos hijos, no el nodo actual

	if(nodo.null())
		return;

	//Estamos en un nodo y comprobamos si alguno de los hijos es nulo
	bintree<Pregunta>::node hijoD = nodo.right();
	bintree<Pregunta>::node hijoI = nodo.left();

	//Vamos a estudiar a los hijos así que en total tenemos 4 nodos
	std::vector<bintree<Pregunta>::node> estudiando {hijoI, hijoD};

	//Para no repetir codigo hacemos un bucle
	for(int i=0; i < 2; i++){
		//Arbol donde guardar lo que recortamos
		bintree<Pregunta> arbolico; // de navidad

		//Comprobamos que el hijo sea una pregunta
		if(!estudiando[i].null() && (*estudiando[i]).obtener_num_personajes() > 1  &&
					(estudiando[i].left().null() || estudiando[i].right().null()) ){

			//recortamos la rama que corresponda
			if(estudiando[i].left().null()){
				arbol.prune_right(estudiando[i], arbolico);
			}
			else if(estudiando[i].right().null()){
				arbol.prune_left(estudiando[i], arbolico);
			}
			//insertamos en el cacho que corresponda
			if (i == 0) {
				arbol.insert_left(nodo, arbolico);
				estudiando[0] = nodo.left();
			} else if(i == 1) {
				arbol.insert_right(nodo, arbolico);
				estudiando[1] = nodo.right();
			}

		}

		//Seguimos con la recursión
		if(!nodo.left().null()){
			if((*nodo.left()).obtener_num_personajes() >=2)
				eliminar_recursivo(nodo.left());
		}

		if(!nodo.right().null()){
			if((*nodo.right()).obtener_num_personajes() >=2)
				eliminar_recursivo(nodo.right());
		}
	}



}

void QuienEsQuien::eliminar_nodos_redundantes(){
	bintree<Pregunta> arbolico; //de navidad
	while(arbol.root().left().null() || arbol.root().right().null()){
		arbolico.clear();
		if (arbol.root().left().null()){
			arbol.prune_right(arbol.root(), arbolico);
		}
		else if(arbol.root().right().null()){
			arbol.prune_left(arbol.root(), arbolico);
		}
		arbol = arbolico;
	}
	eliminar_recursivo(arbol.root());
}

void QuienEsQuien::profundidad_recursivo(bintree<Pregunta>::node nodo,
	int profundidad, int& suma, int& num_ramas){

	if(nodo.null() || (*nodo).es_personaje()){
		//Aumentamos en 1 en lugar de 2 ya que la anterior sigue contando. Es
		//una bifurcación.
		num_ramas++;
		suma += profundidad;
		return;
	}else{
		//Descendemos un nivel
		profundidad++;
		//Evaluamos recursivamente la situación
		profundidad_recursivo(nodo.left(), profundidad, suma, num_ramas);
		profundidad_recursivo(nodo.right(), profundidad, suma, num_ramas);
	}
}

float QuienEsQuien::profundidad_promedio_hojas(){
	float Profundidad = 0;
	int suma = 0;
	int num_ramas = 0;

	profundidad_recursivo(arbol.root(), Profundidad, suma, num_ramas);

	Profundidad = (suma + 0.0) / num_ramas;
	return Profundidad;
}

/**
 * @brief Genera numero enteros positivos aleatorios en el rango [min,max).
**/

int generaEntero(int min, int max){
    int tam= max -min;
    return ((rand()%tam)+min);
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
	srand(0);

	this->limpiar();

	float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);

	int numero_de_atributos = ceil(log_2_numero_de_personajes);

	cout << "Petición para generar "<< numero_de_personajes<<" personajes ";
	cout << "con "<<numero_de_atributos<< " atributos"<<endl;
	cout << "Paso 1: generar "<< pow(2,numero_de_atributos) << " personajes"<<endl;

	//Fase 1: completar el tablero con todos los personajes posibles
	//Completo el tablero y los nombres de personajes a la vez
	for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
		vector<bool> atributos_personaje = convertir_a_vector_bool(indice_personaje,numero_de_atributos);
		string nombre_personaje = "Personaje_"+to_string(indice_personaje);

		this->personajes.push_back(nombre_personaje);
		this->tablero.push_back(atributos_personaje);
	}

	// Completo los nombres de los atributos.
	for(int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
		string nombre_atributo = "Atributo_"+to_string(indice_atributo);
		this->atributos.push_back(nombre_atributo);
	}

	cout << "Paso 2: eliminar "<< (pow(2,numero_de_atributos)-numero_de_personajes) << " personajes"<<endl;
	//Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
	while(personajes.size()>numero_de_personajes){
		int personaje_a_eliminar = generaEntero(0,personajes.size());

		personajes.erase(personajes.begin()+personaje_a_eliminar);
		tablero.erase(tablero.begin()+personaje_a_eliminar);
	}
}

//Metodos adicionales

void QuienEsQuien::preguntas_formuladas(bintree<Pregunta>::node jugada){

	//Para esta parte usaremos un stack. Podríamos usar una lista y recorrerla
	//en dos sentidos pero para esto un stack es la mejor estructura.

	stack<string> preguntas;

	while(jugada != arbol.root()){
		string respuesta = "";
		if(jugada.parent().right() == jugada)
			respuesta = "no";
		else
			respuesta = "sí";
		jugada = jugada.parent();
		preguntas.push((*jugada).obtener_pregunta() + " - " + respuesta);
	}

	cout << "El personaje tiene las siguientes características: " << endl;
	while(!preguntas.empty()){
		cout << preguntas.top() << endl;
		preguntas.pop();
	}
	cout << "pero aún no sé cuál es" << endl;

	//Creamos un stack
	//recorremos hacia arriba el arbol hasta que llegamos a la raiz
	//Introducimos las preguntas en el stack
	//Imprimos el stack

}

bool QuienEsQuien::aniade_personaje(string nombre, vector<bool> caracteristicas){
	// Si ya está el personaje
	if(find(personajes.begin(), personajes.end(), nombre) != personajes.end())
		return 0;

	bintree<Pregunta>::node actual = arbol.root();

	for(int i=0; i<atributos.size(); i++){

		// Vemos si es una pregunta
		if((*actual).es_pregunta()){

			// Sumamos 1 al número de personajes para esa pregunta
			Pregunta aux((*actual).obtener_pregunta(), (*actual).obtener_num_personajes()+1);
			(*actual) = aux;

			if(caracteristicas[i]) 			// Si tiene el atributo
				actual = actual.left();				// Nos movemos a la izquierda
			else 												// No tiene el atributo
				actual = actual.right();			// Nos movemos a la derecha
		}

		// Es un personaje
		else {
			// Obtenemos el nombre y sus caracteristicas
			string persona = (*actual).obtener_personaje();
			int k = find(personajes.begin(), personajes.end(), persona) - personajes.begin();
			vector<bool> carac = tablero[k];

			int j = i;
			// Buscamos la primera caracteristica que los distinga
			bool iguales = true;
			int preg;
			while(j<atributos.size() && iguales){
				if(carac[j] != caracteristicas[j]){
					iguales = false;
					preg = j;
				}
				j++;
			}

			// Mismo personaje con otro nombre
			if(iguales)
				return 0;

			// Añadimos el personaje
			personajes.push_back(nombre);
			tablero.push_back(caracteristicas);

			// Modificamos el arbol
			Pregunta p(atributos[preg], 2);
			Pregunta nuevo(nombre, 1);
			Pregunta estaba(persona, 1);
			(*actual) = p;

			// Izquierda SI derecha NO
			if(caracteristicas[preg]){
				arbol.insert_left(actual, nuevo);
				arbol.insert_right(actual, estaba);
			} else {
				arbol.insert_left(actual, estaba);
				arbol.insert_right(actual, nuevo);
			}
			return 1;
		}
	}
	return 0;
}

bool QuienEsQuien::elimina_personaje(string nombre){
	int k = find(personajes.begin(), personajes.end(), nombre) - personajes.begin();

	// Si no está el personaje
	if(k == personajes.size())
		return 0;

	vector<bool> caracteristicas = tablero[k];

	// Eliminamos el personaje
	personajes.erase(personajes.begin()+k);
	tablero.erase(tablero.begin()+k);

	bintree<Pregunta>::node actual = arbol.root();
	for(int i=0; i<atributos.size(); i++){
		// Vemos si es una pregunta
		if((*actual).es_pregunta()){

			// Restamos 1 al número de personajes para esa pregunta si tiene más 2 personajes
			// Si tiene 2 el siguiente nodo será el que eliminemos
			if((*actual).obtener_num_personajes() > 2){
				Pregunta aux((*actual).obtener_pregunta(), (*actual).obtener_num_personajes()-1);
				(*actual) = aux;
			}

			if(caracteristicas[i]) 			// Si tiene el atributo
				actual = actual.left();				// Nos movemos a la izquierda
			else 												// No tiene el atributo
				actual = actual.right();			// Nos movemos a la derecha
		}

		// Hemos llegado al personaje
		else {
			// Modificamos el árbol
			bintree<Pregunta> aux;
			actual = actual.parent();
			int j = find(atributos.begin(), atributos.end(), (*actual).obtener_pregunta()) - atributos.begin();
			if(caracteristicas[j]) 							// Si tiene el atributo
				(*actual) = (*actual.right());				// Nos quedamos con el hijo de la derecha
			else															 // No tiene el atributo
				(*actual) = (*actual.left());					// Nos quedamos con el hijo de la izquierda

			// Eliminamos los dos hijos
			arbol.prune_left(actual, aux);
			arbol.prune_right(actual, aux);

			return 1;
		}
	}
	return 0;
}

int QuienEsQuien::eligePreguntaOptimizado(std::vector<bool> &que, std::vector<bool> &per){

	int best = eligePregunta(que); //Por defecto la siguiente es la primera que podamos elegir

	int contador = 0;
	float best_ratio = 1; //Ponemos el peor caso
	float ratio;
	int personajes_vivos = count(per.begin(), per.end(), true); //Esto es de alg

	for(int y=best; y < atributos.size(); y++){
		if(que[y]){
			contador = 0;
			for(int x=0; x < per.size(); x++){
				if(tablero[x][y] && per[x])
					contador++;
			}
			ratio = abs(0.5 - ((contador + 0.0) / personajes_vivos));
			if(ratio < best_ratio){
				best_ratio = ratio;
				best = y;
			}
		}
	}
	return best;
}


bool QuienEsQuien::crear_recursivoOptimizado(bintree<Pregunta> &arbol,
	std::vector<bool> per, std::vector<bool> que){

	//Hacemos recursión mientras tengamos preguntas que hacer
  if(find(que.begin(), que.end(), true) == que.end())
		return true;

  //Se pueden seguir haciendo preguntas

	//Elegimos una pregunta a hacer
  int pregunta = eligePreguntaOptimizado(que, per);

	//Vectores que almacenan las posiciones de los personajes que verifican
	//y que no verfican la pregunta que se hace
  std::vector<bool> verifican(per.size(), false);
	std::vector<bool> noVerifican(per.size(), false);

	int vivos = 0;

	//Iteramos sobre los presonajes
  for(int i = 0; i < per.size(); i++){
		//Si el personaje sigue en la rama
    if(per[i]){
			//Si el personaje verifica la condición
      if(tablero[i][pregunta] == true)
				verifican[i] = true;
      else
				noVerifican[i] = true;

			vivos ++;
    }
  }

	//Desmarcamos la pregunta como pregunta que se pueda hacer
  que[pregunta] = false;

  //Hay más de un personaje hacemos recursividad
  if(vivos > 1){

		//Creamos un nodo con la pregunta
		Pregunta preguntita(atributos[pregunta], vivos);

		//Hacemos un arbol con esa pregunta
		bintree<Pregunta> arbolico(preguntita);
		arbol = arbolico;

    //La rama de la derecha son los que NO verifican la condición
    bintree<Pregunta> rama_izq;
    //La rama izquierda es la de los personajes que SI verifican
    //la condición
    bintree<Pregunta> rama_dch;

		int enVerifican = count(verifican.begin(), verifican.end(), true);
		int enNoVerfican = count(noVerifican.begin(), noVerifican.end(), true);

		if(enVerifican > 0){
    	crear_recursivoOptimizado(rama_izq,verifican, que);
			arbol.insert_left(arbol.root(),rama_izq);
		}
		if(enNoVerfican > 0){
			crear_recursivoOptimizado(rama_dch,noVerifican, que);
			arbol.insert_right(arbol.root(),rama_dch);
		}
  }else{

		//Posicion del ultimo personaje
		int pos = find(verifican.begin(), verifican.end(), true) - verifican.begin();
		if(pos == personajes.size())
			pos = find(noVerifican.begin(), noVerifican.end(), true) - noVerifican.begin();

    Pregunta ultPer(personajes[pos], 1);
    bintree<Pregunta> arb(ultPer);
    arbol = arb;

  } //Hemos llegado al final. Fue bonito mientras duro

}

bintree<Pregunta> QuienEsQuien::crear_arbol_Optimizado(){
	arbol.clear();
	//Vamos a crear un vector que tenga los personajes
	//que todavía no hemos descartado. True es que sigue en la partida
	std::vector<bool> perState(personajes.size(), true);

	//Vector que almacena las preguntas que se han hecho. True se puede preguntar
	std::vector<bool> queState(atributos.size(), true);

	//Arbol de preguntas
	bintree<Pregunta> arbol;

	//Creamos una función recursiva
	crear_recursivoOptimizado(arbol, perState, queState);

	return arbol;
}
