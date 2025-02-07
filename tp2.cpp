#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <string>
#include <vector>

#define TAMANOPALABRA 256
#define COLOR_AZUL "\033[0;34m"
#define COLOR_CIAN "\033[0;36m"
#define COLOR_BLANCO "\033[0;37m"
#define COLOR_ROJO "\033[31m"

using namespace std;

/****************************************************************************************
 **************************************NODOS Y
 *STRUCT************************************
 ****************************************************************************************/

/**
 * @brief Clase Nodo que representa un nodo genérico para una estructura de
 * datos.
 *
 * @tparam T Tipo de dato almacenado en el nodo.
 */
template <class T> class Nodo {
private:
  T dato;        ///< Dato almacenado en el nodo.
  Nodo *next;    ///< Puntero al siguiente nodo.
  Nodo *derecha; ///< Puntero al nodo derecho (para estructuras como árboles).
  Nodo *
      izquierda; ///< Puntero al nodo izquierdo (para estructuras como árboles).
  int contador;  ///< Contador de referencias o usos del nodo.

public:
  Nodo() {
    next = NULL;
    contador = 0;
  };
  Nodo(T a) {
    dato = a;
    next = NULL;
    contador = 0;
  };
  int get_contador(void) { return contador; };
  void set_contador(int cont) { contador = cont; }
  void set_dato(T a) { dato = a; };
  void incrementarContador() { contador++; };
  void set_next(Nodo *n) { next = n; };
  T get_dato(void) { return dato; };
  Nodo *&get_der(void) { return derecha; };
  void set_der(Nodo *n) { derecha = n; };
  Nodo *&get_izq() { return izquierda; };
  void set_izq(Nodo *n) { izquierda = n; };
  Nodo *get_next(void) { return next; };
  bool es_vacio(void) { return next == NULL; };
};

/**
 * @brief Clase NodoArbolBinario para representar nodos de un árbol binario con
 * un nodo de lista asociado.
 *
 * @tparam T Tipo de dato del nodo de la lista asociada.
 */
template <class T> class NodoArbolBinario {
private:
  Nodo<T> *nodoLista;             ///< Puntero al nodo de lista asociado.
  NodoArbolBinario<T> *derecha;   ///< Puntero al nodo derecho.
  NodoArbolBinario<T> *izquierda; ///< Puntero al nodo izquierdo.

public:
  NodoArbolBinario()
      : nodoLista(nullptr), derecha(nullptr), izquierda(nullptr){};
  NodoArbolBinario<T> *&get_der(void) { return derecha; };
  void set_der(NodoArbolBinario<T> *n) { derecha = n; };
  NodoArbolBinario<T> *&get_izq() { return izquierda; };
  void set_izq(NodoArbolBinario<T> *n) { izquierda = n; };
  void set_nodoLista(Nodo<T> *n) { nodoLista = n; };
  Nodo<T> *get_nodoLista() { return nodoLista; };
};

/**
 * @brief Estructura para almacenar información de eficiencia durante
 * operaciones.
 */
struct InfoEficiencia {
  int comparaciones; ///< Número de comparaciones realizadas.
  int movimientos;   ///< Número de movimientos realizados.
};

/****************************************************************************************
 *****************************ARBOL BINARIO DE
 *BUSQUEDA**********************************
 ****************************************************************************************/

template <class T> class EstructuraDualColaArbol;

/**
 * @brief Clase genérica que representa un árbol binario.
 * @tparam T Tipo de dato almacenado en los nodos del árbol.
 */
template <class T> class ArbolBinario {
private:
  NodoArbolBinario<T> *raiz; ///< Puntero a la raíz del árbol.
  int profundidad;           ///< Profundidad del árbol.

  void ArbolBusq(T x, NodoArbolBinario<T> *&nuevo);
  void crearArbol(NodoArbolBinario<T> *&actual, int profundidad);
  void insertarDatos(EstructuraDualColaArbol<T> *lista, int profundidad);
  void insertardatoaux(NodoArbolBinario<T> *actual, vector<bool> posicion,
                       Nodo<T> *nuevo);
  Nodo<T> *buscarNodoAux(NodoArbolBinario<T> *actual, vector<bool> k, int pos);
  vector<bool> getBin(int k);

public:
  ArbolBinario(int profundidad, EstructuraDualColaArbol<T> *lista) {
    this->profundidad = profundidad;
    crearArbol(raiz, profundidad);
    insertarDatos(lista, profundidad);
  };
  Nodo<T> *buscarNodo(int k) { return buscarNodoAux(raiz, getBin(k), 0); };
};

