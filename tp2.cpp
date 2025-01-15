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
#define COLOR_NEGRO "\033[0;30m"
#define COLOR_ROJO "\033[0;31m"
#define COLOR_VERDE "\033[0;32m"
#define COLOR_AMARILLO "\033[0;33m"
#define COLOR_AZUL "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CIAN "\033[0;36m"
#define COLOR_BLANCO "\033[0;37m"

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
    Nodo<T>* get_nodoLista() { return nodoLista;};
};

struct InfoEficiencia {
    int comparaciones;
    int movimientos;
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
        void swap(Nodo<T>* nodo1,Nodo<T>* nodo2 );
        InfoEficiencia QuickSortAux(Nodo<T>* cabeza, int primero, int ultimo);
        ArbolBinario<T>* getArbolbin(){if(arbolbin==nullptr)arbolbin= new ArbolBinario<T>(getProfundidad(siz),this);
                                        return arbolbin;};
       
public:
    EstructuraDualColaArbol() { czo = new Nodo<T>(); raiz=nullptr; listainorden=nullptr; siz=0; arbolbin=nullptr;};
    EstructuraDualColaArbol(Nodo<T>* n) { czo = n; raiz=n; listainorden=nullptr; siz=1;arbolbin=nullptr;};
    void add(T d); 
    bool esvacia(void);
    InfoEficiencia ordenarSeleccion();
    Nodo<T>* nodoCabeza(void); //retorna el dato del primer nodo
    EstructuraDualColaArbol* resto(void); //retorna el puntero al "resto" de la lista
    void impre();
    void impreAlf();
    T last(); //retorna el dato del ultimo nodo
     EstructuraDualColaArbol <T>* getListainorden();
     int get_siz(){return siz;};
     /*********************************/
    InfoEficiencia ordenarQuickSort(){ return QuickSortAux(czo,0,siz-1);};


};

template<class T> 
void EstructuraDualColaArbol<T>::swap(Nodo<T>* nodo1,Nodo<T>* nodo2 ){
    if(nodo1== nullptr || nodo2== nullptr){
        cout<< "Error en la funcion swap"<< flush;
        return;
    }
 T auxdato=nodo2->get_dato();
 int auxcont=nodo2->get_contador();
  nodo2->set_contador(nodo1->get_contador());
  nodo2->set_dato(nodo1->get_dato());
  nodo1->set_dato(auxdato);
  nodo1->set_contador(auxcont);
}

template<class T>
InfoEficiencia EstructuraDualColaArbol<T>:: QuickSortAux(Nodo<T>* cabeza, int primero, int ultimo) {
    InfoEficiencia info;// tiene la variable int comparaciones y variable int movimientos
    info.comparaciones=0;
    info.movimientos=0;
    if (ultimo > primero) {
        // Obtén el valor del pivote
        Nodo<T>* pivot = getArbolbin()->buscarNodo(ultimo);
        int i = primero - 1;
        int j = ultimo;

        while (true) {
            
          while (i < siz && getArbolbin()->buscarNodo(++i)->get_dato() > pivot->get_dato())info.comparaciones++;
          while (j > primero && getArbolbin()->buscarNodo(--j)->get_dato() < pivot->get_dato())info.comparaciones++;


            if (++info.comparaciones && i >= j) break;

            // Intercambia los valores entre buscarNodo(i) y buscarNodo(j)
            swap(getArbolbin()->buscarNodo(i),getArbolbin()->buscarNodo(j));
            info.movimientos+=6;
        }

        // Intercambia el pivote con el nodo en la posición i
        swap(getArbolbin()->buscarNodo(i), pivot);
        info.movimientos+=6;
        // Llamadas recursivas para las sublistas
       InfoEficiencia infoIzq = QuickSortAux(cabeza, primero, i - 1);
       InfoEficiencia infoDer =QuickSortAux(cabeza, i + 1, ultimo);
       info.comparaciones += infoIzq.comparaciones + infoDer.comparaciones;
       info.movimientos += infoIzq.movimientos + infoDer.movimientos;
    }
    return info;
}

