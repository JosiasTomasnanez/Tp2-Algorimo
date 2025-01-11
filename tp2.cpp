#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class T> class Nodo {
private:
    T dato;
    Nodo* next;
    Nodo* derecha;
    Nodo* izquierda;
    int contador;
public:
    Nodo() { next = NULL;  contador=0; };
    Nodo(T a) { dato = a; next = NULL; contador=0; };
    void set_dato(T a) { dato = a; };
    void incrementarContador(){contador++;}
    void set_next(Nodo* n) { next = n; };
    T get_dato() { return dato; };
    Nodo*& get_der(){return derecha;}
    void set_der(Nodo* n) { derecha = n; };
    Nodo*& get_izq(){return izquierda;}
     void set_izq(Nodo* n) { izquierda = n; };
    Nodo* get_next() { return next; };
    bool es_vacio() { return next == NULL; }
};

template <class T> class Lista {
private:
       Nodo<T>* czo;
       Nodo<T>* raiz;
       void addO(T d, Nodo<T>* ant);
       void borrarD(T d, Nodo<T>* ant);
       void arbolAdd(Nodo<T>*& raiz,Nodo<T>* nuevo);
       void show(Nodo<T>* aux, int n);
       Nodo<T>* buscarNodoArbol(T d){ return nullptr;};
public:
    Lista() { czo = new Nodo<T>(); raiz=nullptr;};
    Lista(Nodo<T>* n) { czo = n; raiz=n; };
    //~Lista(void);
    void add(T d); //sumar nodos a la lista
    bool esvacia(void);
    T cabeza(void); //retorna el dato del primer nodo
    Lista* resto(void); //retorna el puntero al "resto" de la lista
                        //resto= lo que queda de la lista sin la cabeza
    string toPrint(string p);
    void impre(void);
    T suma(T i);
    void VerArbol() { show(raiz, 0);}
    int  size();
    bool esta(T d);// detecta si d esta en la lista
    void borrarDato(T d) { borrarD(d, NULL); }//borra el nodo que contiene d
    void borrar(void); //borra la cabeza
    void borrar_last();//borra el ultimo
    void concat(Lista<T>* l1);// le transfiere los datos de l1 a this
    Lista<T>* copy(void);// hace una copia de la lista
    void tomar(int n);//deja "vivos" los n primeros nodos y borra el resto
    void addOrdenado(T d) { addO(d, NULL); }; //sumar nodos a la lista Ordenados de menor a MAYOR
    T last(); //retorna el dato del ultimo nodo

};
template <class T>
T Lista<T>::last()
{
    if (!this->esvacia()) {
        if (this->resto()->esvacia())return this->cabeza();
        return this->resto()->last();
    }return 0;
}

template <class T>
void Lista<T>::arbolAdd(Nodo<T>*& raiz, Nodo<T>* nuevoNodo ){
     if (!raiz) {
        nuevoNodo ->set_der(nullptr);
        nuevoNodo->set_izq(nullptr);
        raiz = nuevoNodo; // Inserta el nodo en el árbol
    
            return;
        }
        if (nuevoNodo->get_dato() < raiz->get_dato()) {
            
            arbolAdd(raiz->get_izq() , nuevoNodo);
        } else {
           arbolAdd(raiz->get_der() , nuevoNodo);
        }
}
// template <class T>
// Nodo<T>* Lista<T>::buscarNodoArbol(T d) {
//     Nodo<T>* actual = raiz;
//     while (actual) {
//         if (actual->get_dato() == d) {
//             return actual; // Nodo encontrado
//         } else if (d < actual->get_dato()) {
//             actual = actual->get_izq();
//         } else {
//             actual = actual->get_der();
//         }
//     }
//     return nullptr; // Nodo no encontrado
// }


