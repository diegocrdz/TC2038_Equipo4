#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm> // Librería utilizada para ordenar arreglo de sufijos

using namespace std;

/*
E1. Actividad Integradora 1

Descripción:
Implementar algoritmos de búsqueda de patrones en strings
para analizar transmisiones de datos.

Equipo:
- Aquiba Yudah Benarroch Bittán, A01783710
- Diego Córdova Rodríguez, A01781166
- Lorena Estefanía Chewtat Torres, A01785378

NOTA: Las referencias bibliográficas para las complejidades de los algoritmos
están en el archivo "team.txt"

Fecha: 23 de octubre de 2025
*/

/*
Función para leer un archivo

Entradas:
- string nombreArchivo: nombre del archivo a leer

Salidas:
- string: contenido del archivo con líneas separadas por '#'
*/
string leerArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    // Si el archivo no se pudo abrir, regresar un string vacío
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return "";
    }

    // Variables para almacenar el contenido del archivo
    string resultado;
    string linea;

    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {
        // Agregar caracter al inicio de cada linea
        // No agrega caracter en la primera línea
        if (!resultado.empty()) {
            resultado += "#";
        }
        // Agregar el resto de la línea
        resultado += linea;
    }

    archivo.close();
    return resultado;
}

/*
Función Z: Buscar patrones en un string

Entradas:
- string s: string donde se buscará el patrón
- string p: patrón a buscar

Salidas:
- void: Imprime true|false indice_inicio en string s

Complejidad:
O(n^2) donde n es el tamaño del string s + p (Gusfield, D., s.f., p. 11).
En el peor de los casos, si se tienen strings repetitivos, se comparan 
n carácteres por los carácteres de p que coinciden en s.
*/

void zfunction(string s, string p) {

    // Concatena patrón + separador + string
    string s_temp = p + "$" + s;

    // índices y contadores
    int i = 0;
    int j = 1;
    int j_temp = 1;
    int encontrados = 0; // Número de veces que se encontró el patrón 
    int repeticiones = 0;

    // Vectores para guardar índices y valores z
    vector<int> indices;
    vector<int> z_values(s_temp.size(), 0);

    // Mientras j sea menor al tamaño de s_temp
    while (j < s_temp.size()) {
        // Inicializa valores
        i = 0;
        j = j_temp;
        repeticiones = 0;

        // Compara caracteres mientras sean iguales 
        while (j < s_temp.size() && s_temp[i] == s_temp[j]) {
            i++;
            j++;
            repeticiones++;
        }

        // Guarda el valor de repeticiones en z_values
        // Avanza j_temp al siguiente índice
        z_values[j_temp] = repeticiones;
        j_temp++;
    }

    // Imprime z_values y busca los patrones encontrados
    for (int k = 0; k < z_values.size(); k++) {
        // Si se encontró el patrón, guarda el índice real
        if (z_values[k] == p.size()) {
            encontrados++;
            indices.push_back(k - (p.size()));
        }
    }

    // Imprime resultados
    if (encontrados > 0) {
        cout << "True ";
        for (int k = 0; k < indices.size(); k++) {
            cout << indices[k] << " ";
        }
        cout << endl;
    } else {
        cout << "False" << endl;
    }
}

/*
Manacher: Encontrar el/los palíndromos más largos en un string

Entradas:
- string s: string donde se buscarán palíndromos

Salidas:
- void: Imprime posicion_inicial posicion_final de palindromo en string s

Complejidad:
O(n^2) donde n es el tamaño del palíndromo de entrada S (Manacher, G., 1975, p. 1).
En el peor de los casos, si se tiene un string con todos los caracteres iguales,
se comparan n caracteres para cada uno de los n índices del string.
*/

void manacher(string s) {

    // Primer carácter de string modificado
    string sm = "$";

    // Variables
    int mayor = 0; // longitud del palíndromo más largo

    // Vector para almacenar los índices iniciales encontrados
    vector<int> indices;

    // Agregar separadores entre caracteres
    for(int i = 0; i < s.size(); i++){
        sm += s[i];
        sm += "$";
    }

    // Buscar palíndromos
    for(int j = 0; j < sm.size(); j++) {
        int var = 1, temp_n = 0;

        // Mientras j sea un índice válido y los caracteres a ambos lados sean iguales
        while((j >= 0 && j <= sm.size()) && (sm[j-var] == sm[j+var])) {
            temp_n++;
            var++;
        }

        // Si hay un nuevo mayor, actualizar
        if(temp_n > mayor){
            mayor = temp_n;
            indices.clear(); // Reiniciar índices
            indices.push_back(j);
        } else if(temp_n == mayor) {
            // Si tiene la misma longitud que el mayor, guardar índice
            indices.push_back(j);
        }
    }

    // Imprimir resultados
    for (int k = 0; k < indices.size(); k++) {
        
        // Obtener el índice del string original
        int indice = indices[k];
        int indice_inicial = (indice / 2) - (mayor / 2) + 1; // +1 para índice basado en 1
        int indice_final = indice_inicial + (mayor - 1);

        // Imprimir índice inicial y final
        cout << indice_inicial << " " << indice_final << endl;
    }
}