template <class T>
InfoEficiencia EstructuraDualColaArbol<T>:: ordenarSeleccion(){
    Nodo<T>* men;
    Nodo<T>* max;
    InfoEficiencia info;
    info.comparaciones=0;
    info.movimientos=0;

    for(int i=0;i<(siz-1)/2;i++){
        men = getArbolbin()->buscarNodo(i);
   for(int j=i+1;j<siz-3-i;j++){
     if(getArbolbin()->buscarNodo(j)->get_contador()<men->get_contador()){
       men=getArbolbin()->buscarNodo(j); 
     }
      info.comparaciones++;
   }
   
  swap(getArbolbin()->buscarNodo(i),men);
  info.movimientos+=6;
  max = getArbolbin()->buscarNodo(siz-i-1);
 
   for(int k=siz-i-2; k>i+3; k--){
     if(getArbolbin()->buscarNodo(k)->get_contador()>max->get_contador()){
       max= getArbolbin()->buscarNodo(k);
     }
      info.comparaciones++;
   }
  swap(getArbolbin()->buscarNodo(siz-i-1),max);
  info.movimientos+=6;
 }
return info;
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
        if (this->resto()->esvacia())return this->nodoCabeza()->get_dato();
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
        cout <<nodoCabeza()->get_dato() << "("<< nodoCabeza()->get_contador() << ")" << endl;
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

int main(int argc, char* argv[])
{
     char* linea= new char[TAMANOPALABRA];
      EstructuraDualColaArbol<string>* lista= new EstructuraDualColaArbol<string>();
       FILE *doc;
       char buffer[TAMANOPALABRA]; // Buffer para almacenar temporalmente las palabras
    while (true) {
   
if(argc>1){
    linea=argv[1];
}


   if(linea[0] == '\0'){
    string aux="texto.txt";
    strcpy(linea, aux.c_str());
   }
    doc=fopen(linea,"r");
    if(doc==NULL){
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }
    while (fscanf(doc, "%255s", buffer) != EOF) { // Leer palabra por palabra
        limpiarYConvertirAMinusculas(buffer);
        lista->add(buffer); 
    }

    fclose(doc); 
   
    bool nuevoTexto=false;
    while(true){
        int x;
        if(nuevoTexto){
            nuevoTexto=false;
            break;
        }
        cout<< COLOR_AZUL<< "Ingrese el numero correspondiente a la accion que desea realizar"<< endl;
        cout<<COLOR_CIAN<<"digite 1 para imprimir la lista."<< endl;
        cout<<endl<<"digite 2 para ordenar la lista almacenada, ordenada por cantidad de apariciones de las palabras.Usando seleccion";
        cout<<endl<<"digite 3 para ordenar la lista almacenada por sus palabras en orden alfabetico usando quicksort.";
        cout<<endl<< "digite 4 para imprimir la lista alfabeticamente usando busqueda por arbol";
        cout<< endl<< "digite 5 leer otro archivo de texto.";
        cout<< endl<< "digite 6 para visualizar el listado de textos posibles a analizar.";
        cout<< endl<< "digite 7 para finalizar el programa."<< endl << COLOR_BLANCO;
        cin >> x;
          if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada no válida
            cout << "Entrada no válida. Por favor, introduce un número." << endl;
            continue;
        } 
        cout<< endl;
        switch (x) {
            case 1:
            lista->impre();
            break;
            case 2:
            {
            InfoEficiencia info= lista->ordenarSeleccion();
            lista->impre();
            cout<<"El algoritmo de seleccion realizo " <<info.comparaciones<< " comparaciones y " << info.movimientos << " movimientos" << endl;
            }
            break;
            case 3:
            {
            InfoEficiencia info = lista->ordenarQuickSort();
            lista->impre();
            cout<<"El algoritmo QuickSort realizo " <<info.comparaciones<< " comparaciones y " << info.movimientos << " movimientos" << endl;
            }
            break;
            case 4:
            lista->impreAlf();
            break;
            case 5:
            cout<< "Ingrese el nombre del archivo de texto que quiera analizar"<< endl;
            cin>>linea;
            nuevoTexto=true;
            continue;
            case 6:
            cout<<"listado de archivos de texto posible:"<< endl;
            {
            FILE* pipe = popen("dir", "r");
             if (!pipe) {
                 pipe = popen("ls", "r");
        
             if (!pipe) {
                  cerr << "No se pudo ejecutar el comando.\n";
                 return EXIT_FAILURE;
                 }
             }
              char bufferLS[TAMANOPALABRA];
              while (fgets(bufferLS, sizeof(bufferLS), pipe)) {
                 if (strstr(bufferLS, ".txt") != nullptr) {
                        cout << bufferLS; 
                    }
              }
                 fclose(pipe);
               }
            break;
            case 7:
            return (EXIT_SUCCESS);
            break;
            default:
            cout<< "El valor ingresado no corresponde a un numero valido"<< endl;
            continue;
            break;
        
        }

    }
   delete lista;
    lista= new EstructuraDualColaArbol<string>();

    }
}