template <class T>
void Lista<T>::add(T d) //100
{
   Nodo<T>* aux= buscarNodoArbol(d);
   if(aux==nullptr){
    Nodo<T>* nuevo = new Nodo<T>(d);
    arbolAdd(raiz,nuevo);
    nuevo->set_next(czo);
    czo = nuevo;

   }else{
   aux->incrementarContador();
   }
    
}
template <class T>
bool Lista<T>::esvacia(void)
{
    return czo->es_vacio();
}
template <class T>
T Lista<T>::cabeza(void)
{
    if (this->esvacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo->get_dato();
}

template <class T>
Lista<T>* Lista<T>::resto(void)
{
    Lista* l = new Lista(czo->get_next());
    return (l);
}

template <class T>
string Lista<T>::toPrint(string p)
{
    if (this->esvacia()) {
        return p;
    }
    else {
        //std::ostringstream stm;
        ostringstream stm;
        stm << this->cabeza() << "-" << this->resto()->toPrint(p) << endl;
        //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
        return stm.str();
    }
}

template <class T>
T Lista<T>::suma(T i)
{    //cout<<" i al entrar= "<<i<<endl;
    if (this->esvacia()) {
        return i;
    }
    else {

        //cout<<"this->cabeza()= "<<this->cabeza()<<endl;   
        return this->resto()->suma(i + this->cabeza());
    }
}


template <class T> int Lista<T>::size()
{
    if (this->esvacia()) return 0;
    return 1 + this->resto()->size();
}



template <class T> void Lista<T>::borrar(void)
{ //borra el nodo cabeza
    if (!this->esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}

template <class T> void Lista<T>::borrar_last()
{ // borra el ultimo nodo
    if (!this->esvacia()) {
        if ((czo->get_next())->get_next() == NULL) {
            delete czo->get_next();
            czo->set_next(NULL);
        }
        else this->resto()->borrar_last();
    }
}

template <class T> void Lista<T>::concat(Lista<T>* l1)
{// le transfiere los datos de l1 a this
    if (!(l1->esvacia())) {
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}

template <class T> Lista<T>* Lista<T>::copy(void)
{
    Lista<T>* aux = new Lista();
    aux->concat(this);
    return aux;
}

template <class T> void Lista<T>::tomar(int n)
{ //deja "vivos" los n primeros nodos y borra el resto
    if (this->size() > n) {
        this->borrar_last();
        this->tomar(n);
    }
}

template <class T> void Lista<T>::impre(void)
{
    Nodo<T>* aux;
    aux = czo;
    while (aux->get_next() != NULL) {
        cout << aux->get_dato() << endl;
        aux = aux->get_next();
    }
}

template <class T>
void Lista<T>::addO(T d, Nodo<T>* ant)
{
    if (this->esvacia()) {//el primero
        this->add(d);
    }
    else {
        if (d < czo->get_dato()) {
            if (ant == NULL) {//al principio
                this->add(d);
            }
            else {//entre medio
                Nodo<T>* nuevo = new Nodo<T>(d);
                nuevo->set_next(ant->get_next());
                ant->set_next(nuevo);
            }
        }
        else {
            if ((czo->get_next())->get_next() == NULL) {//al final
                Nodo<T>* nuevo = new Nodo<T>(d);
                nuevo->set_next(czo->get_next());
                czo->set_next(nuevo);

            }
            else this->resto()->addO(d, czo);

        }
    }
}

template <class T> bool Lista<T>::esta(T d)
{// busca d en la lista
    if (this->esvacia()) return false;
    if (this->cabeza() == d) return true;

    return this->resto()->esta(d);
}

template <class T>
void Lista<T>::borrarD(T d, Nodo<T>* ant)
{
    if (!this->esvacia()) {
        if (d == this->cabeza()) {
            if (ant == NULL) {//al principio
                this->borrar();
            }
            else {//entre medio
                ant->set_next(czo->get_next());
                delete czo;
            }
        }
        else  this->resto()->borrarD(d, czo);

    }
}


template <class T> class Pila :public Lista<T> {
public:
    Pila() { Lista<T>(); };
    void apilar(T d) { this->add(d); };
    T tope(void) { return this->cabeza(); };
    void desapilar(void) { this->borrar(); };
    bool pilavacia() { return this->esvacia(); };
};
template <class T> class Cola :public Lista<T> {
public:
    Cola(void) { Lista<T>(); };
    //~Cola(void);
    T tope() { return this->last(); };
    bool colavacia(void) { return this->esvacia(); };
    void encolar(T a) { this->add(a); };
    void desencolar(void) { this->borrar_last(); };
    T ultimo(void) { return this->cabeza(); };
    string imprimir(string s) { return this->toPrint(s); };
};

template <class T> void Lista<T>::show( Nodo<T>* aux, int n)
{
    int i;
    if (aux != NULL) {                      //OjO este es un recorrido dri
        show(aux->get_der(), n + 1);
        for (i = 1; i <= n; i++) cout << "     ";
        cout << aux->get_dato() << "\n";
        show(aux->get_izq(), n + 1);
    }
}
int main()
{
  Lista<string> lista;
  lista.add("ale");
  lista.add("juan");
  lista.add("cesar");
  lista.add("lucas");
  lista.add("pedro");
  lista.VerArbol();
  lista.impre();
  return 0;
}

