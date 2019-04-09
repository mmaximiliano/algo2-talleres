
template <class T>
Conjunto<T>::Conjunto() {
    _raiz = NULL;
}

template <class T>
Conjunto<T>::~Conjunto() {
    borrar(_raiz);
}

template <class T>
void Conjunto<T>::borrar(Nodo* p) {
    if(p == NULL){
        //caso base
    }else{
        borrar(p->izq);
        borrar(p->der);
        delete p;
    }

}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* p = _raiz;
    bool encontramos = false;
    while(p!=NULL && !encontramos){
        if(p!=NULL && p->valor == clave){
            encontramos = true;
        }
        if(p->valor < clave){
            p = p->der;
        } else{
            p = p->izq;
        }
    }

    return encontramos;
}


template <class T>
void Conjunto<T>::insertar(const T& clave) {

    Nodo* nuevo = new Nodo(clave);
    if(_raiz == NULL){
        _raiz = nuevo;
    } else{
        if(!(pertenece(clave))){
            Nodo* p = _raiz;
            Nodo* padre = NULL;
            while(p!=NULL){
                padre = p;
                if(p->valor < clave){
                    p = p->der;
                } else{
                    p = p->izq;
                }
            }

            if(padre->valor > clave){
                padre->izq = nuevo;
            } else{
                padre->der = nuevo;
            }

        } else{
            delete nuevo;
        }
    }
}


template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::buscar(const T& clave) {
    Nodo *p = _raiz;

    while (p->valor != clave) {
        if (p->valor < clave) {
            p = p->der;
        } else {
            p = p->izq;
        }
    }

    return p;
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(pertenece(clave)){
        Nodo *padre = NULL;
        Nodo *p = _raiz;
        while (p->valor != clave) {
            padre = p;
            if (p->valor < clave) {
                p = p->der;
            } else {
                p = p->izq;
            }
        }
        if (p == _raiz ){
            //Caso soy raiz
            if(p->izq == NULL && p->der==NULL) {
                // No tengo hijos
                _raiz = NULL;
            } else if(p->izq != NULL xor p->der !=NULL) {
                // Tengo un hijo
                if(p->der != NULL){
                    _raiz = p->der;
                } else {
                    _raiz = p->izq;
                }
            } else {
                // Tengo dos hijos
                _raiz = p->der;
                Nodo* minDerecha = p->der;
                while (minDerecha->izq!=NULL){
                    minDerecha = minDerecha->izq;
                }
                minDerecha->izq = p->izq;
            }
        }else if(p->izq == NULL && p->der==NULL) {
            // Caso sin hijos.
            if (padre->valor < p->valor) {
                padre->der = NULL;
            } else {
                padre->izq = NULL;
            }
        } else if(p->izq != NULL xor p->der !=NULL){
            // Caso un solo hijo.
            if(p->der != NULL){
                if (padre->valor < p->valor) {
                    padre->der = p->der;
                } else {
                    padre->izq = p->der;
                }
            } else{
                // Caso dos hijos
                if (padre->valor < p->valor) {
                    padre->der = p->izq;
                } else {
                    padre->izq = p->izq;
                }
            }
        } else if (p->der != NULL && p->izq != NULL && p != _raiz) {
            // Caso dos hijos y no soy raiz.
            if (padre->valor < p->valor) {
                padre->der = p->der;
            } else {
                padre->izq = p->der;
            }
            Nodo* minDerecha = p->der;
            while (minDerecha->izq!=NULL){
                minDerecha = minDerecha->izq;
            }
            minDerecha->izq = p->izq;
        }
        delete p;
    } else {
        //NADA.
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    bool encontramos = false;
    Nodo *p = _raiz;
    Nodo *padre = p;
    stack<Nodo*> pila;
    while (!encontramos && p != NULL) {
        if (p->valor == clave) {
            encontramos = true;
        } else {
            padre = p;
            pila.push(padre);
            if (p->valor < clave) {
                p = p->der;
            } else {
                p = p->izq;
            }
        }
    }
     // Caso A
     if (p->der != NULL) {
         p = p->der;
         while (p->izq != NULL) {
             p = p->izq;
         }
     }else{
         // Caso B1
         if ((padre->izq)->valor = p->valor){
             p = padre;
         }else{
             // Caso B2

             while(!(((pila.top())->izq)->valor = p->valor)){
                 p = pila.top();
                 pila.pop();
             }

         }
     }
     return p->valor;
 }

    template <class T>
    const T& Conjunto<T>::minimo() const {
        Nodo* p = _raiz;
        while((p->izq) != NULL){
            p = p->izq;
        }
        return p->valor;

        //assert(false);
    }

    template <class T>
    const T& Conjunto<T>::maximo() const {
        Nodo *p = _raiz;
        while((p->der) != NULL){
            p = p->der;
        }
        return p->valor;

        //assert(false);
    }

    template <class T>
    unsigned int Conjunto<T>::cardinal() const {
        //assert(false);
        int cant = cardAux(_raiz);
        return cant;
    }

    template <class T>
    int Conjunto<T>::cardAux(Nodo* p) const{
        int cant = 0;

        if(p != NULL){
            cant = 1 + cardAux(p->izq) + cardAux(p->der);
        }

        return cant;
    }

    template <class T>
    void Conjunto<T>::mostrar(std::ostream&) const {
        assert(false);
    }

    template <class T>
    const T& Conjunto<T>::minimoSubArbol(Nodo* raiz) const {
        return minimo();
    }