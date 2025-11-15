#include <iostream>
#include <vector>

using namespace std;

/*
Función para buscar y eliminar el nodo con el menor valor f en el stack
Es utilizado en el algoritmo A* para seleccionar el siguiente nodo a explorar
en cada iteración

Entrada:
- stack: vector de pares donde cada par contiene (nodo, f)

Salida:
- par con el nodo y su valor f minimo
*/
pair<int,int> buscarEliminarMinimo(vector<pair<int,int>> &stack) {
    int indice_min = 0;
    for(int i = 1; i < stack.size(); i++) {
        if(stack[i].second < stack[indice_min].second) {
            indice_min = i;
        }
    }
    pair<int,int> nodo_min = stack[indice_min];
    stack.erase(stack.begin() + indice_min);
    return nodo_min;
}

/*
Algorimo A*
Expande todos los nodos con el menor costo, considerando que tan
lejos estamos del nodo objetivo, mediante la heurística

Entrada:
- m: matriz de adyacencia con los costos entre nodos
- h_list: vector con los valores heurísticos para cada nodo
- inicio: nodo inicial
- obj: nodo objetivo

Salida:
- Imprime el recorrido desde el nodo inicial al objetivo y el costo total
*/
void a_star(vector<vector<int>> m, vector<int>h_list, int inicio, int obj) {
    int n = m.size(); // Número de nodos
    vector<pair<int,int>> stack; // Stack de nodos por explorar
    vector<int> c_list(n, INT_MAX); // Costos acumulados
    vector<bool> visitado(n, false); // Nodos visitados

    // Vector de padres
    // Sirve para conocer el camino que se tomó al final
    vector<int> padres(n, 0);
    
    // Inicializar el stack con el nodo inicial
    stack.push_back({inicio, h_list[inicio]});
    c_list[inicio] = 0;
    
    // Mientras el stack no esté vacío
    // Explorar vecinos del nodo con menor f
    while(!stack.empty()) {

        // Buscar y eliminar el nodo con menor f
        pair<int,int> actual = buscarEliminarMinimo(stack);
        int nodo_actual = actual.first;
        
        // Si no ha sido visitado, procesarlo
        if(!visitado[nodo_actual]) {

            // Marcar como visitado
            visitado[nodo_actual] = true;
            
            // Si ya es el objetivo, terminar
            if (nodo_actual == obj) {
                break;
            }
            
            // Recorrer vecinos
            for(int j = 0; j < n; j++) {

                // Verificar si el vecino no ha sido visitado y hay conexión con otro
                if(m[nodo_actual][j] != 0 && m[nodo_actual][j] != INT_MAX && !visitado[j]) {
                    // Calcula el nuevo costo
                    int c_actual = c_list[nodo_actual] + m[nodo_actual][j];
                    
                    // Si el nuevo costo es menor, calcular la f y actualizar
                    if(c_actual < c_list[j]) {
                        c_list[j] = c_actual;
                        padres[j] = nodo_actual; // Guardar padre
                        int f_actual = c_actual + h_list[j];
                        
                        // Agregar nuevo nodo al stack
                        stack.push_back({j, f_actual});
                    }
                }
            }
        }
    }

    // Inicia a reconstruir el camino del recorrido desde el
    // nodo objetivo
    vector<int> recorrido;
    int i = obj;

    // Para cada nodo, lo agrega al recorrido y repite para su padre
    while (i != inicio) {
        recorrido.push_back(i);
        i = padres[i];
    }
    // Al final, agrega el nodo inicial
    recorrido.push_back(inicio);
    
    // Imprime el recorrido en el orden correcto
    cout << "Recorrido: ";
    for(int j = recorrido.size() - 1; j >= 0; j--) {
        cout << recorrido[j] << " ";
    }
    cout << endl;

    // Imprime el costo total
    cout << "Costo total: " << c_list[obj] << endl;
}

int main() {
    vector<vector<int>>m = {
        {0, 1 , INT_MAX, INT_MAX, INT_MAX, 10},
        {1, 0, 2, 1,INT_MAX, INT_MAX},
        {INT_MAX,2, 0, INT_MAX, 5, INT_MAX},
        {INT_MAX, 1, INT_MAX, 0, 3, 4},
        {INT_MAX, INT_MAX, 5, 3 , 0 , 2},
        {10, INT_MAX, INT_MAX, 4, 2, 0},
    };

    vector<int> h_list = {5, 3, 4, 2, 6, 0};

    a_star(m, h_list, 0, 5);

    return 0;
}