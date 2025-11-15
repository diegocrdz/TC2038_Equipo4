#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
Algoritmo de Agente Viajero con Branch and Bound en C++
Equipo:
- Aquiba Yudah Benarroch Bittán, A01783710
- Diego Córdova Rodríguez, A01781166
- Lorena Estefanía Chewtat Torres, A01785378
*/

/*
Función recursiva del agente viajero para explorar vecinos con branch and bound
Explora las ramas e ignora las que no cumplan con el mejor costo que se ha encontrado

Actualiza el mejor costo y camino si encuentra una mejor solución
*/
void explorarVecinos(
    vector<vector<int>>& m,
    vector<bool>& visitado,
    vector<int>& stack,
    int costoActual,
    int nodoActual,
    int nivel,
    int inicio,
    int& mejorCosto,
    vector<int>& mejorCamino) {
    
    // Si estamos en el último nivel, revisar que el costo total sea mejor
    if (nivel == m.size()) {
        // Incrementar el costo para regresar al nodo inicial
        int costoTotal = costoActual + m[nodoActual][inicio];
        
        // Si el costo es mejor, actualizar mejor solución
        if (costoTotal < mejorCosto) {
            mejorCosto = costoTotal;
            mejorCamino = stack;
            mejorCamino.push_back(inicio); // Agrega el nodo inicial al recorrido
        }
        return;
    }
    
    // Mientras no estemos en el último nivel, explorar nodos no visitados
    for (int i = 0; i < m.size(); i++) {

        // Si el nodo no ha sido visitado y tiene conexión a otro nodo
        if (!visitado[i] && m[nodoActual][i] != 0) {

            // Obtener el costo hacia el nuevo nodo
            int nuevoCosto = costoActual + m[nodoActual][i];
            
            // Si el costo es menor al mejor costo, explorar esta rama
            if (nuevoCosto < mejorCosto) {
                // Marca el nodo como visitado y explora sus vecinos
                visitado[i] = true;
                stack.push_back(i);
                explorarVecinos(m, visitado, stack, nuevoCosto, i, nivel + 1, inicio, mejorCosto, mejorCamino);

                // Backtracking
                // Después de hacer todo el proceso, regresa un nodo antes y lo marca como no visitado
                stack.pop_back();
                visitado[i] = false; 
            }
        }
    }
}

/*
Función principal del agente viajero

De acuerdo a un nodo inicial, recorre todos los nodos con el
menor costo posible haciendo un ciclo hamiltoniano

Entrada:
- m: matriz de adyacencia
- inicio: nodo inicial

Salida:
- Imprime el recorrido óptimo y su costo
*/
void agenteViajero(vector<vector<int>> m, int inicio) {

    int n = m.size(); // Número de nodos
    int mejorCosto = INT_MAX; // Mejor costo obtenido
    vector<int> mejorCamino = {}; // Mejor camino obtenido
    vector<bool> visitado(n, false); // Lista para saber si ya se visitó un nodo
    vector<int> stack; // Almacena el camino actual
    
    // Visitar el primer nodo
    visitado[inicio] = true;
    stack.push_back(inicio);
    
    // Explorar vecinos desde el nodo inicial con branch and bound
    explorarVecinos(m, visitado, stack, 0, inicio, 1, inicio, mejorCosto, mejorCamino);
    
    // Imprimir resultados
    cout << "Nodo inicial: " << inicio << endl;
    
    // Imprimir recorrido con su costo
    cout << "Recorrido: ";
    for (int i = 0; i < mejorCamino.size(); i++) {
        cout << mejorCamino[i] << " ";
    }
    cout << endl;
    
    // Imprimir recorrido inverso con su costo
    cout << "Recorrido inverso: ";
    for (int i = mejorCamino.size()-1; i >= 0; i--) {
        cout << mejorCamino[i] << " ";
    }
    cout << endl;
    cout << "Costo total: " << mejorCosto << endl;
    cout << endl;
}

int main() {

    // Matriz de adyacencia
    vector<vector<int>> m = {
        {0, 259, 177, 611, 504, 899, 827, 971, 969, 1007},
        {259, 0, 277, 546, 492, 906, 912, 1045, 1049, 1110},
        {177, 277, 0, 440, 327, 723, 670, 811, 830, 859},
        {611, 546, 440, 0, 139, 385, 507, 597, 612, 702},
        {504, 492, 327, 139, 0, 415, 453, 569, 578, 655},
        {899, 906, 723, 385, 415, 0, 274, 270, 296, 401},
        {827, 912, 670, 507, 453, 274, 0, 146, 142, 202},
        {971, 1045, 811, 597, 569, 270, 146, 0, 28, 131},
        {969, 1049, 830, 612, 578, 296, 142, 28, 0, 105},
        {1007, 1110, 859, 702, 655, 401, 202, 131, 105, 0}
    };

    // Índice de ciudades
    vector<string> ciudades = {"Y", "CH", "CA", "TG", "V", "O", "X", "P", "T", "PA"};

    // Imprimir la ciudad y su índice 
    cout << "Índice de ciudades:" << endl;
    for (int i = 0; i < ciudades.size(); i++) {
        cout << i << ": " << ciudades[i] << endl;
    }
    cout << endl;

    // Agente viajero
    agenteViajero(m, 6); // Iniciando desde Xalapa
    agenteViajero(m, 0); // Iniciando desde Yucatán

    return 0;
}