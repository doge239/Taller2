#pragma once
#include "Nodo.h"

class MatrizDispersa {
private:
    Nodo* inicio;

public:
    MatrizDispersa();
    MatrizDispersa(const MatrizDispersa& otra);
    MatrizDispersa& operator=(const MatrizDispersa& otra);
    
    void add(int value, int xPos, int yPos);
    int get(int xPos, int yPos) const;  
    void remove(int xPos, int yPos);
    void valoresAlmacenados() const;    
    int densidadMatriz() const;         
    void obtenerDimensiones(int& maxX, int& maxY) const;  
    MatrizDispersa* multiplicarMatriz(MatrizDispersa* second) const;  
    
    ~MatrizDispersa();
}
