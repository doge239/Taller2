#include "MatrizDispersa.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Funcion auxiliar para buscar un nodo
Nodo* buscarNodo(Nodo* inicio, int posX, int posY) {
    Nodo* actual = inicio;
    while (actual != nullptr) {
        if (actual->coordenadaX == posX && actual->coordenadaY == posY) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Funcion auxiliar para contar elementos
int contarElementos(Nodo* inicio) {
    int contador = 0;
    Nodo* actual = inicio;
    while (actual != nullptr) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

// Funcion auxiliar para encontrar dimensiones máximas
void encontrarDimensionesMaximas(Nodo* inicio, int& maxX, int& maxY) {
    maxX = -1;
    maxY = -1;
    Nodo* actual = inicio;
    while (actual != nullptr) {
        if (actual->coordenadaX > maxX) maxX = actual->coordenadaX;
        if (actual->coordenadaY > maxY) maxY = actual->coordenadaY;
        actual = actual->siguiente;
    }
}

// Funcion auxiliar para insertar ordenado
void insertarOrdenado(Nodo* &inicio, Nodo* nuevoNodo) {
    if (inicio == nullptr) {
        inicio = nuevoNodo;
        return;
    }
    
    // Insertar al inicio si es necesario
    if (nuevoNodo->coordenadaY < inicio->coordenadaY || 
        (nuevoNodo->coordenadaY == inicio->coordenadaY && 
         nuevoNodo->coordenadaX < inicio->coordenadaX)) {
        nuevoNodo->siguiente = inicio;
        inicio->anterior = nuevoNodo;
        inicio = nuevoNodo;
        return;
    }
    
    // Buscar posicion de insercion
    Nodo* actual = inicio;
    while (actual->siguiente != nullptr) {
        if (nuevoNodo->coordenadaY < actual->siguiente->coordenadaY || 
            (nuevoNodo->coordenadaY == actual->siguiente->coordenadaY && 
             nuevoNodo->coordenadaX < actual->siguiente->coordenadaX)) {
            break;
        }
        actual = actual->siguiente;
    }
    
    // Insertar despues de 'actual'
    nuevoNodo->siguiente = actual->siguiente;
    nuevoNodo->anterior = actual;
    if (actual->siguiente != nullptr) {
        actual->siguiente->anterior = nuevoNodo;
    }
    actual->siguiente = nuevoNodo;
}

// Funcion auxiliar para limpiar la lista
void limpiarLista(Nodo* &inicio) {
    Nodo* actual = inicio;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    inicio = nullptr;
}

// Implementacion de metodos publicos
MatrizDispersa::MatrizDispersa() : inicio(nullptr) {}

MatrizDispersa::MatrizDispersa(const MatrizDispersa& otra) : inicio(nullptr) {
    Nodo* actual = otra.inicio;
    while (actual != nullptr) {
        this->add(actual->valor, actual->coordenadaX, actual->coordenadaY);
        actual = actual->siguiente;
    }
}

MatrizDispersa& MatrizDispersa::operator=(const MatrizDispersa& otra) {
    if (this != &otra) {
        limpiarLista(inicio);
        Nodo* actual = otra.inicio;
        while (actual != nullptr) {
            this->add(actual->valor, actual->coordenadaX, actual->coordenadaY);
            actual = actual->siguiente;
        }
    }
    return *this;
}

MatrizDispersa::~MatrizDispersa() {
    limpiarLista(inicio);
}

void MatrizDispersa::add(int value, int xPos, int yPos) {
    if (xPos < 0 || yPos < 0) {
        cout << "Error: Coordenadas no pueden ser negativas" << endl;
        return;
    }
    
    // Buscar si ya existe un nodo en esa posicion
    Nodo* nodoExistente = buscarNodo(inicio, xPos, yPos);
    
    if (nodoExistente != nullptr) {
        // Nodo existe, actualizar valor
        if (value == 0) {
            // Si el nuevo valor es 0, eliminar el nodo
            remove(xPos, yPos);
        } else {
            // Actualizar el valor existente
            cout << "Actualizando valor en (" << xPos << "," << yPos << ") de " 
                 << nodoExistente->valor << " a " << value << endl;
            nodoExistente->valor = value;
        }
    } else {
        // Nodo no existe, crear nuevo solo si valor no es 0
        if (value != 0) {
            Nodo* nuevoNodo = new Nodo(value, xPos, yPos);
            insertarOrdenado(inicio, nuevoNodo);
            cout << "Nuevo elemento agregado en (" << xPos << "," << yPos << "): " << value << endl;
        } else {
            cout << "No se agrega elemento con valor 0 en (" << xPos << "," << yPos << ")" << endl;
        }
    }
}

int MatrizDispersa::get(int xPos, int yPos) const {
    if (xPos < 0 || yPos < 0) {
        return 0;
    }
    
    Nodo* nodo = buscarNodo(inicio, xPos, yPos);
    if (nodo != nullptr) {
        return nodo->valor;
    }
    return 0;
}

void MatrizDispersa::remove(int xPos, int yPos) {
    if (xPos < 0 || yPos < 0) {
        return;
    }
    
    Nodo* nodoAEliminar = buscarNodo(inicio, xPos, yPos);
    
    if (nodoAEliminar != nullptr) {
        // Reenlazar los nodos adyacentes
        if (nodoAEliminar->anterior != nullptr) {
            nodoAEliminar->anterior->siguiente = nodoAEliminar->siguiente;
        } else {
            inicio = nodoAEliminar->siguiente;
        }
        
        if (nodoAEliminar->siguiente != nullptr) {
            nodoAEliminar->siguiente->anterior = nodoAEliminar->anterior;
        }
        
        cout << "Elemento eliminado de (" << xPos << "," << yPos << ")" << endl;
        delete nodoAEliminar;
    } else {
        cout << "No existe elemento en (" << xPos << "," << yPos << ") para eliminar" << endl;
    }
}

void MatrizDispersa::valoresAlmacenados() const {
    Nodo* actual = inicio;
    
    if (actual == nullptr) {
        cout << "La matriz no contiene elementos diferentes a cero." << endl;
        return;
    }
    
    cout << "Elementos almacenados (diferentes a 0):" << endl;
    cout << "################################################" << endl; 
    cout << "Coordenadas   | Valor" << endl;
    cout << " ###########  | ######" << endl;
    
    int contador = 0;
    while (actual != nullptr) {
        cout << "(" << actual->coordenadaX << ", " << actual->coordenadaY << ")      | " << actual->valor << endl;
        actual = actual->siguiente;
        contador++;
    }
    cout << "################################################" << endl;
    cout << "Total de elementos: " << contador << endl;
}

int MatrizDispersa::densidadMatriz() const {
    int cantidadElementos = contarElementos(inicio);
    
    if (cantidadElementos == 0) {
        return 0;
    }
    
    int maxX, maxY;
    encontrarDimensionesMaximas(inicio, maxX, maxY);
    
    // Si no hay elementos, densidad es 0
    if (maxX == -1 || maxY == -1) {
        return 0;
    }
    
    int filas = maxX + 1;
    int columnas = maxY + 1;
    int tamanoTotal = filas * columnas;
    
    if (tamanoTotal == 0) {
        return 0;
    }
    
    return (cantidadElementos * 100) / tamanoTotal;
}

void MatrizDispersa::obtenerDimensiones(int& maxX, int& maxY) const {
    maxX = -1;
    maxY = -1;
    Nodo* actual = inicio;
    
    while (actual != nullptr) {
        if (actual->coordenadaX > maxX) maxX = actual->coordenadaX;
        if (actual->coordenadaY > maxY) maxY = actual->coordenadaY;
        actual = actual->siguiente;
    }
}

MatrizDispersa* MatrizDispersa::multiplicarMatriz(MatrizDispersa* segundaMatriz) const {
    if (segundaMatriz == nullptr) {
        cout << "Error: Segunda matriz es nula" << endl;
        return new MatrizDispersa();
    }
    
    // Verificar si alguna matriz está vacía
    if (inicio == nullptr || segundaMatriz->inicio == nullptr) {
        cout << "Una de las matrices está vacía - resultado será matriz vacía" << endl;
        return new MatrizDispersa();
    }
    
    MatrizDispersa* matrizResultado = new MatrizDispersa();
    
    // Encontrar dimensiones REALES (con -1 si está vacía)
    int maxX1, maxY1, maxX2, maxY2;
    encontrarDimensionesMaximas(inicio, maxX1, maxY1);
    encontrarDimensionesMaximas(segundaMatriz->inicio, maxX2, maxY2);
    
    // Si alguna matriz realmente no tiene elementos
    if (maxX1 == -1 || maxY1 == -1 || maxX2 == -1 || maxY2 == -1) {
        cout << "Una de las matrices no tiene elementos" << endl;
        return matrizResultado;
    }
    
    // Calcular dimensiones reales
    int columnasA = maxY1 + 1;
    int filasB = maxX2 + 1;
    
    // Verificar compatibilidad
    if (columnasA != filasB) {
        cout << "Error: Matrices incompatibles para multiplicacion." << endl;
        cout << "Matriz A es " << (maxX1 + 1) << "x" << columnasA << endl;
        cout << "Matriz B es " << filasB << "x" << (maxY2 + 1) << endl;
        cout << "Columnas de A (" << columnasA << ") deben igualar filas de B (" << filasB << ")" << endl;
        return matrizResultado;
    }
    
    cout << "Multiplicando matrices..." << endl;
    cout << "Dimensiones: (" << (maxX1 + 1) << "x" << columnasA << ") x (" 
         << filasB << "x" << (maxY2 + 1) << ")" << endl;
    
    Nodo* actualPrimera = inicio;
    int operaciones = 0;
    
    while (actualPrimera != nullptr) {
        Nodo* actualSegunda = segundaMatriz->inicio;
        
        while (actualSegunda != nullptr) {
            if (actualPrimera->coordenadaY == actualSegunda->coordenadaX) {
                int producto = actualPrimera->valor * actualSegunda->valor;
                int xResultado = actualPrimera->coordenadaX;
                int yResultado = actualSegunda->coordenadaY;
                int valorActual = matrizResultado->get(xResultado, yResultado);
                matrizResultado->add(valorActual + producto, xResultado, yResultado);
                operaciones++;
            }
            actualSegunda = actualSegunda->siguiente;
        }
        actualPrimera = actualPrimera->siguiente;
    }
    
    cout << "Multiplicacion completada. Operaciones realizadas: " << operaciones << endl;
    return matrizResultado;
}