#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

/*
NOTAS IMPORTANTES PARA LA EJECUCIÓN DEL CÓDIGO
1. En caso de que la matriz de adyacencia tenga un valor infinito, este debe ser representado como INT_MAX
2. Se espera el siguiente formato en el archivo de entrada.txt:
    - Numero de colonias
    - Matriz de adyacencia 
    - Coordenadas de las centrales en el formato (x, y)
*/

/*
E1. Actividad Integradora 2

Descripción:
Implementar algoritmos de ordenamiento y exploración de grafos
para optimizar rutas de conexión y recorridos, ayudando a una empresa
de servicios de internet a optimar sus operaciones.

Equipo:
- Aquiba Yudah Benarroch Bittán, A01783710
- Diego Córdova Rodríguez, A01781166
- Lorena Estefanía Chewtat Torres, A01785378

Fecha: 20 de noviembre de 2025
*/

// Estructura para almacenar los datos leídos del archivo
struct DatosArchivo {
    int numColonias;
    vector<vector<int>> matrizDistancias;
    vector<pair<int, int>> coordenadas;
};

/*
Función para leer un archivo

Entradas:
- string nombreArchivo: nombre del archivo a leer

Salidas:
- DatosArchivo: estructura con los datos leídos del archivo
*/
DatosArchivo leerArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    // Si el archivo no se pudo abrir, regresa datos vacíos
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return {};
    }
 
    // Variables para almacenar el contenido del archivo
    DatosArchivo resultado;
    string linea;

    // Leer el número de colonias
    while (getline(archivo, linea)) {
        // Ignorar líneas vacías
        if (linea.empty()) {
            continue;
        }

        // Guardamos el número de colonias
        resultado.numColonias = stoi(linea);

        // Si ya leímos el número de colonias, salimos del ciclo
        break;
    }

    // Redimensionar la matriz de distancias al número de colonias encontrado
    resultado.matrizDistancias.resize(resultado.numColonias);

    // Leer la matriz de distancias
    for (int i = 0; i < resultado.numColonias; ++i) {
        int distancia;

        // Leer una fila de la matriz
        while (archivo >> distancia) {
            resultado.matrizDistancias[i].push_back(distancia);

            // Si ya leímos una fila completa, salimos del ciclo
            if (resultado.matrizDistancias[i].size() == resultado.numColonias) {
                break;
            }
        }
    }

    // Leer las coordenadas de las centrales
    for (int i = 0; i < resultado.numColonias; ++i) {
        int x, y;
        char ch; // para leer los caracteres de las coordenadas ( , )
        archivo >> ch >> x >> ch >> y >> ch;
        resultado.coordenadas.push_back(make_pair(x, y));
    }
    
    archivo.close();
    return resultado;
}

/*
Conexion
Clase para representar una conexión entre dos nodos

Esta clase es utilizada en el algoritmo Kruskal para almacenar
todas las conexiones (aristas) entre nodos con su costo asociado.

Atributos de la clase:
- int node1: primer nodo de la conexión
- int node2: segundo nodo de la conexión
- int cost: costo de la conexión
*/
class Conexion {
private:
    int node1, node2;
    int cost;

public:
    // Constructor default
    Conexion() : node1(0), node2(0), cost(0) {}

    // Constructor con parámetros
    Conexion(int node1, int node2, int cost) {
        this->node1 = node1;
        this->node2 = node2;
        this->cost  = cost;
    }

    // Getters
    int getNode1() { return node1; }
    int getNode2() { return node2; }
    int getCost() { return cost; }
};

/*
CycleDetector
Clase para detectar ciclos en un grafo mediante padres y rangos

Esta clase es utilizada en el algoritmo de Kruskal para evitar
la formación de ciclos al conectar nodos.

Atributos de la clase:
- vector<int> parent: vector que almacena el padre de cada nodo
- vector<int> rank: vector que almacena el rango de cada nodo
*/
class CycleDetector {
private:
    vector<int> parent; // Padre de cada nodo
    vector<int> rank; // Rango = mayor número nodos conectados al nodo
    
public:
    // Constructor default
    CycleDetector() {
        parent = vector<int>();
        rank = vector<int>();
    }

