#include "Nodo.h"

Nodo::Nodo(int val, int coordenadaX, int coordenadaY) // Constructor de posicion con valor
    : valor(val), coordenadaX(coordenadaX), coordenadaY(coordenadaY), // Inicializar punteros
      siguiente(nullptr), anterior(nullptr) { 
    


    // Validaciones básicas
    if (coordenadaX < 0 || coordenadaY < 0) {
        throw std::invalid_argument("Las coordenadas no pueden ser negativas"); // Manejo de error simple
    }
}

Nodo::~Nodo() {
    // Limpiar referencias para seguridad
    siguiente = nullptr;
    anterior = nullptr;
}

// Método para verificar si está en una posición específica

bool Nodo::estaEnPosicion(int coordenadaX, int coordenadaY) const {
    return (coordenadaX == coordenadaX && coordenadaY == coordenadaY);
}