template <typename T>
string_map<T>::string_map(){
    raiz = NULL;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    borraraux(raiz);
    raiz = NULL;
    _size = 0;
    auto iter = d.palabras.begin();
    while(iter!= d.palabras.end()){
        (*this)[*iter] = d.at(*iter);
        ++iter;
    }
}

template <typename T>
string_map<T>::~string_map(){
    borraraux(raiz);
    raiz = NULL;
    _size = 0;
}

template <typename T>
void string_map<T>::borraraux(Nodo *a) {
    if (a != NULL) {
        int i = 0;
        while (i < 255) {
            if (a->siguientes[i] != NULL) {
                borraraux(a->siguientes[i]);
            }
            i++;
        }
/*
        auto it = palabras.begin();
        while (it != palabras.end()) {
            it = palabras.erase(it);
            ++it;
        }
*/

        delete a;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){

    if(empty()){
        Nodo* nuevo = new Nodo();
        raiz = nuevo;
    }


    int i = 0;
    Nodo* it = raiz;
    if(count(clave) == 1){
        while(i<clave.size()){
            it = it->siguientes[int(clave[i])];
            i++;
        }
        return *(it->definicion);
    } else {
        _size++;
        while(i<clave.size() && it->siguientes[int(clave[i])] != NULL){
            it = it->siguientes[int(clave[i])];
            i++;
        }

        while(i<clave.size()){
            palabras.push_back(clave);
            Nodo* nuevo2 = new Nodo();
            it->siguientes[int(clave[i])] = nuevo2;
            it->cantHijos++;
            it = it->siguientes[int(clave[i])];
            i++;
        }
        if (it->definicion == NULL) {
            it->definicion = new T();
        }
        return *(it->definicion);
    }
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if(empty()){
        return 0;
    }else {
        int res = 0;
        Nodo *it = raiz;
        int i = 0;
        while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {
            it = it->siguientes[int(clave[i])];
            i++;
        }
        if (i < clave.size()) {

        } else {
            if (it->definicion != NULL) {
                res = 1;
            }
        }
        return res;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo *it = raiz;
    int i = 0;
    while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {
        it = it->siguientes[int(clave[i])];
        i++;
    }
    T& res = *it->definicion;
    return res;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo *it = raiz;
    int i = 0;
    while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {
        it = it->siguientes[int(clave[i])];
        i++;
    }
    T& res = *it->definicion;
    return res;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    if(_size == 1){
        Nodo *it = raiz;
        int i = 0;
        while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {
            camino.emplace(it);
            it = it->siguientes[int(clave[i])];
            i++;
        }
        Nodo* aBorrar = it;
        delete aBorrar;
        it = camino.top();
        it->cantHijos--;
        int j = clave.size() - 1;
        while(it->cantHijos==0 && it->definicion== NULL && j >0){
            Nodo* borrar = it;
            borrar->siguientes[int(clave[j])] = NULL;
            camino.pop();
            delete borrar;
            it = camino.top();
            it->cantHijos--;
            j--;
        }
        it->siguientes[int(clave[j])] = NULL;
        delete raiz;
        raiz = NULL;
    } else {
        Nodo *it = raiz;
        int i = 0;
        while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {
            camino.emplace(it);
            it = it->siguientes[int(clave[i])];
            i++;
        }
        if(it->cantHijos>0){
            delete it->definicion;
            it->definicion = NULL;
        } else {
            Nodo* aBorrar = it;
            delete aBorrar;
            it = camino.top();
            it->cantHijos--;
            int j = clave.size() - 1;
            while(it->cantHijos==0 && it->definicion== NULL && j >0){
                Nodo* borrar = it;
                borrar->siguientes[int(clave[j])] = NULL;
                camino.pop();
                delete borrar;
                it = camino.top();
                it->cantHijos--;
                j--;
            }
            it->siguientes[int(clave[j])] = NULL;

        }
    }

    _size--;
    auto iter = palabras.begin();
    while(iter!= palabras.end()){
        if( *iter == clave){
            iter = palabras.erase(iter);
        }
        ++iter;
    }
    while(!camino.empty()){
        camino.pop();
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return raiz == NULL;
}