    // Constructor con parámetros
    CycleDetector(vector<int> nodos) { // Lista de nodos en el grafo
        // Establecer el tamaño inicial de los vectores para que coincidan con el número n de nodos
        int n = nodos.size();
        parent.resize(n);
        rank.resize(n);

        // Inicialmente, cada nodo es su propio padre y tiene un rango de 1
        for (int i=0; i<n; i++) {
            parent[nodos[i]] = nodos[i];
            rank[nodos[i]] = 1;
        }
    }

    // Encontrar el padre de un nodo
    int getParent(int n) {
        // Si el nodo es su propio padre, regresar el nodo
        if (parent[n] == n) {
            return n;
        // Si no, buscar recursivamente el padre del nodo
        } else {
            parent[n] = getParent(parent[n]);
            return parent[n];
        }
    }
    
    // Conectar dos nodos
    void connect(int n1, int n2) {
        // Encontrar los padres de los nodos
        int p1 = getParent(n1);
        int p2 = getParent(n2);

        // Si los padres son diferentes, conectar los nodos
        if(p1 != p2){
            // Comparar los rangos de los padres para decidir cuál será el nuevo padre
            // Si el rango de p1 es menor que el de p2, p2 será el nuevo padre
            if(rank[p1] < rank[p2]) { // Padre 1 es más grande
                parent[p1] = p2;
                rank[p1]++;
            } else if(rank[p1] > rank[p2]) { // Padre 2 es más grande
                parent[p2] = p1;
                rank[p2]++;
            } else {
                // Si ambos rangos son iguales, elegir uno como nuevo padre y aumentar su rango
                parent[p2] = parent[p1];
                rank[p1]++;
            }
        }
    }
};

/*
Merge Sort
Algoritmo de ordenamiento utilizado en el algoritmo
Kruskal para ordenar las conexiones del grafo por costo

Entradas:
- vector<Conexion>& conexiones: vector de conexiones a ordenar

Salidas:
- void: ordena el vector de conexiones por costo en orden ascendente

Complejidad:
- O(n log n) donde n es el número de conexiones en el grafo
*/

// Combinar dos mitades del array
void merge(int lo, int mid, int hi, vector<Conexion>& conexiones) {
    // Copiar el array original a un array auxiliar
    vector<Conexion> aux = conexiones;

    // Indices para recorrer las dos mitades
    int i=lo, j=mid+1, k=lo;
    
    while (i<=mid && j<=hi) {
        if (aux[i].getCost() <= aux[j].getCost()) {
            conexiones[k] = aux[i];
            i++;
        }
        else {
            conexiones[k] = aux[j];
            j++;
        }
        k++;
    }

    // Combinar los elementos restantes
    while (i<=mid) { // Izquierda
        conexiones[k] = aux[i];
        i++;
        k++;
    }

    while (j<=hi) { // Derecha
        conexiones[k] = aux[j];
        j++;
        k++;
    }
}

// Dividir el array en mitades y ordenarlas
void sort(int lo, int hi, vector<Conexion>& conexiones) {
    if (hi <= lo) return;

    // Encontrar el punto medio del array
    int mid = (lo + hi) / 2;

    // Sortear las dos mitades
    sort(lo, mid, conexiones);
    sort(mid+1, hi, conexiones);

    // Combinar las dos mitades ordenadas
    merge(lo, mid, hi, conexiones);
}

// Función wrapper para merge sort
// Esta es la función que se llama externamente
void mergeSort(vector<Conexion>& conexiones) {
    sort(0, conexiones.size() - 1, conexiones);
}

// Parte 1. Forma óptima de cablear todas las colonias con fibra (lista de arcos de la forma (A,B))