/**
 * @brief Convierte un número entero a su representación binaria en un vector de
 * tamaño fijo.
 * @tparam T Tipo de dato almacenado en el árbol.
 * @param k Número entero a convertir.
 * @return Vector booleano que representa el número en binario.
 */
template <class T> vector<bool> ArbolBinario<T>::getBin(int k) {
  vector<bool> v(profundidad, false); // Iniciar el vector con 'p' bits en falso
  // Llenar el vector con los bits del número (i-1) en binario
  int num = k - 1;
  for (int j = 0; j < profundidad; j++) {
    v[profundidad - j - 1] =
        (num & (1 << j)) != 0; // Asignar cada bit de forma inversa
  }
  return v;
}

/**
 * @brief Busca un nodo en el árbol auxiliarmente.
 * @tparam T Tipo de dato almacenado en el árbol.
 * @param actual Nodo actual en el que se realiza la búsqueda.
 * @param k Vector booleano que representa la posición.
 * @param pos Posición actual en el vector.
 * @return Nodo encontrado.
 */
template <class T>
Nodo<T> *ArbolBinario<T>::buscarNodoAux(NodoArbolBinario<T> *actual,
                                        vector<bool> k, int pos) {
  if (pos >= k.size()) {
    return actual->get_nodoLista();
  }
  if (k[pos] == 1) {
    return buscarNodoAux(actual->get_der(), k, pos + 1);
  } else {
    return buscarNodoAux(actual->get_izq(), k, pos + 1);
  }
}

/**
 * @brief Inserta datos en el árbol desde una estructura dual.
 * @tparam T Tipo de dato almacenado en el árbol.
 * @param lista Estructura dual con los datos a insertar.
 * @param profundidad Profundidad del árbol.
 */
template <class T>
void ArbolBinario<T>::insertarDatos(EstructuraDualColaArbol<T> *lista,
                                    int profundidad) {
  EstructuraDualColaArbol<T> *aux = lista;

  for (int i = 1; i <= lista->get_siz(); i++) {
    vector<bool> k = getBin(i - 1);
    insertardatoaux(raiz, k, aux->nodoCabeza());
    aux = aux->resto();
  }
}

/**
 * @brief Inserta un dato auxiliarmente en el árbol.
 * @tparam T Tipo de dato almacenado en el árbol.
 * @param actual Nodo actual en el que se inserta el dato.
 * @param posicion Vector booleano que indica la posición del nodo.
 * @param nuevo Nodo a insertar.
 */
