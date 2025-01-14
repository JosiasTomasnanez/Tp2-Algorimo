#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <stdio.h>
#include <cstring> 
#include <vector>
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
    Nodo() { next = NULL;  contador=0;  };
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
template <class T> class NodoArbolBinario {
private:
    Nodo<T>* nodoLista;
    NodoArbolBinario<T>* derecha;
    NodoArbolBinario<T>* izquierda;

public:
    NodoArbolBinario() : nodoLista(nullptr), derecha(nullptr), izquierda(nullptr) {};
    NodoArbolBinario<T>*& get_der(void){return derecha;};
    void set_der(NodoArbolBinario<T>* n) { derecha = n; };
    NodoArbolBinario<T>*& get_izq(){return izquierda;};
     void set_izq(NodoArbolBinario<T>* n) { izquierda = n; };
     void set_nodoLista(Nodo<T>* n) { nodoLista = n; };
     
    /*************************/
    Nodo<T>* get_nodoLista() { return nodoLista;};
};

template<class T>
class EstructuraDualColaArbol;

template <class T> class ArbolBinario{
private:
    NodoArbolBinario<T>* raiz ;int profundidad;
    void ArbolBusq(T x, NodoArbolBinario<T>*& nuevo);
    void crearArbol(NodoArbolBinario<T>*& actual,int profundidad);
    void insertarDatos(EstructuraDualColaArbol<T>* lista, int profundidad);
    void insertardatoaux(NodoArbolBinario<T>* actual,vector<bool> posicion, Nodo<T>* nuevo);
    Nodo<T>* buscarNodoAux(NodoArbolBinario<T>* actual,vector<bool> k,int pos);
    vector<bool> getBin(int k);
public:
    ArbolBinario( int profundidad, EstructuraDualColaArbol<T>* lista) {
                this->profundidad=profundidad;
                 crearArbol(raiz, profundidad);
                 insertarDatos(lista,profundidad);
                  };
    ~ArbolBinario() {};
    Nodo<T>* buscarNodo(int k){return buscarNodoAux(raiz, getBin(k), 0);};

};

template<class T> 
vector<bool> ArbolBinario<T>:: getBin(int k){
vector<bool> v(profundidad, false); // Iniciar el vector con 'p' bits en falso
        // Llenar el vector con los bits del número (i-1) en binario
        int num = k - 1;
        for (int j = 0; j < profundidad; j++) {
            v[profundidad - j - 1] = (num & (1 << j)) != 0;  // Asignar cada bit de forma inversa
        }
        return v;
 }



template<class T> 
Nodo<T>* ArbolBinario<T>::buscarNodoAux(NodoArbolBinario<T>* actual,vector<bool> k,int pos){
        if (pos >= k.size()) {
        return actual->get_nodoLista();
    }
        if(k[pos]==1){
          return  buscarNodoAux(actual->get_der(),k,pos+1);
        }else{
          return  buscarNodoAux(actual->get_izq(),k,pos+1);
        }
}

template<class T> 
void ArbolBinario<T>::insertarDatos( EstructuraDualColaArbol<T>* lista,int profundidad) {
    EstructuraDualColaArbol<T>*aux=lista;
    
    for(int i=1; i<=lista->get_siz();i++){
  vector<bool> k= getBin(i-1);
   insertardatoaux(raiz,k,aux-> nodoCabeza());
   aux=aux->resto();

    }

    }

template<class T> 
void ArbolBinario<T>::insertardatoaux(
    NodoArbolBinario<T>* actual, 
    vector<bool> posicion, 
    Nodo<T>* nuevo) 
{
    if (posicion.empty()) {
        actual->set_nodoLista(nuevo); 
        return;
    }

    bool direccion = posicion.front();
    posicion.erase(posicion.begin());

    if (direccion == false) { 
        if (!actual->get_izq()) {
            actual->set_izq(new NodoArbolBinario<T>());
        }
        insertardatoaux(actual->get_izq(), posicion, nuevo);
    } else { 
        if (!actual->get_der()) {
            actual->set_der(new NodoArbolBinario<T>());
        }
        insertardatoaux(actual->get_der(), posicion, nuevo);
    }
}


template<class T> 
void ArbolBinario<T>::crearArbol(NodoArbolBinario<T>*& actual, int profundidad) {
if (profundidad == 0) {
            return;
        }
        actual = new NodoArbolBinario<T>();
        crearArbol(actual->get_izq(), profundidad - 1); 
        crearArbol(actual->get_der(), profundidad - 1); 
 }



/**************************************************************************************** 
 ****************************************************************************************/