/*
Función para comparar 2 strings y encontrar la longitud del substring común más largo

Entradas:
- string s1: primer string
- string s2: segundo string

Salidas:
- int: longitud del substring común más largo

Complejidad:
O(n) donde n es la longitud del substring común más largo entre s1 y s2
*/

int comparador(string s1, string s2) {
    int len = 0; // Longitud en común
    int i = 0; // índice

    while(s1[i] == s2[i]) {
        len++;
        i++;
    }
    return len;
}

/*
Arreglo de sufijos: Encontrar el substring común más largo entre 2 strings

Entradas:
- string s1: primer string
- string s2: segundo string

Salidas:
- void: Imprime posicion_inicial posicion_final de substring en string s1 y string s2

Complejidad:
O(n^2 log n) donde n es la longitud del string n1 + n2 (Fischer, J., Sanders, P., 2013, p. 75).
Ordenar los sufijos toma O(n log n) y comparar sufijos toma O(n) en el peor de los casos.
Si además se tienen que comparar todos los sufijos vecinos, la complejidad total es O(n^2 log n).
*/

void suffix(string s1, string s2) {
    
    // Concatenar strings con separador
    string s = s1 + "$" + s2;
    int i_sep = s1.size(); // Índice donde se encuentra el separador
    
    // Vectores para almacenar resultados
    vector<pair<string, int>> sufijos; // par sufijo, indice en s
    vector<pair<string, int>> ord; // sufijos ordenados

    // Generar sufijos y almacenarlos
    for (int i = s.size() - 1; i >= 0; i--) {
        sufijos.push_back({s.substr(i), i});
    }

    // Ordenar sufijos alfabéticamente A-Z
    ord = sufijos;
    sort(ord.begin(), ord.end());

    int mayor = 0; // Longitud del substring común más largo
    vector<pair<int, int>> indices; // índices de inicio y fin de substring en s1
    
    // Recorrer sufijos ordenados y comparar vecinos
    for(int i = 1; i < ord.size() ; i++){
        
        // Obtener índices de sufijos a comparar
        int indice1 = ord[i-1].second; // Solo obtiene el índice en s
        int indice2 = ord[i].second;

        // Ver si los sufijos pertenecen a strings diferentes
        if ((indice1 < i_sep && indice2 > i_sep) ||
            (indice1 > i_sep && indice2 < i_sep)
        ) {
            // Obtener los sufijos a comparar
            string sufijo1 = ord[i-1].first;
            string sufijo2 = ord[i].first;

            // Comparar sufijos y obtener longitud en común
            int len = comparador(sufijo1, sufijo2);

            // Si la longitud es mayor, actualizar
            if(len > mayor) {
                mayor = len;
                indices.clear(); // Reiniciar índices
            }

            // Si la longitud es igual al mayor, guardar índices
            if (len == mayor) {
                // Ver cuál sufijo pertenece al string 1
                if (indice1 < i_sep) {
                    // Sufijo 1 pertenece a string 1
                    indices.push_back({indice1 + 1, indice1 + len});
                } else {
                    // Sufijo 2 pertenece a string 1
                    indices.push_back({indice2 + 1, indice2 + len});
                }
            }
        } 
    }

    // Imprimir resultados
    if (mayor > 0) {
        // Si se encontraron resultados, los imprime
        for (int j = 0; j < indices.size(); j++) {
            cout << indices[j].first << " " << indices[j].second << endl;
        }
    } else {
        // Si no hay resultados, imprime error
        cout << "Error. No se encontraron resultados." << endl;
    }
}


int main() {
    // Leer archivos
    string mcode1 = leerArchivo("mcode1.txt");
    string mcode2 = leerArchivo("mcode2.txt");
    string mcode3 = leerArchivo("mcode3.txt");
    string transmission1 = leerArchivo("transmission1.txt");
    string transmission2 = leerArchivo("transmission2.txt");

    // Parte 1: Buscar códigos maliciosos en las transmisiones
    cout << "--------- Parte 1: Buscar códigos maliciosos en las transmisiones -----------" << endl;
    cout << endl;
    cout << "Transmisión 1:" << endl;
    zfunction(transmission1, mcode1);
    zfunction(transmission1, mcode2);
    zfunction(transmission1, mcode3);
    cout << endl;
    cout << "Transmisión 2:" << endl;
    zfunction(transmission2, mcode1);
    zfunction(transmission2, mcode2);
    zfunction(transmission2, mcode3);
    cout << endl;

    // Parte 2: Encontrar palíndromos más largos en transmisiones
    cout << "-------- Parte 2: Encontrar palíndromos más largos en transmisiones ---------" << endl;
    cout << endl;
    cout << "Transmisión 1:" << endl;
    manacher(transmission1);
    cout << endl;
    cout << "Transmisión 2:" << endl;
    manacher(transmission2);
    cout << endl;

    // Parte 3: Encontrar substring común más largo entre  transmisiones
    cout << "----- Parte 3: Encontrar substring común más largo entre  transmisiones -----" << endl;
    cout << endl;
    suffix(transmission1, transmission2);
    cout << endl;

    return 0;
}