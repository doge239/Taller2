#pragma once
#include <stdexcept>    // Para manejo de excepciones

class Nodo {             // Clase Nodo 
public:
    int valor;           // Valor x,y almacenado
    int coordenadaX;     // Coordenada de X
    int coordenadaY;     // Coordenada de Y
    Nodo* siguiente;     // Puntero al siguiente nodo
    Nodo* anterior;      // Puntero al nodo anterior
    
    // Constructor de posicion con valor
    Nodo(int valor, int coordenadaX, int coordenadaY);
    
    // Destructor del nodo
    ~Nodo();
    
    // Método para verificar si está en una posición específica
    bool estaEnPosicion(int coordenadaX, int coordenadaY) const;
    
    // Prevenir copia no deseada para evitar errores
    Nodo(const Nodo&) = delete;
    Nodo& operator=(const Nodo&) = delete;
};