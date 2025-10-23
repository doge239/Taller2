#include "MatrizDispersa.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct ResultadoPrueba {
    int tamano;
    string operacion;
    string densidad;
    double tiempo;
    string arquitectura;
};

vector<ResultadoPrueba> resultados;

void guardarResultado(int tamano, string operacion, string densidad, double tiempo, string arquitectura) {
    ResultadoPrueba r;
    r.tamano = tamano;
    r.operacion = operacion;
    r.densidad = densidad;
    r.tiempo = tiempo;
    r.arquitectura = arquitectura;
    resultados.push_back(r);
}

void pruebaInsercion(int n, int rango, string densidad, string arquitectura) {
    MatrizDispersa matriz;
    clock_t start = clock();
    
    for (int i = 0; i < n; i++) {
        int x = rand() % rango;
        int y = rand() % rango;
        int valor = rand() % 100 + 1;
        matriz.add(valor, x, y);
    }
    
    clock_t end = clock();
    double tiempo = double(end - start) / CLOCKS_PER_SEC;
    
    guardarResultado(n, "Insercion", densidad, tiempo, arquitectura);
    cout << "  Insercion " << densidad << " densidad: " << tiempo << " segundos";
    cout << " (Densidad real: " << matriz.densidadMatriz() << "%)" << endl;
}

void pruebaBusqueda(int n, int rango, string densidad, string arquitectura) {
    MatrizDispersa matriz;
    
    // Llenar matriz primero
    for (int i = 0; i < n; i++) {
        int x = rand() % rango;
        int y = rand() % rango;
        int valor = rand() % 100 + 1;
        matriz.add(valor, x, y);
    }
    
    // Medir busquedas
    clock_t start = clock();
    for (int i = 0; i < n; i++) {
        int x = rand() % rango;
        int y = rand() % rango;
        matriz.get(x, y);
    }
    clock_t end = clock();
    
    double tiempo = double(end - start) / CLOCKS_PER_SEC;
    guardarResultado(n, "Busqueda", densidad, tiempo, arquitectura);
    cout << "  Busqueda " << densidad << " densidad: " << tiempo << " segundos" << endl;
}

void pruebaMultiplicacion(int n, string arquitectura) {
    MatrizDispersa matrizA, matrizB;
    
    // Crear matriz A (20 x 30)
    for (int i = 0; i < n; i++) {
        int x = rand() % 20;
        int y = rand() % 30;
        int valor = rand() % 10 + 1;
        matrizA.add(valor, x, y);
    }
    
    // Crear matriz B (30 x 15) - compatible con A
    for (int i = 0; i < n; i++) {
        int x = rand() % 30;
        int y = rand() % 15;
        int valor = rand() % 10 + 1;
        matrizB.add(valor, x, y);
    }
    
    clock_t start = clock();
    MatrizDispersa* resultado = matrizA.multiplicarMatriz(&matrizB);
    clock_t end = clock();
    
    double tiempo = double(end - start) / CLOCKS_PER_SEC;
    guardarResultado(n, "Multiplicacion", "Media", tiempo, arquitectura);
    cout << "  Multiplicacion: " << tiempo << " segundos" << endl;
    
    delete resultado;
}

void ejecutarPruebasParaArquitectura(string arquitectura) {
    vector<int> sizes = {50, 250, 500, 1000, 5000};
    
    cout << "\n=== EJECUTANDO PRUEBAS PARA " << arquitectura << " ===" << endl;
    
    for (int n : sizes) {
        cout << "\n--- Tamano: " << n << " elementos ---" << endl;
        
        // Pruebas con baja densidad (<40%)
        pruebaInsercion(n, n * 10, "Baja", arquitectura);
        pruebaBusqueda(n, n * 10, "Baja", arquitectura);
        
        // Pruebas con alta densidad (>70%)
        pruebaInsercion(n, max(5, n / 10), "Alta", arquitectura);
        pruebaBusqueda(n, max(5, n / 10), "Alta", arquitectura);
        
        // Prueba de multiplicacion (solo para tamanos mayores)
        if (n >= 500) {
            pruebaMultiplicacion(n, arquitectura);
        }
    }
}

void generarArchivoCSV() {
    ofstream archivo("resultados_rendimiento.csv");
    
    // Encabezado del CSV
    archivo << "Arquitectura,Tamano,Operacion,Densidad,Tiempo_segundos" << endl;
    
    for (const auto& resultado : resultados) {
        archivo << resultado.arquitectura << ","
                << resultado.tamano << ","
                << resultado.operacion << ","
                << resultado.densidad << ","
                << resultado.tiempo << endl;
    }
    
    archivo.close();
    cout << "\nArchivo CSV generado: resultados_rendimiento.csv" << endl;
}

