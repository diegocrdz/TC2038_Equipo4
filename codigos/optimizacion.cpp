#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void explorarVecinos(
    vector<vector<int>> &tabla,
    vector<bool> &trabajoAsignado,
    vector<int> &stack,
    int costoActual,
    vector<int> orden,
    int nivel,
    int &mejorCosto,
    vector<int> &mejorAsignacion) {

    // Si ya asignamos todos los trabajadores, verificar si es mejor solución
    if (nivel == tabla.size()) {
        if (costoActual < mejorCosto) {
            mejorCosto = costoActual;
            mejorAsignacion = stack;
        }
        return;
    }

    // Seleccionar trabajador actual
    int trabajadorActual = orden[nivel];

    // Mientras no estemos en el último nivel, asignamos trabajos a cada trabajador
    for (int i = 0; i < tabla.size(); i++) {

        // Si el trabajo no ha sido asignado
        if (!trabajoAsignado[i]) {

            // Obtener el costo hacia el nuevo nodo
            int nuevoCosto = costoActual + tabla[trabajadorActual][i];

            // Si el costo es menor al mejor costo, explorar esta rama
            if (nuevoCosto < mejorCosto) {
                // Asignar el trabajo
                trabajoAsignado[i] = true;
                stack[trabajadorActual] = i; // Asignar el trabajo
                explorarVecinos(tabla, trabajoAsignado, stack, nuevoCosto, orden, nivel + 1, mejorCosto, mejorAsignacion);

                // Backtracking
                // Después de hacer todo el proceso, desasigna el trabajo para explorar caminos
                trabajoAsignado[i] = false;
                stack[trabajadorActual] = -1;
            }
        }
    }
}

// Funcion para optimizar el costo de trabajos asignados
void optimizacion(vector<vector<int>> tabla, vector<int> orden) {
    int n = tabla.size();
    vector<bool> trabajoAsignado(n, false); // Para saber si el trabajo ya fue asignado
    vector<int> stack(n, -1); // Guarda el trabajo de cada trabajador
    vector<int> mejorAsignacion(n, -1); // Guarda el mejor trabajo para cada trabajador
    int mejorCosto = INT_MAX; // Mejor costo total obtenido

    // Llamada inicial a la funcion branch and bound
    explorarVecinos(tabla, trabajoAsignado, stack, 0, orden, 0, mejorCosto, mejorAsignacion);

    // Imprimir resutlados
    cout << "Mejor Asignación de trabajos: " << endl;
    for (int i = 0; i < mejorAsignacion.size(); i++) {
        cout << "Trabajador: " << i << " Trabajo: " << mejorAsignacion[i] << " Costo: " << tabla[i][mejorAsignacion[i]] << endl; 
    }
    cout << "Costo: " << mejorCosto << endl;
}

int main () {

    // Matriz de trabajos con costos
    // Filas son trabajadores, columnas trabajos
    
    vector<vector<int>> tabla = {
        {5, 9, 10, 3},
        {2, 6, 12, 1},
        {7, 4, 4, 8},
        {11, 16, 2, 14}
    };
    

    // Orden en el que se asignarán los trabajos

    // A B C D
    vector<int> ordenA = {0, 1, 2, 3};

    // B C D A
    vector<int> ordenB = {1, 2, 3, 0};

    // Asignación de trabajos
    cout << "-----Empezando por A-----" << endl;
    optimizacion(tabla, ordenA);
    cout << "-----Empezando por B-----" << endl;
    optimizacion(tabla, ordenB);
}