/*
Kruskal
Algoritmo para encontrar el árbol de expansión mínima (MST) y su costo total

Internamente utiliza la clase CycleDetector para evitar ciclos,
así como el algoritmo de Merge Sort para ordenar las conexiones por costo.

Entradas:
- vector<vector<int>> m: matriz de adyacencia del grafo

Salidas:
- pair<vector<Conexion>, int>: par con la lista de conexiones del MST y su costo total
*/
pair<vector<Conexion>, int> kruskal(vector<vector<int>> m) {
    int V = m.size(); // Número de nodos
    vector<Conexion> conexiones; // Lista de conexiones (nodo1, nodo2, costo)

    // Crear una lista de conexiones para ordenarlas por costo
    for (int i = 0; i < V; i++) {
        for (int j = i+1; j < V; j++) {
            if (m[i][j] != 0) { // Si hay una conexión entre los nodos
                conexiones.push_back(Conexion(i, j, m[i][j]));
            }
        }
    }

    // Crear una lista con todos los nodos presentes en el grafo
    vector<int> nodos;
    for (int i=0; i<V; i++) {
        nodos.push_back(i);
    }

    // Sortear las conexiones por costo usando merge sort
    mergeSort(conexiones);

    // Crear el detector de ciclos
    CycleDetector cd(nodos);
    vector<Conexion> T; // Arbol de mínima expansión (MST)
    int totalCost = 0;
    int count = 0; // Contador para las conexiones v-1
    
    // Para cada conexión 
    for (int i=0; i<conexiones.size(); i++) {
        // Obtener los nodos y el costo de la conexión
        int n1 = conexiones[i].getNode1();
        int n2 = conexiones[i].getNode2();
        int cost = conexiones[i].getCost();
        
        // Si los nodos tienen diferentes padres, pueden conectarse
        if (cd.getParent(n1) != cd.getParent(n2)) {
            if (count == V-1) break;
            else {
                // Hacer una nueva conexión entre los nodos
                cd.connect(n1, n2);
                totalCost += cost; 
                count++;
                // Guardar la conexión en el MST
                T.push_back(conexiones[i]);
            }
        }
    }
    
    return { T, totalCost };
}

