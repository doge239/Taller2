#pragma once
#include "Nodo.h"

class MatrizDispersa {
private:
    Nodo* start;  // Puntero al inicio de la lista

public:
    MatrizDispersa();
    void add(int value, int xPos, int yPos);
    int get(int xPos, int yPos);
    void remove(int xPos, int yPos);
    void valoresAlmacenados();
    int densidadMatriz();
    MatrizDispersa* multiplicarMatriz(MatrizDispersa* second);
    ~MatrizDispersa();
    
    // Constructor de copia y operador de asignación (Rule of Three)
    MatrizDispersa(const MatrizDispersa& otra);
    MatrizDispersa& duplicarMatriz(const MatrizDispersa& otra);
};