template <class T>
void ArbolBinario<T>::insertardatoaux(NodoArbolBinario<T> *actual,
                                      vector<bool> posicion, Nodo<T> *nuevo) {
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

/**
 * @brief Crea recursivamente la estructura del árbol binario.
 * @tparam T Tipo de dato almacenado en el árbol.
 * @param actual Nodo actual en la construcción.
 * @param profundidad Profundidad restante a construir.
 */
template <class T>
void ArbolBinario<T>::crearArbol(NodoArbolBinario<T> *&actual,
                                 int profundidad) {
  if (profundidad == 0) {
    return;
  }
  actual = new NodoArbolBinario<T>();
  crearArbol(actual->get_izq(), profundidad - 1);
  crearArbol(actual->get_der(), profundidad - 1);
}

/****************************************************************************************
 *****************************ESTRUCTURA DUAL
 *LISTA-ARBOL********************************
 ****************************************************************************************/

/**
 * @class EstructuraDualColaArbol
 * @brief Clase que combina una estructura de lista doble y un árbol binario
 * para almacenamiento y ordenación de datos.
 * @tparam T Tipo de los datos almacenados en la estructura.
 */
template <class T> class EstructuraDualColaArbol {
private:
  Nodo<T> *czo;              ///< Puntero al primer nodo de la lista.
  Nodo<T> *raiz;             ///< Raíz del árbol binario.
  ArbolBinario<T> *arbolbin; ///< Puntero al árbol binario asociado.
  int siz;                   ///< Número de elementos en la estructura.
  EstructuraDualColaArbol<T> *
      listainorden; ///< Lista que representa el recorrido en inorden del árbol.

  void arbolAdd(Nodo<T> *&raiz, Nodo<T> *nuevo);
  Nodo<T> *buscarNodoArbol(T d, Nodo<T> *aux);
  void impreAlfAux(Nodo<T> *aux);
  int getProfundidad(int num);
  void generarListaInorden(Nodo<T> *aux);
  void swap(Nodo<T> *nodo1, Nodo<T> *nodo2);
  InfoEficiencia QuickSortAux(Nodo<T> *cabeza, int primero, int ultimo);
  ArbolBinario<T> *getArbolbin() {
    if (arbolbin == nullptr)
      arbolbin = new ArbolBinario<T>(getProfundidad(siz), this);
    return arbolbin;
  };

public:
  EstructuraDualColaArbol() {
    czo = new Nodo<T>();
    raiz = nullptr;
    listainorden = nullptr;
    siz = 0;
    arbolbin = nullptr;
  };
  EstructuraDualColaArbol(Nodo<T> *n) {
    czo = n;
    raiz = n;
    listainorden = nullptr;
    siz = 1;
    arbolbin = nullptr;
  };
  ~EstructuraDualColaArbol() {
    delete arbolbin;
    Nodo<T> *current = czo;
    while (current != nullptr) {
      Nodo<T> *next = current->get_next();
      delete current; // Libera la memoria del nodo
      current = next;
    }
  };
  void add(T d);
  bool esvacia(void);
  void set_listainorden(EstructuraDualColaArbol<T> *list) {
    listainorden = list;
  };
  InfoEficiencia ordenarSeleccion();
  Nodo<T> *nodoCabeza(void); // retorna el dato del primer nodo
  EstructuraDualColaArbol *
  resto(void); // retorna el puntero al "resto" de la lista
  void impre();
  void impreAlf();
  EstructuraDualColaArbol<T> *getListainorden();
  int get_siz() { return siz; };
  InfoEficiencia ordenarQuickSort() { return QuickSortAux(czo, 0, siz - 1); };
};

/**
 * @brief Intercambia los datos y contadores de dos nodos.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @param nodo1 Puntero al primer nodo.
 * @param nodo2 Puntero al segundo nodo.
 *
 * Este método verifica que los nodos no sean nulos antes de proceder. Si alguno
 * de los nodos es nulo, imprime un mensaje de error. Luego, intercambia los
 * valores de los datos y contadores entre los nodos dados.
 */
template <class T>
void EstructuraDualColaArbol<T>::swap(Nodo<T> *nodo1, Nodo<T> *nodo2) {
  if (nodo1 == nullptr || nodo2 == nullptr) {
    cout << "Error en la funcion swap" << flush;
    return;
  }
  T auxdato = nodo2->get_dato();
  int auxcont = nodo2->get_contador();
  nodo2->set_contador(nodo1->get_contador());
  nodo2->set_dato(nodo1->get_dato());
  nodo1->set_dato(auxdato);
  nodo1->set_contador(auxcont);
}

/**
 * @brief Realiza el ordenamiento QuickSort en la estructura usando un árbol
 * binario.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @param cabeza Nodo inicial de la estructura.
 * @param primero Índice inicial del rango a ordenar.
 * @param ultimo Índice final del rango a ordenar.
 * @return InfoEficiencia Estructura que contiene las estadísticas de
 * eficiencia:
 * - `comparaciones`: número de comparaciones realizadas.
 * - `movimientos`: número de movimientos realizados.
 *
 * Este método utiliza un nodo pivote para dividir la estructura en subrangos
 * menores y mayores al pivote. Realiza intercambios para asegurar el orden y
 * llama recursivamente al método para ordenar los subrangos.
 *
 * Requiere que la estructura esté respaldada por un árbol binario para la
 * búsqueda de nodos.
 */
template <class T>
InfoEficiencia EstructuraDualColaArbol<T>::QuickSortAux(Nodo<T> *cabeza,
                                                        int primero,
                                                        int ultimo) {
  InfoEficiencia
      info; // tiene la variable int comparaciones y variable int movimientos
  info.comparaciones = 0;
  info.movimientos = 0;
  if (ultimo > primero) {
    // Obtén el valor del pivote
    Nodo<T> *pivot = getArbolbin()->buscarNodo(ultimo);
    int i = primero - 1;
    int j = ultimo;

    while (true) {

      while (i < siz &&
             getArbolbin()->buscarNodo(++i)->get_dato() > pivot->get_dato())
        info.comparaciones++;
      while (j > primero &&
             getArbolbin()->buscarNodo(--j)->get_dato() < pivot->get_dato())
        info.comparaciones++;

      if (++info.comparaciones && i >= j)
        break;

      // Intercambia los valores entre buscarNodo(i) y buscarNodo(j)
      swap(getArbolbin()->buscarNodo(i), getArbolbin()->buscarNodo(j));
      info.movimientos += 6;
    }

    // Intercambia el pivote con el nodo en la posición i
    swap(getArbolbin()->buscarNodo(i), pivot);
    info.movimientos += 6;
    // Llamadas recursivas para las sublistas
    InfoEficiencia infoIzq = QuickSortAux(cabeza, primero, i - 1);
    InfoEficiencia infoDer = QuickSortAux(cabeza, i + 1, ultimo);
    info.comparaciones += infoIzq.comparaciones + infoDer.comparaciones;
    info.movimientos += infoIzq.movimientos + infoDer.movimientos;
  }
  return info;
}

/**
 * @brief Ordena los elementos de la estructura usando el algoritmo de
 * selección.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @return InfoEficiencia Estructura que contiene las estadísticas de
 * eficiencia:
 * - `comparaciones`: número de comparaciones realizadas.
 * - `movimientos`: número de movimientos realizados.
 *
 * Este método implementa el algoritmo de selección, que encuentra el valor
 * mínimo y máximo en la estructura en cada iteración y los intercambia con los
 * nodos en los extremos. Recorre la estructura para ordenar los elementos en
 * función de su contador, haciendo comparaciones y realizando intercambios.
 */
template <class T>
InfoEficiencia EstructuraDualColaArbol<T>::ordenarSeleccion() {
  Nodo<T> *men;
  Nodo<T> *max;
  Nodo<T> *nodok;
  Nodo<T> *nodoj;
  InfoEficiencia info;
  info.comparaciones = 0;
  info.movimientos = 0;

  for (int i = 0; i < (siz) / 2; i++) {
    men = getArbolbin()->buscarNodo(i);
    for (int j = i + 1; j < siz - i; j++) {
      nodoj = getArbolbin()->buscarNodo(j);
      if (nodoj->get_contador() < men->get_contador()) {
        men = nodoj;
      }
      info.comparaciones++;
    }

    swap(getArbolbin()->buscarNodo(i), men);
    info.movimientos += 6;
    max = getArbolbin()->buscarNodo(siz - i - 1);

    for (int k = siz - i - 2; k > i; k--) {
      nodok = getArbolbin()->buscarNodo(k);
      if (nodok->get_contador() > max->get_contador()) {
        max = nodok;
      }
      info.comparaciones++;
    }
    swap(getArbolbin()->buscarNodo(siz - i - 1), max);
    info.movimientos += 6;
  }
  return info;
}

/**
 * @brief Calcula la profundidad de un número en la estructura.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @param num Número para calcular la profundidad.
 * @return int La profundidad del número en la estructura.
 *
 * Este método calcula la profundidad de un número dentro de una estructura
 * binaria. Utiliza una operación de multiplicación por 2 en cada iteración para
 * encontrar la potencia de 2 que sea mayor o igual al número proporcionado.
 */
template <class T> int EstructuraDualColaArbol<T>::getProfundidad(int num) {
  int prof = 0;
  int aux = 1;
  while (aux < num) {
    aux = aux * 2;
    prof++;
  }
  return prof;
}

/**
 * @brief Obtiene la lista de nodos en orden.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @return EstructuraDualColaArbol<T>* Puntero a la lista de nodos en orden.
 *
 * Este método genera y retorna una lista de nodos en orden. Si la lista aún no
 * ha sido generada, llama al método `generarListaInorden` para crearla.
 */
template <class T>
EstructuraDualColaArbol<T> *EstructuraDualColaArbol<T>::getListainorden() {
  if (listainorden == nullptr)
    generarListaInorden(raiz);
  return listainorden;
}

/**
 * @brief Agrega un nuevo nodo al árbol binario.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @param raiz Referencia al puntero de la raíz del árbol.
 * @param nuevoNodo Nodo a insertar en el árbol.
 *
 * Este método agrega un nuevo nodo al árbol binario. Si la raíz está vacía, se
 * inserta el nodo en ella. De lo contrario, se inserta recursivamente en el
 * subárbol izquierdo o derecho, dependiendo del valor del dato del nuevo nodo.
 */
template <class T>
void EstructuraDualColaArbol<T>::arbolAdd(Nodo<T> *&raiz, Nodo<T> *nuevoNodo) {
  if (!raiz) {
    nuevoNodo->set_der(nullptr);
    nuevoNodo->set_izq(nullptr);
    raiz = nuevoNodo; // Inserta el nodo en el árbol

    return;
  }
  if (nuevoNodo->get_dato() < raiz->get_dato()) {
    arbolAdd(raiz->get_izq(), nuevoNodo);
  } else {
    arbolAdd(raiz->get_der(), nuevoNodo);
  }
}

/**
 * @brief Busca un nodo en el árbol binario con el valor dado.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @param d Valor que se busca en el árbol.
 * @param aux Nodo actual en la búsqueda.
 * @return Nodo<T>* Puntero al nodo encontrado o nullptr si no se encuentra.
 *
 * Este método realiza una búsqueda recursiva en el árbol binario para encontrar
 * un nodo con el dato `d`. Si el valor de `d` es menor que el dato del nodo
 * actual, busca en el subárbol izquierdo; si es mayor, busca en el subárbol
 * derecho.
 */
template <class T>
Nodo<T> *EstructuraDualColaArbol<T>::buscarNodoArbol(T d, Nodo<T> *aux) {
  if (aux == NULL) {
    return nullptr;
  }
  if (d == aux->get_dato())
    return aux;
  if (d < aux->get_dato())
    return buscarNodoArbol(d, aux->get_izq());
  return buscarNodoArbol(d, aux->get_der());
}

/**
 * @brief Agrega un elemento a la estructura, incrementando su contador si ya
 * existe.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @param d Dato a agregar a la estructura.
 *
 * Este método busca el elemento en el árbol binario. Si no se encuentra, crea
 * un nuevo nodo y lo inserta en el árbol. Luego, se agrega el nodo a la lista
 * de cola (czo) y se incrementa el contador del nodo si ya existía en la
 * estructura.
 */
template <class T>
void EstructuraDualColaArbol<T>::add(T d) // 100
{
  Nodo<T> *aux = buscarNodoArbol(d, raiz);
  if (aux == nullptr) {
    Nodo<T> *nuevo = new Nodo<T>(d);
    arbolAdd(raiz, nuevo);
    nuevo->set_next(czo);
    czo = nuevo;
    aux = nuevo;
    siz++;
  }
  aux->incrementarContador();
}

/**
 * @brief Verifica si la estructura está vacía.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @return bool Verdadero si la estructura está vacía, falso en caso contrario.
 *
 * Este método verifica si la cola de nodos está vacía, lo cual indica si la
 * estructura está vacía.
 */
template <class T> bool EstructuraDualColaArbol<T>::esvacia(void) {
  return czo->es_vacio();
}

/**
 * @brief Obtiene el nodo cabeza de la lista de cola.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @return Nodo<T>* Puntero al nodo cabeza de la lista de cola.
 *
 * Este método devuelve el nodo cabeza de la lista de cola. Si la lista está
 * vacía, muestra un mensaje de error y devuelve un puntero nulo.
 */
template <class T> Nodo<T> *EstructuraDualColaArbol<T>::nodoCabeza(void) {
  if (this->esvacia()) {
    cout << " Error, Cabeza de lista vacia";
    return NULL;
  }
  return czo;
}

/**
 * @brief Obtiene el resto de la estructura a partir del siguiente nodo.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @return EstructuraDualColaArbol<T>* Nueva estructura que contiene el resto de
 * los nodos.
 *
 * Este método crea una nueva instancia de la estructura que contiene el resto
 * de los nodos a partir del siguiente nodo al nodo cabeza actual.
 */
template <class T>
EstructuraDualColaArbol<T> *EstructuraDualColaArbol<T>::resto(void) {
  EstructuraDualColaArbol *l = new EstructuraDualColaArbol(czo->get_next());
  return (l);
}

/**
 * @brief Imprime los elementos de la estructura en orden inverso.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 *
 * Este método imprime los elementos de la estructura en orden inverso,
 * comenzando desde el nodo cabeza y recorriendo el resto de la estructura
 * recursivamente.
 */
template <class T> void EstructuraDualColaArbol<T>::impre() {
  if (!esvacia()) {
    resto()->impre();
    cout << nodoCabeza()->get_dato() << "(" << nodoCabeza()->get_contador()
         << ")" << endl;
  }
}

/**
 * @brief Genera una lista en orden (inorden) a partir del árbol binario.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 * @param aux Nodo actual del árbol para comenzar la generación de la lista en
 * orden.
 *
 * Este método realiza un recorrido en orden (inorden) del árbol binario y
 * agrega los elementos a la lista de nodos ordenada `listainorden`. También se
 * asegura de copiar el contador de cada nodo.
 */
template <class T>
void EstructuraDualColaArbol<T>::generarListaInorden(Nodo<T> *aux) {
  if (aux != NULL) {
    if (listainorden == nullptr) {
      listainorden = new EstructuraDualColaArbol<T>(); // Suponiendo que miLista
                                                       // es de tipo Lista<T>
    }
    generarListaInorden(aux->get_izq());
    listainorden->add(aux->get_dato());
    listainorden->nodoCabeza()->set_contador(aux->get_contador());
    generarListaInorden(aux->get_der());
  }
}

/**
 * @brief Imprime los elementos de la estructura en orden alfabético.
 *
 * @tparam T Tipo de dato almacenado en los nodos.
 *
 * Este método genera la lista de nodos en orden alfabético (inorden) si aún no
 * ha sido generada y luego imprime los elementos de la lista de nodos
 * ordenados.
 */
template <class T> void EstructuraDualColaArbol<T>::impreAlf() {
  if (getListainorden() == nullptr) {
    generarListaInorden(raiz);
  }
  getListainorden()->impre();
}

/****************************************************************************************
 ***************************FUNCIONES PARA EL MAIN Y
 *MAIN********************************
 ****************************************************************************************/

/**
 * @brief Limpia la cadena y convierte sus caracteres a minúsculas.
 *
 * Esta función recorre cada carácter de la cadena y, si es alfanumérico, lo
 * convierte a minúscula y lo mueve al principio de la cadena. Al final, asegura
 * que la cadena termine correctamente con un '\0'.
 *
 * @param palabra Puntero a la cadena que será limpiada y convertida a
 * minúsculas.
 */
void limpiarYConvertirAMinusculas(char *palabra) {
  int len = strlen(palabra);
  int i = 0;

  // Recorrer la palabra y hacer ambas operaciones en el mismo ciclo
  for (int j = 0; j < len; j++) {
    if (isalnum(palabra[j])) { // Si el caracter es alfanumérico
      palabra[i++] =
          tolower(palabra[j]); // Convertir a minúsculas y moverlo al principio
    }
  }
  palabra[i] = '\0'; // Asegurarse de que la cadena termine correctamente
}

/**
 * @brief Función principal del programa.
 *
 * Este programa lee un archivo de texto, procesa las palabras para convertirlas
 * a minúsculas y las almacena en una estructura de datos. Luego, permite
 * realizar diferentes acciones como imprimir la lista de palabras, ordenarlas,
 * leer otro archivo o finalizar el programa.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Arreglo de cadenas de caracteres que contienen los argumentos de
 * línea de comandos.
 *
 * @return Código de salida del programa.
 */
int main(int argc, char *argv[]) {
  char *linea = new char[TAMANOPALABRA];
  char *carpeta = new char[TAMANOPALABRA];
  string aux = "texts/";
  strcpy(carpeta, aux.c_str());
  EstructuraDualColaArbol<string> *lista =
      new EstructuraDualColaArbol<string>();
  FILE *doc;
  char
      buffer[TAMANOPALABRA]; // Buffer para almacenar temporalmente las palabras
  while (true) {
    if (argc > 1) {
      linea = argv[1];
    }
    if (linea[0] == '\0') {
      string aux = "texto.txt";
      strcpy(linea, aux.c_str());
    }
    doc = fopen(strcat(carpeta, linea), "r");
    if (doc == NULL) {
      cout << "Error al abrir el archivo." << endl;
      return 1;
    }
    while (fscanf(doc, "%255s", buffer) != EOF) { // Leer palabra por palabra
      limpiarYConvertirAMinusculas(buffer);
      lista->add(buffer);
    }
    fclose(doc);
    bool nuevoTexto = false;
    while (true) {
      int x;
      if (nuevoTexto) {
        nuevoTexto = false;
        break;
      }
      cout << COLOR_AZUL
           << "Ingrese el numero correspondiente a la accion que desea realizar"
           << endl;
      cout << COLOR_ROJO<<"*"<<COLOR_CIAN<<"Digite 1 para imprimir la lista.";
      cout << endl
           <<COLOR_ROJO<<"*"<<COLOR_CIAN<<"Digite 2 para imprimir la lista alfabeticamente usando busqueda "
              "por arbol";
      cout << endl
           <<COLOR_ROJO<<"*"<<COLOR_CIAN<< "Digite 3 para ordenar la lista almacenada, ordenada por "
              "cantidad de apariciones de las palabras usando algoritmo seleccion";
      cout << endl
           << COLOR_ROJO<<"*"<<COLOR_CIAN<<"Digite 4 para ordenar la lista almacenada por sus palabras en "
              "orden alfabetico usando algoritmo quicksort.";
      cout << endl<< COLOR_ROJO<<"*"<<COLOR_CIAN<<"digite 5 leer otro archivo de texto.";
      cout << endl
           << COLOR_ROJO<<"*"<<COLOR_CIAN<<"Digite 6 para visualizar el listado de textos posibles a "
              "analizar.";
      cout << endl
           <<COLOR_ROJO<<"*"<<COLOR_CIAN<< "Digite 7 para finalizar el programa." << endl
           << COLOR_BLANCO;
      cin >> x;
      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Descarta la entrada no válida
        cout << "Entrada no válida. Por favor, introduce un número." << endl;
        continue;
      }
      cout << endl;
      switch (x) {
      case 1:
        lista->impre();
        break;
      case 2:
        lista->impreAlf();
        break;
      case 3: {
        InfoEficiencia info = lista->ordenarSeleccion();
        lista->impre();
        cout << "El algoritmo de seleccion realizo " << info.comparaciones
             << " comparaciones y " << info.movimientos << " movimientos"
             << endl;
        lista->set_listainorden(nullptr);
      } break;
      case 4: {
        InfoEficiencia info = lista->ordenarQuickSort();
        lista->impre();
        cout << "El algoritmo QuickSort realizo " << info.comparaciones
             << " comparaciones y " << info.movimientos << " movimientos"
             << endl;
        lista->set_listainorden(nullptr);
      } break;
      case 5:
        cout << "Ingrese el nombre del archivo de texto que quiera analizar"
             << endl;
        cin >> linea;
        nuevoTexto = true;
        continue;
      case 6:
        cout << "listado de archivos de texto posible:" << endl;
        {
          FILE *pipe = popen("dir texts", "r");
          if (!pipe) {
            pipe = popen("ls texts", "r");

            if (!pipe) {
              cerr << "No se pudo ejecutar el comando.\n";
              delete lista;
              delete[] linea;
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
        delete lista;
        delete[] linea;
        return EXIT_SUCCESS;
        break;
      default:
        cout << "El valor ingresado no corresponde a un numero valido" << endl;
        continue;
        break;
      }
    }
    string aux = "texts/";
    strcpy(carpeta, aux.c_str());
    delete lista;
    lista = new EstructuraDualColaArbol<string>();
  }
}