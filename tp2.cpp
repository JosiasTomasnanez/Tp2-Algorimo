#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring> 


#define TAMANOPALABRA  256

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
    int get_contador(void){return contador;};
    void set_contador(int cont){contador=cont;}
    void set_dato(T a) { dato = a; };
    void incrementarContador(){contador++;};
    void set_next(Nodo* n) { next = n; };
    T get_dato(void) { return dato; };
    Nodo*& get_der(void){return derecha;};
    void set_der(Nodo* n) { derecha = n; };
    Nodo*& get_izq(){return izquierda;};
     void set_izq(Nodo* n) { izquierda = n; };
    Nodo* get_next(void) { return next; };
    bool es_vacio(void) { return next == NULL; };
};

template <class T> class EstructuraDualColaArbol {
private:
       Nodo<T>* czo;
       Nodo<T>* raiz;
       EstructuraDualColaArbol <T>* listainorden;
       void arbolAdd(Nodo<T>*& raiz,Nodo<T>* nuevo);
       void show(Nodo<T>* aux, int n);
       Nodo<T>* buscarNodoArbol(T d, Nodo<T>* aux);
       void impreAlfAux(Nodo<T>* aux);
        void generarListaInorden(Nodo<T>* aux);
public:
    EstructuraDualColaArbol() { czo = new Nodo<T>(); raiz=nullptr; listainorden=nullptr;};
    EstructuraDualColaArbol(Nodo<T>* n) { czo = n; raiz=n; listainorden=nullptr; };
    void add(T d); //sumar nodos a la lista
    bool esvacia(void);
    Nodo<T>* nodoCabeza(void); //retorna el dato del primer nodo
    EstructuraDualColaArbol* resto(void); //retorna el puntero al "resto" de la lista
    void impre();
    void impreAlf();
    void VerArbol() { show(raiz, 0);};
    T last(); //retorna el dato del ultimo nodo
     EstructuraDualColaArbol <T>* getListainorden();

};
template <class T>
T EstructuraDualColaArbol<T>::last()
{
    if (!this->esvacia()) {
        if (this->resto()->esvacia())return this->cabeza();
        return this->resto()->last();
    }return 0;
}
template <class T>
EstructuraDualColaArbol <T>* EstructuraDualColaArbol<T>::getListainorden(){
    if(listainorden==nullptr) generarListaInorden(raiz);
    return listainorden;
}

template <class T>
void EstructuraDualColaArbol<T>::arbolAdd(Nodo<T>*& raiz, Nodo<T>* nuevoNodo ){
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
template <class T>
Nodo<T>* EstructuraDualColaArbol<T>::buscarNodoArbol(T d, Nodo<T>* aux) {
   if (aux == NULL) {
        return nullptr;
    }
    if (d == aux->get_dato()) { return aux; }
    if (d < aux->get_dato()) { return buscarNodoArbol(d, aux->get_izq());}
    return buscarNodoArbol(d, aux->get_der());
}


template <class T>
void EstructuraDualColaArbol<T>::add(T d) //100
{
   Nodo<T>* aux= buscarNodoArbol(d,raiz);
   if(aux==nullptr){
    Nodo<T>* nuevo = new Nodo<T>(d);
    arbolAdd(raiz,nuevo);
    nuevo->set_next(czo);
    czo = nuevo;
    aux=nuevo;
   }
   aux->incrementarContador();
}
template <class T>
bool EstructuraDualColaArbol<T>::esvacia(void)
{
    return czo->es_vacio();
}
template <class T>
Nodo<T>* EstructuraDualColaArbol<T>::nodoCabeza(void)
{
    if (this->esvacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo;
}

template <class T>
EstructuraDualColaArbol<T>* EstructuraDualColaArbol<T>::resto(void)
{
    EstructuraDualColaArbol* l = new EstructuraDualColaArbol(czo->get_next());
    return (l);
}


template <class T>
void EstructuraDualColaArbol<T>::impre() {
    if (!esvacia()) {
        resto()->impre();
        cout << nodoCabeza()->get_dato() << "("<< nodoCabeza()->get_contador() << ")" << endl;
    }
}

template <class T>
void EstructuraDualColaArbol<T>::generarListaInorden(Nodo<T>* aux){
   if (aux != NULL) {
    if (listainorden == nullptr) {
            listainorden = new EstructuraDualColaArbol <T>();  // Suponiendo que miLista es de tipo Lista<T>
        }
        generarListaInorden(aux->get_izq());
        listainorden->add(aux->get_dato());
        listainorden->nodoCabeza()->set_contador(aux->get_contador());
        generarListaInorden(aux->get_der());
    }
}


template <class T>
void EstructuraDualColaArbol<T>::impreAlf(){
   if(getListainorden()==nullptr){
    generarListaInorden(raiz);
    }
   getListainorden()->impre();
}

template <class T> void EstructuraDualColaArbol<T>::show( Nodo<T>* aux, int n)
{
    int i;
    if (aux != NULL) {                      //OjO este es un recorrido dri
        show(aux->get_der(), n + 1);
        for (i = 1; i <= n; i++) cout << "     ";
        cout << aux->get_dato() << "\n";
        show(aux->get_izq(), n + 1);
    }
}

void limpiarYConvertirAMinusculas(char* palabra) {
    int len = strlen(palabra);
    int i = 0;
    
    // Recorrer la palabra y hacer ambas operaciones en el mismo ciclo
    for (int j = 0; j < len; j++) {
        if (isalnum(palabra[j])) {  // Si el caracter es alfanumérico
            palabra[i++] = tolower(palabra[j]);  // Convertir a minúsculas y moverlo al principio
        }
    }
    palabra[i] = '\0'; // Asegurarse de que la cadena termine correctamente
}

int main()
{
    FILE *doc;
    EstructuraDualColaArbol<string> lista;
    doc=fopen("texto.txt","r");
    if(doc==NULL){
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }
     char buffer[TAMANOPALABRA]; // Buffer para almacenar temporalmente las palabras
    while (fscanf(doc, "%255s", buffer) != EOF) { // Leer palabra por palabra
        limpiarYConvertirAMinusculas(buffer);
        lista.add(buffer); 
    }

    fclose(doc); 
  lista.getListainorden()->impre();
  //lista.VerArbol();//visualizar arbol
  //lista.impreAlf();// visualizar palabras orden alfabetico;
 // lista.impre();//visualizar palabras en orden de llegada y cantidad de veces uqe se repiten
  return 0;
}

