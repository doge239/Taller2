#include "MatrizDispersa.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <string>

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cout << "Error: Por favor ingrese un número válido." << endl;
            limpiarBuffer();
        } else {
            limpiarBuffer();
            return valor;
        }
    }
}

void mostrarMenu() {
    cout << "\n---- MENU MATRIZ DISPERSA ----" << endl;
    cout << "1. Insertar elemento" << endl;
    cout << "2. Obtener elemento" << endl;
    cout << "3. Eliminar elemento" << endl;
    cout << "4. Mostrar valores almacenados" << endl;
    cout << "5. Calcular densidad" << endl;
    cout << "6. Multiplicar con otra matriz" << endl;
    cout << "7. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

// Funcion para crear matriz B
void crearMatrizSecundariaMismoPatron(const MatrizDispersa& matrizA, MatrizDispersa& matrizB) {
    matrizB = MatrizDispersa(); // Limpiar matriz
    
    // Obtener dimensiones de A
    int maxX, maxY;
    matrizA.obtenerDimensiones(maxX, maxY);
    
    if (maxX == -1 || maxY == -1) {
        return; // Matriz A vacía
    }
    
    int filas = maxX + 1;
    int columnas = maxY + 1;
    
    cout << "Creando matriz B con mismo patron " << filas << "x" << columnas << endl;
    
    // Para cada posible posicion en A, si A tiene un elemento ahi, B también tendra uno
    for (int x = 0; x < filas; x++) {
        for (int y = 0; y < columnas; y++) {
            // Si A tiene un elemento en (x,y), entonces B tambien tendra uno
            if (matrizA.get(x, y) != 0) {
                int valor = rand() % 9 + 1; // Valor aleatorio entre 1 y 9
                matrizB.add(valor, x, y);
                cout << "Agregado en B(" << x << "," << y << "): " << valor << endl;
            }
        }
    }
}

int main() {
    srand(time(0));
    
    int opcion;
    MatrizDispersa matrizPrincipal;
    MatrizDispersa matrizSecundaria;
    
    cout << "Sistema de Matriz Dispersa - Inicializado correctamente" << endl;
    
    do {
        mostrarMenu();
        opcion = leerEntero("");
        
        switch(opcion) {
            case 1: {
                int valor = leerEntero("Ingrese valor: ");
                int x = leerEntero("Ingrese coordenada X: ");
                int y = leerEntero("Ingrese coordenada Y: ");
                matrizPrincipal.add(valor, x, y);
                break;
            }
            case 2: {
                int x = leerEntero("Ingrese coordenada X: ");
                int y = leerEntero("Ingrese coordenada Y: ");
                int resultado = matrizPrincipal.get(x, y);
                cout << "Valor en (" << x << "," << y << "): " << resultado << endl;
                break;
            }
            case 3: {
                int x = leerEntero("Ingrese coordenada X: ");
                int y = leerEntero("Ingrese coordenada Y: ");
                matrizPrincipal.remove(x, y);
                break;
            }
            case 4:
                matrizPrincipal.valoresAlmacenados();
                break;
            case 5:
                cout << "Densidad: " << matrizPrincipal.densidadMatriz() << "%" << endl;
                break;
            case 6: {
                // Verificar si la matriz principal tiene elementos
                cout << "Matriz principal actual:" << endl;
                matrizPrincipal.valoresAlmacenados();
                
                // Obtener dimensiones reales
                int maxX, maxY;
                matrizPrincipal.obtenerDimensiones(maxX, maxY);
                
                if (maxX == -1 || maxY == -1) {
                    cout << "La matriz principal esta vacia. No se puede multiplicar." << endl;
                    cout << "Agregue elementos primero usando la opcion 1." << endl;
                    break;
                }
                
                int filasA = maxX + 1;
                int columnasA = maxY + 1;
                
                cout << "Dimensiones de matriz A: " << filasA << "x" << columnasA << endl;
                
                // Crear matriz B con el MISMO PATRON que A
                crearMatrizSecundariaMismoPatron(matrizPrincipal, matrizSecundaria);
                
                cout << "Matriz secundaria generada:" << endl;
                matrizSecundaria.valoresAlmacenados();
                
                cout << "Realizando multiplicacion..." << endl;
                MatrizDispersa* resultado = matrizPrincipal.multiplicarMatriz(&matrizSecundaria);
                cout << "Resultado de la multiplicacion:" << endl;
                resultado->valoresAlmacenados();
                delete resultado;
                break;
            }
            case 7:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
        
    } while (opcion != 7);
    
    return 0;
}