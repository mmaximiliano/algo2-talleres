#include "Lista.h"
using namespace std;

template <typename T>
Lista<T>::Lista() {
    _primero = NULL;
    _ultimo = NULL;
}

// Inicializa una lista vacía y luego utiliza operator= para no duplicar el
// código de la copia de una lista.
template <typename T>
Lista<T>::Lista(const Lista<T>& l) : Lista() { *this = l; }

template <typename T>
Lista<T>::~Lista() {
    while(_primero != NULL){
        sacarPrimero();
    }
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& l) {

    destruir();
    Lista<T>& nueva = copiar(*this, l);

    return nueva;
}

template <typename T>
void Lista<T>::destruir() {
    while (longitud()>0) {
        eliminar(0);
    }
}

template <typename T>
Lista<T>& Lista<T>::copiar(Lista& r, const Lista<T>& s) {
    int j = 0;
    while (j < s.longitud()){
        r.agregarAtras(s.iesimo(j));
        j++;
    }
}


template <typename T>
void Lista<T>::agregarAdelante(const T& elem) {
    Nodo* nuevo = new Nodo(elem);
    if(_ultimo == nullptr){
        _ultimo = nuevo;
    }
    if (_primero != nullptr){
        _primero -> anterior = nuevo;
    }
    nuevo -> siguiente = _primero;
    nuevo -> anterior = nullptr;
    _primero = nuevo;
}

template <typename T>
void Lista<T>::agregarAtras(const T& elem) {
    Nodo* nuevo = new Nodo(elem);
    if(_primero == nullptr){
        _primero = nuevo;
    }
    if (_ultimo != nullptr){
        _ultimo -> siguiente = nuevo;
    }
    nuevo -> siguiente = nullptr;
    nuevo -> anterior = _ultimo;
    _ultimo = nuevo;
}


template <typename T>
int Lista<T>::longitud() const { // Calculo la longitud igual que en lista simplemente enlazada
    int tam = 0;
    Nodo* p = _primero;
    while (p != NULL){
        tam++;
        p = p -> siguiente;
    }
    return tam;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const { // Calculo el i-esimo igual que en lista simplemente enlazada
    Nodo* p = _primero;
    int actual = 0;
    while (p != NULL && actual < i){
        p = p -> siguiente;
        actual++;
    }
    return p->valor;
}

template <typename T>
void Lista<T>::eliminar(Nat i) {

    // obtenemos el nodo a borrar
    int j = 0;
    Nodo* actual = _primero;

    while(j<i){
        actual = actual -> siguiente;
        j++;
    }

    // Si el nodo a borrar es el primero
    if (_primero == actual) {
        _primero = actual->siguiente;
    }
    // Si el nodo a borrar es el primero
    if (_ultimo == actual) {
        _ultimo = actual->anterior;
    }

    // Cambiamos siguiente solo si el nodo a borrar no es el ultimo
    if (actual->siguiente != NULL) {
        (actual->siguiente)->anterior = actual->anterior;
    }

    // Cambiamos siguiente solo si el nodo a borrar no es el primero
    if (actual->anterior != NULL) {
        (actual->anterior)->siguiente = actual->siguiente;
    }


    // liberamos la memoria
    delete(actual);
}



template <typename T>
T& Lista<T>::iesimo(Nat i) {
    Nodo* p = _primero;
    int actual = 0;
    while (p != NULL && actual < i){
        p = p -> siguiente;
        actual++;
    }
    return p->valor;
}

template <typename T>
void Lista<T>::mostrar(std::ostream& o) {
	// Completar
    Nodo *actual = _primero; //Actual es el primer valor de la lista
    cout << "[";
    while (actual != NULL) //Continuo mientras no llegue al final
    {
        cout << actual->valor << ", "; //Imprimo el valor actual
        actual = actual->siguiente; //Paso al siguiente
    }
    cout << "]";
}

template <typename T>
void Lista<T>::sacarPrimero() {
    Nodo* p = _primero;
    _primero = _primero->siguiente;
    delete p;
}
