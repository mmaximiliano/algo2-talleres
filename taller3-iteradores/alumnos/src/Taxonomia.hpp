#include <sstream>
#include "Taxonomia.h"
// Métodos de Taxonomia (ya implementados por la cátedra):

template<class T>
int Taxonomia<T>::_espiarProximoCaracter(istream& is) const {
	int c = is.peek();
	while (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
		is.get();
		c = is.peek();
	}
	return is.peek();
}

template<class T>
typename Taxonomia<T>::Nodo* Taxonomia<T>::_leerDe(istream& is) {
	Taxonomia<T>::Nodo* nodo = new Taxonomia<T>::Nodo();
	is >> nodo->valor;
	if (_espiarProximoCaracter(is) == '{') {
		is.get();
		while (_espiarProximoCaracter(is) != '}') {
			nodo->hijos.push_back(_leerDe(is));
		}
		is.get();
	}
	return nodo;
}

template<class T>
Taxonomia<T>::Taxonomia(const string& input) {
	istringstream is(input);
	_raiz = _leerDe(is);
}

template<class T>
void Taxonomia<T>::_borrar(Taxonomia<T>::Nodo* nodo) {
	for (int i = 0; i < nodo->hijos.size(); i++) {
		_borrar(nodo->hijos[i]);
	}
	delete nodo;
}

template<class T>
Taxonomia<T>::~Taxonomia() {
	_borrar(_raiz);
}

template<class T>
void Taxonomia<T>::_identar(ostream& os, int tab) const {
	for (int i = 0; i < tab; i++) {
		os << "  ";
	}
}

template<class T>
void Taxonomia<T>::_mostrarEn(
		ostream& os, Taxonomia<T>::Nodo* nodo, int tab) const {
	_identar(os, tab);
	os << nodo->valor;
	if (nodo->hijos.size() == 0) {
		os << "\n";
	} else {
		os << " {\n";
		for (int i = 0; i < nodo->hijos.size(); i++) {
			_mostrarEn(os, nodo->hijos[i], tab + 1);
		}
		_identar(os, tab);
		os << "}\n";
	}
}

template<class T>
void Taxonomia<T>::mostrar(ostream& os) const {
	_mostrarEn(os, _raiz, 0);
}

////////////////////////////////////////

// Métodos para implementar el iterador de Taxonomia<T> (para completar)

// Devuelve un iterador válido al principio de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::begin() {
	return iterator(_raiz);
}

// Devuelve un iterador válido al final de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::end() {
	iterator s = iterator(NULL);
	return s;
}

// Constructor por defecto del iterador.
// (Nota: puede construir un iterador inválido).
template<class T>
Taxonomia<T>::iterator::iterator() {
	actual = NULL;
}

// Referencia mutable al nombre de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
T& Taxonomia<T>::iterator::operator*() const {
	return actual->valor;
}

// Cantidad de subcategorías de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
int Taxonomia<T>::iterator::cantSubcategorias() const {
	return actual->hijos.size();
}

// Ubica el iterador sobre la i-ésima subcategoría.
// Pre: el iterador está posicionado sobre una categoría
// y además 0 <= i < cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::subcategoria(int i) {
	upperCategory.push(actual);
	actual = actual->hijos[i];
}

// Devuelve true sii la categoría actual es la raíz. 
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
bool Taxonomia<T>::iterator::esRaiz() const {
	return upperCategory.empty();
}

// Ubica el iterador sobre la supercategoría de la categoría
// actual.
// Pre: el iterador está posicionado sobre una categoría
// y además !esRaiz()
template<class T>
void Taxonomia<T>::iterator::supercategoria() {
    if(!upperCategory.empty()) {
        Nodo *exActual = actual;
        actual = upperCategory.top();
        upperCategory.pop();
    }
}

