#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <stack>
#include <vector>
#include<list>
using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    operator[]
    * Acceso o definición de pares clave/valor
    **/

    T &operator[](const string &key);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

private:

    struct Nodo {
        Nodo (){
            siguientes = new Nodo*[256];
            int i = 0;
            while(i<255){
                siguientes[i] = NULL;
                i++;
                cantHijos = 0;
            }
            definicion = NULL;

        }
        int cantHijos;
        Nodo** siguientes; //Arreglo de punteros a nodos
        T* definicion;

        ~Nodo() {
            delete[] siguientes;
            if (definicion != NULL) {
               delete definicion;
            }
        }
    };
    list<string> palabras;
    stack<Nodo*> camino;
    Nodo* raiz;
    int _size;
    void borraraux(Nodo* a);

};

#include "string_map.hpp"

#endif // STRING_MAP_H_
