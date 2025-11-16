#include <iostream>
#include <vector>
#include <climits>

using namespace std;

/*
Algoritmo del problema de asignación de trabajos con Branch and Bound
Equipo:
- Aquiba Yudah Benarroch Bittán, A01783710
- Diego Córdova Rodríguez, A01781166
- Lorena Estefanía Chewtat Torres, A01785378
*/

/*
Función recursiva del problema de asignación para explorar vecinos con branch and bound
Explora las ramas e ignora las que no cumplan con el mejor costo que se ha encontrado
*/
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

/*
Función principal del problema de asignación de trabajos

De acuerdo a una tabla de costos y un orden de asignación, asigna trabajos a trabajadores
con el menor costo posible

Entrada:
- tabla: matriz de costos
- orden: orden en el que se asignarán los trabajos

Salida:
- Imprime la mejor asignación de trabajos y su costo total
*/
void asignarTrabajos(vector<vector<int>> tabla, vector<int> orden) {
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
    vector<int> ordenA = {0, 1, 2, 3}; // A B C D
    vector<int> ordenB = {1, 2, 3, 0}; // B C D A

    // Asignación de trabajos
    cout << "-----Empezando por A (0)-----" << endl;
    asignarTrabajos(tabla, ordenA);
    cout << "-----Empezando por B (1)-----" << endl;
    asignarTrabajos(tabla, ordenB);
}

