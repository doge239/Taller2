#pragma once
#include <stdexcept>

class Nodo {
public:
    int valor;  // Valor almacenado en el nodo
    int coordenadaX; // Coordenada X del nodo
    int coordenadaY; // Coordenada Y del nodo
    Nodo* siguiente; // Puntero al siguiente nodo
    Nodo* anterior; // Puntero al nodo anterior
    
    Nodo(int val, int x, int y);  // Constructor
    ~Nodo(); // Destructor
    
    bool estaEnPosicion(int x, int y) const; // Verificar si el nodo esta en la posicion dada
    
    Nodo(const Nodo&) = delete; // Deshabilitar constructor de copia
    Nodo& operator=(const Nodo&) = delete; // Deshabilitar operador de asignacion
};