// Parte 2. Ruta a seguir por el personal que reparte correspondencia

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
        if (!visitado[i] && m[nodoActual][i] > 0 && m[nodoActual][i] < INT_MAX) {

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
pair<vector<int>, int> agenteViajero(vector<vector<int>> m) {

    int n = m.size(); // Número de nodos
    int mejorCostoTotal = INT_MAX; // Mejor costo obtenido en total
    vector<int> mejorCaminoTotal = {}; // Mejor camino obtenido en total

    // Probar con cada nodo como inicio
    for(int inicio = 0; inicio < n; inicio ++){

        int mejorCosto = INT_MAX; // Mejor costo obtenido
        vector<int> mejorCamino = {}; // Mejor camino obtenido

        vector<bool> visitado(n, false); // Lista para saber si ya se visitó un nodo
        vector<int> stack; // Almacena el camino actual

        // Iniciar desde este nodo
        visitado[inicio] = true;
        stack.push_back(inicio);

        // Explorar vecinos desde el nodo inicial con branch and bound
        explorarVecinos(m, visitado, stack, 0, inicio, 1, inicio, mejorCosto, mejorCamino);

        if (mejorCosto < mejorCostoTotal) {
            mejorCostoTotal = mejorCosto;
            mejorCaminoTotal = mejorCamino;
        }
    }
    
    return {mejorCaminoTotal, mejorCostoTotal};
}

// Parte 3. Distancia al servidor más cercano 

/*
Función para comparar las coordenadas y encontrar la distancia mínima
Devuelve: (x1, y1, x2, y2, distancia)
*/
vector<tuple<int, int, int, int, double>> comparar_cord(vector<pair<int, int>> centrales, pair<int, int> nuevoPunto) {
    if (centrales.size() < 2) {
        return vector<tuple<int, int, int, int, double>>();
    }
    
    double min = INT_MAX; 
    vector<tuple<int, int, int, int, double>> res;

    // Comparar todos los pares de puntos
    for (int i = 0; i < centrales.size(); i++) {
        // Distancia euclidiana entre los puntos
        double d = sqrt(
            pow(nuevoPunto.first - centrales[i].first, 2) +
            pow(nuevoPunto.second - centrales[i].second, 2)
        );

        // Actualizar el mínimo y resultados
        if (d < min) {
            min = d;
            res.clear();
            res.push_back(make_tuple(
                nuevoPunto.first, nuevoPunto.second,
                centrales[i].first, centrales[i].second,
                d
            ));
        } else if (d == min) {
            res.push_back(make_tuple(
                nuevoPunto.first, nuevoPunto.second,
                centrales[i].first, centrales[i].second,
                d
            ));
        }
    }
    return res;
}

/*
Función principal para Closest Pair of Points (CPP)
Devuelve los puntos más cercanos al punto dado

Entradas:
- vector<pair<int, int>> p: lista de puntos (coordenadas de centrales)
- pair<int, int> punto: punto de referencia (casa)

Salidas:
- vector<tuple<int, int, int, int, double>>: lista de tuplas con (x1, y1, x2, y2, distancia)
*/
vector<tuple<int, int, int, int, double>> cpp(vector<pair<int, int>> p, pair<int, int> punto) {
    // Ordenar los puntos por coordenada x
    sort(p.begin(), p.end());

    //Comparar coordenadas 
    vector<tuple<int, int, int, int, double>> resultado = comparar_cord(p, punto);

    return resultado;
}

int main() {
    // Leer datos del archivo
    DatosArchivo datos = leerArchivo("entrada.txt");

    // Imprimir datos leidos
    cout << endl;
    cout << "------------------ Datos leídos del archivo ------------------" << endl;
    cout << "Número de colonias: " << datos.numColonias << endl;
    cout << "Matriz de distancias:" << endl;
    for (int i = 0; i < datos.numColonias; i++) {
        for (int j = 0; j < datos.numColonias; j++) {
            cout << datos.matrizDistancias[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Coordenadas de las centrales:" << endl;
    for (int i = 0; i < datos.numColonias; i++) {
        cout << "(" << datos.coordenadas[i].first << ", " << datos.coordenadas[i].second << ")" << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
    cout << endl;

    // Definir nombres para las colonias
    vector<string> nombresColonias = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                                      "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
                                      "U", "V", "W", "X", "Y", "Z"};

    // Parte 1. Forma óptima de cablear todas las colonias con fibra (lista de arcos de la forma (A,B))
    // Kruskal

    cout << endl;
    cout << "-------- Parte 1: Forma óptima de cablear todas las colonias ---------" << endl;
    cout << endl;

    // Obtener e imprimir el resultado
    pair<vector<Conexion>, int> resultadoKruskal;
    resultadoKruskal = kruskal(datos.matrizDistancias);

    for (int i = 0; i < resultadoKruskal.first.size(); i++) {
        // Obtener datos de la conexión
        int n1 = resultadoKruskal.first[i].getNode1();
        int n2 = resultadoKruskal.first[i].getNode2();
        int costo = resultadoKruskal.first[i].getCost();
        string col1 = nombresColonias[n1];
        string col2 = nombresColonias[n2];
        cout << "(" << col1 << ", " << col2 << ") " << costo << " km" << endl;
    }
    cout << "Distancia Total: " << resultadoKruskal.second << " km" << endl;

    // Parte 2. Ruta a seguir por el personal que reparte correspondencia
    // Agente Viajero

    cout << endl;
    cout << "-------------- Parte 2: Ruta a seguir por el personal ----------------" << endl;
    cout << endl;

    // Obtener e imprimir el resultado
    pair<vector<int>, int> resultadoAgenteViajero;
    resultadoAgenteViajero = agenteViajero(datos.matrizDistancias);

    cout << "Ruta         : ";
    for (int i = 0; i < resultadoAgenteViajero.first.size(); i++) {
        // Obtener el nombre de la colonia
        int idx = resultadoAgenteViajero.first[i];
        string col = nombresColonias[idx];
        cout << col << " ";
    }
    cout << endl;

    cout << "Ruta inversa : ";
    for (int i = resultadoAgenteViajero.first.size()-1; i >= 0; i--) {
        // Obtener el nombre de la colonia
        int idx = resultadoAgenteViajero.first[i];
        string col = nombresColonias[idx];
        cout << col << " ";
    }
    cout << endl;

    cout << "Distancia    : " << resultadoAgenteViajero.second << " km" << endl;

    // Parte 3. Distancia al servidor más cercano 
    // Pares Cortos (Distancia Euclidiana)

    cout << endl;
    cout << "-------------- Parte 3: Distancia al servidor más cercano ------------" << endl;
    cout << endl;

    cout << "Introduce las coordenadas de tu casa (formato: 'x y'): ";
    int xCasa, yCasa;
    cin >> xCasa >> yCasa;
    pair<int, int> punto = make_pair(xCasa, yCasa); // Coordenadas de la casa
    vector<tuple<int, int, int, int, double>> resultado = cpp(datos.coordenadas, punto);

    cout << "Casa     : "<< "(" << punto.first << ", " << punto.second << ")" << endl;
    for (int i = 0; i < resultado.size(); i++) {
        // Obtener datos del servidor
        int x = get<2>(resultado[i]);
        int y = get<3>(resultado[i]);
        double distancia = get<4>(resultado[i]);
        cout << "Servidor : (" << x << ", " << y << ") Distancia: " << distancia << " km" << endl;
    }

    cout << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << endl;

    return 0;
}