template <class T> class EstructuraDualColaArbol {
private:
       Nodo<T>* czo;
       Nodo<T>* raiz;
       ArbolBinario<T>* arbolbin;
       int siz;
       EstructuraDualColaArbol <T>* listainorden;
       void arbolAdd(Nodo<T>*& raiz,Nodo<T>* nuevo);
       Nodo<T>* buscarNodoArbol(T d, Nodo<T>* aux);
       void impreAlfAux(Nodo<T>* aux);
       int getProfundidad(int num);
       void generarListaInorden(Nodo<T>* aux);
        ArbolBinario<T>* getArbolbin(){if(arbolbin==nullptr)arbolbin= new ArbolBinario<T>(getProfundidad(siz),this);
                                        return arbolbin;};
       
public:
    EstructuraDualColaArbol() { czo = new Nodo<T>(); raiz=nullptr; listainorden=nullptr; siz=0; arbolbin=nullptr;};
    EstructuraDualColaArbol(Nodo<T>* n) { czo = n; raiz=n; listainorden=nullptr; siz=1;arbolbin=nullptr;};
    void add(T d); 
    bool esvacia(void);
    void ordenarSeleccion();
    Nodo<T>* nodoCabeza(void); //retorna el dato del primer nodo
    EstructuraDualColaArbol* resto(void); //retorna el puntero al "resto" de la lista
    void impre();
    void impreAlf();
    T last(); //retorna el dato del ultimo nodo
     EstructuraDualColaArbol <T>* getListainorden();
     int get_siz(){return siz;};
     /*********************************/
    void QuickSort(ArbolBinario<T>, int, int);
    Nodo<T>* QuickSortAux(ArbolBinario<T>, int, int);


};


template <class T>
void EstructuraDualColaArbol<T>:: ordenarSeleccion(){
    Nodo<T>* men;
    Nodo<T>* max;
    Nodo<T>*aux2;
    int auxcont=0;
    T auxdato;

    for(int i=0;i<siz-1;i++){
        // m++;
        men = getArbolbin()->buscarNodo(i+1);
   for(int j=i+1;j<siz-i;j++){
     //c++;
     if(getArbolbin()->buscarNodo(j)->get_contador()<men->get_contador()){
       men=getArbolbin()->buscarNodo(j); //m++;
     }
   }
   
  aux2=getArbolbin()->buscarNodo(i);
  auxdato=men->get_dato();
  auxcont=men->get_contador();
  men->set_contador(aux2->get_contador());
  men->set_dato(aux2->get_dato());
  aux2->set_dato(auxdato);
  aux2->set_contador(auxcont);

 max = getArbolbin()->buscarNodo(siz-i-1);
 
   for(int k=siz-i-2; k>i; k--){
    // c++;
     if(getArbolbin()->buscarNodo(k)->get_contador()>max->get_contador()){
       max= getArbolbin()->buscarNodo(k);// m++;
     }
   }
  aux2=getArbolbin()->buscarNodo(siz-i-1);
  auxdato=max->get_dato();
  auxcont=max->get_contador();
  max->set_contador(aux2->get_contador());
  max->set_dato(aux2->get_dato());
  aux2->set_dato(auxdato);
  aux2->set_contador(auxcont);
 }

}




 








template <class T>
int EstructuraDualColaArbol<T>:: getProfundidad(int num){
    int prof=0;
    int aux=1;
   while (aux<num) {
    aux= aux*2;
   prof++;
   }
   return prof;
}





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
    if (d == aux->get_dato()) return aux; 
    if (d < aux->get_dato()) return buscarNodoArbol(d, aux->get_izq());
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
    siz++;
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


/**************************************************************************************** 
 ****************************************************************************************/


template <class T>
void EstructuraDualColaArbol<T>::QuickSort(ArbolBinario<T> arbolbinario, int inicio, int final){
    int i,j,k;
    i=inicio-1;
    Nodo<T> aux;
    Nodo<T>* pivote;
    
    // if (final>inicio)
    // {
    //     pivote = arbolbinario->BuscarPosicion(final);
    //     i=inicio-1; j=final;
    //     for(;;){
    //                  while(v[++i]<pivot)cc++;
    //                  while(v[ --j ] >pivot)cc++;
    //                  if(i>=j)break;
    //                  aux=v[i];v[i]=v[j];v[j]=aux; cm=cm+3;     
    //          }
    // }
    

    


   
}

// void ordenaQS(int v[], int primero, int ultimo)
// { int i,j,k,pivot,aux;
//       if(ultimo>primero){
//              pivot=v[ultimo];cm++;
//              //printf("\n -> %d  %d <-%4i",primero,ultimo,pivot);
//              i=primero-1; j=ultimo;      
//              for(;;){
//                      while(v[++i]<pivot)cc++;
//                      while(v[ --j ] >pivot)cc++;
//                      if(i>=j)break;
//                      aux=v[i];v[i]=v[j];v[j]=aux; cm=cm+3;     
//              }// fin for
//              aux=v[i];v[i]=v[ultimo];v[ultimo]=aux;cm=cm+3;
//              //for(k=0;k<10;k++)printf("\n a[%d]=%d",k,v[k]);
//              //printf("\n ------------------------------------");
//              ordenaQS(v,primero,i-1);
//              ordenaQS(v,i+1,ultimo);
//              //printf("\nRETORNO -> %d  %d <-",primero,ultimo);
//       } //fin if 
// }// fin ordena



/**************************************************************************************** 
 ****************************************************************************************/


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
 // lista.impre();
  //lista.ordenarSeleccion();
  lista.impre();

  
  //lista.impreAlf();// visualizar palabras orden alfabetico;
 // lista.impre();//visualizar palabras en orden de llegada y cantidad de veces uqe se repiten
  return 0;
}