// Compara dos iteradores por igualdad.
// Pre: deben ser dos iteradores de la misma taxonomía.
template<class T>
bool Taxonomia<T>::iterator::operator==(
		const Taxonomia<T>::iterator& otro) const {
	return (actual == otro.actual);
}

// Ubica el iterador sobre la categoría siguiente a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la última categoría de la taxonomía,
// el iterador resultante debe ser igual al iterador end()
// de la taxonomía.
template<class T>
void Taxonomia<T>::iterator::operator++() {
	if (actual != lastNodo(raiz())) {
		if (actual->hijos.size() != 0) {
			subcategoria(0);
		} else if (actual->hijos.size() == 0) {
			int j = incrementar();
			while (j == actual->hijos.size() - 1) {
				j = incrementar();
			}

			subcategoria(j + 1);
		} else {

		}
	}
	else{
		actual = NULL;
	}
}
template<class T>
int Taxonomia<T>::iterator::incrementar(){
	Nodo *exActual = actual;
	supercategoria();
	int i = 0;
	while (actual->hijos[i] != exActual) {
		i++;
	}
	return i;
}

// Ubica el iterador sobre la categoría anterior a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la raíz de la taxonomía el iterador
// resultante debe ser igual al iterador end() de la taxonomía.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
void Taxonomia<T>::iterator::operator--() {
	if(!esRaiz()) {
		Nodo *exActual = actual;
		supercategoria();
		int i = 0;
		while (actual->hijos[i] != exActual) {
			i++;
		}
		if(i-1>= 0){
			subcategoria(i-1);
			while(actual->hijos.size() > 0){
				subcategoria(actual->hijos.size() -1);
			}
		} else {
		//No hago nada
		}
	} else {
		actual = NULL;
	} //Falta hacer cuando soy raiz.
}

// Inserta una subcategoría con el nombre indicado
// en el lugar i-ésimo.
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores.
// Pre: el iterador está posicionado sobre una categoría,
// y además 0 <= i <= cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::insertarSubcategoria(int i, const T& nombre) {
	Taxonomia<T>::Nodo* nuevo = new Taxonomia<T>::Nodo();
	nuevo->valor = nombre;
	actual->hijos.push_back(nuevo);
	actual->hijos[actual->hijos.size()-1] = actual->hijos[i];
	actual->hijos[i] = nuevo;
}

// Elimina la categoría actual de la taxonomía
// (y todas sus subcategorías).
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores. Debe encargarse de
// liberar la memoria.
// Pre: el iterador está posicionado sobre una categoría,
// y además !esRaiz().
template<class T>
void Taxonomia<T>::iterator::eliminarCategoria() {
	if(actual->hijos.size() == 0){
		Nodo* it = actual;
		supercategoria();
		int i = 0;
		vector<Nodo*> nuevosHijos;
		while(i<actual->hijos.size()){
			if(actual->hijos[i] != it){
				nuevosHijos.push_back(actual->hijos[i]);
			}
            i++;
		}
		actual->hijos = nuevosHijos;
		delete it;
	} else {
        Nodo* it = actual;
		while(it->hijos.size()>0){
            while(actual->hijos.size() > 0) {
                subcategoria(actual->hijos.size() - 1);
            }
            eliminarCategoria();
		}
        eliminarCategoria();
	}
}

template<class T>
typename Taxonomia<T>::Nodo* Taxonomia<T>::iterator::lastNodo(Nodo *r) { //Cómo hago esto?
	Nodo* s = r;
	while(s->hijos.size() > 0){
		s = s->hijos[s->hijos.size() -1];
	}
	return s;
}

template<class T>
typename Taxonomia<T>::Nodo* Taxonomia<T>::iterator::raiz() {
	Nodo* first = NULL;
	if(!upperCategory.empty()){
		stack<Nodo*> nueva = upperCategory;
		while (nueva.size() > 1) {
			nueva.pop();
		}
		first = nueva.top();
	} else {
		first = actual;
	}
	return first;
}