void generarReporteTexto() {
    ofstream archivo("reporte_rendimiento.txt");
    
    archivo << "REPORTE DE RENDIMIENTO - MATRIZ DISPERSA" << endl;
    archivo << "+++++++++++++++++++++++++++++++++++++++++" << endl << endl;
    
    for (const string& arquitectura : {"Intel", "AMD", "Apple"}) {
        archivo << "ARQUITECTURA: " << arquitectura << endl;
        archivo << "-------------------" << endl;
        
        for (int tamano : {50, 250, 500, 1000, 5000}) {
            archivo << "Tamano " << tamano << " elementos:" << endl;
            
            for (const string& operacion : {"Insercion", "Busqueda", "Multiplicacion"}) {
                for (const string& densidad : {"Baja", "Alta", "Media"}) {
                    for (const auto& r : resultados) {
                        if (r.arquitectura == arquitectura && 
                            r.tamano == tamano && 
                            r.operacion == operacion && 
                            r.densidad == densidad) {
                            archivo << "  " << operacion << " (" << densidad << "): " 
                                   << r.tiempo << " segundos" << endl;
                        }
                    }
                }
            }
            archivo << endl;
        }
        archivo << endl;
    }
    
    archivo.close();
    cout << "Reporte de texto generado: reporte_rendimiento.txt" << endl;
}

void mostrarResumenConsola() {
    cout << "\n=== RESUMEN EJECUTADO EN ESTA MAQUINA ===" << endl;
    
    // Asumir que la arquitectura actual es Intel (cambiar segun tu PC)
    string arquitecturaActual = "Intel"; // CAMBIAR ESTO según tu procesador
    
    cout << "Arquitectura: " << arquitecturaActual << endl;
    cout << "Tamano\tInsercion(Baja)\tInsercion(Alta)\tBusqueda(Baja)\tBusqueda(Alta)" << endl;
    cout << "------\t---------------\t---------------\t---------------\t--------------" << endl;
    
    for (int tamano : {50, 250, 500, 1000, 5000}) {
        double insBaja = 0, insAlta = 0, busBaja = 0, busAlta = 0;
        
        for (const auto& r : resultados) {
            if (r.arquitectura == arquitecturaActual && r.tamano == tamano) {
                if (r.operacion == "Insercion" && r.densidad == "Baja") insBaja = r.tiempo;
                if (r.operacion == "Insercion" && r.densidad == "Alta") insAlta = r.tiempo;
                if (r.operacion == "Busqueda" && r.densidad == "Baja") busBaja = r.tiempo;
                if (r.operacion == "Busqueda" && r.densidad == "Alta") busAlta = r.tiempo;
            }
        }
        
        cout << tamano << "\t" << insBaja << "\t\t" << insAlta << "\t\t" 
             << busBaja << "\t\t" << busAlta << endl;
    }
}

int main() {
    cout << "+++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "    PRUEBA INFORME - MATRIZ DISPERSA" << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++" << endl;
    
    srand(time(0));
    
    // IMPORTANTE: Cambiar este valor según el procesador donde ejecutes
    string arquitecturaActual;
    
    cout << "Seleccione la arquitectura del procesador:" << endl;
    cout << "1. Intel" << endl;
    cout << "2. AMD" << endl;
    cout << "3. Apple Silicon" << endl;
    cout << "Opcion: ";
    
    int opcion;
    cin >> opcion;
    
    switch(opcion) {
        case 1:
            arquitecturaActual = "Intel";
            break;
        case 2:
            arquitecturaActual = "AMD";
            break;
        case 3:
            arquitecturaActual = "Apple";
            break;
        default:
            arquitecturaActual = "Intel";
            cout << "Usando Intel por defecto" << endl;
    }
    
    cout << "\nEjecutando pruebas para: " << arquitecturaActual << endl;
    cout << "Esto puede tomar algunos segundos..." << endl;
    
    ejecutarPruebasParaArquitectura(arquitecturaActual);
    
    generarArchivoCSV();
    generarReporteTexto();
    mostrarResumenConsola();
    
    cout << "\n+++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "           PROCESO COMPLETADO" << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++" << endl;
    
    return 0;
}
