#include "Nodo.h"

Nodo::Nodo(int val, int x, int y)  // Inicializador
    : valor(val), coordenadaX(x), coordenadaY(y), 
      siguiente(nullptr), anterior(nullptr) { // Validar coordenadas
    
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Las coordenadas no pueden ser negativas");
    }
}

Nodo::~Nodo() { // Destructor de clase Nodo
    siguiente = nullptr;
    anterior = nullptr;
}

bool Nodo::estaEnPosicion(int x, int y) const { // Verificar si el nodo esta en la posicion dada
    return (coordenadaX == x && coordenadaY == y);
}