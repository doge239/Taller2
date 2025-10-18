#include "MatrizDispersa.h"
#include <iostream>
#include <stdexcept>

using namespace std;


Nodo* buscarNodo(Nodo* inicio, int posX, int posY) {
    Nodo* actual = inicio;
    while (actual != nullptr) {
        if (actual->estaEnPosicion(posX, posY)) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr; // No se encontró el nodo
}

int contarElementos(Nodo* inicio) {
    int contador = 0;
    Nodo* actual = inicio;
    while (actual != 0) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

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

void insertarOrdenado(Nodo* &inicio, Nodo* nuevoNodo) {
    if (inicio == nullptr) {
        inicio = nuevoNodo;
        return;
    }
    
    // Caso especial: insertar al inicio
    if (nuevoNodo->coordenadaY < inicio->coordenadaY || 
        (nuevoNodo->coordenadaY == inicio->coordenadaY && 
         nuevoNodo->coordenadaX < inicio->coordenadaX)) {
        nuevoNodo->siguiente = inicio;
        inicio->anterior = nuevoNodo;
        inicio = nuevoNodo;
        return;
    }
    
    // Buscar posición de inserción
    Nodo* actual = inicio;
    while (actual->siguiente != nullptr) {
        if (nuevoNodo->coordenadaY < actual->siguiente->coordenadaY || 
            (nuevoNodo->coordenadaY == actual->siguiente->coordenadaY && 
             nuevoNodo->coordenadaX < actual->siguiente->coordenadaX)) {
            break;
        }
        actual = actual->siguiente;
    }
    
    // Insertar después de 'actual'
    nuevoNodo->siguiente = actual->siguiente;
    nuevoNodo->anterior = actual;
    if (actual->siguiente != nullptr) {
        actual->siguiente->anterior = nuevoNodo;
    }
    actual->siguiente = nuevoNodo;
}

void limpiarLista(Nodo* &inicio) {
    Nodo* actual = inicio;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    inicio = nullptr;
}



MatrizDispersa::MatrizDispersa() : start(nullptr) {}

MatrizDispersa::MatrizDispersa(const MatrizDispersa& otra) : start(nullptr) {
    // Copiar todos los elementos de la otra matriz
    Nodo* actual = otra.start;
    while (actual != nullptr) {
        this->add(actual->valor, actual->coordenadaX, actual->coordenadaY);
        actual = actual->siguiente;
    }
}

MatrizDispersa& MatrizDispersa::operator=(const MatrizDispersa& otra) {
    if (this != &otra) {
        // Limpiar contenido actual
        limpiarLista(start);
        
        // Copiar elementos de la otra matriz
        Nodo* actual = otra.start;
        while (actual != nullptr) {
            this->add(actual->valor, actual->coordenadaX, actual->coordenadaY);
            actual = actual->siguiente;
        }
    }
    return *this;
}

MatrizDispersa::~MatrizDispersa() {
    limpiarLista(start);
}

void MatrizDispersa::add(int value, int xPos, int yPos) {
    if (xPos < 0 || yPos < 0) {
        return;
    }
    
    if (value == 0) {
        remove(xPos, yPos);
        return;
    }
    
    Nodo* nodoExistente = buscarNodo(start, xPos, yPos);
    
    if (nodoExistente != nullptr) {
        nodoExistente->valor = value;
    } else {
        Nodo* nuevoNodo = new Nodo(value, xPos, yPos);
        insertarOrdenado(start, nuevoNodo);
    }
}

int MatrizDispersa::get(int xPos, int yPos) {
    // Validar coordenadas - si son negativas, retornar 0 inmediatamente
    if (xPos < 0 || yPos < 0) {
        return 0;
    }
    
    // Buscar el nodo en la posición especificada
    Nodo* nodo = buscarNodo(start, xPos, yPos);
    
    // Si se encontró el nodo, retornar su valor
    // Si no se encontró, retornar 0 (como especifica el PDF)
    if (nodo != nullptr) {
        return nodo->valor;
    } else {
        return 0; // No hay datos en dicha coordenada
    }
}

// Primera parte de clase MatrizDispersa





