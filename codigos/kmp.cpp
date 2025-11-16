#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Función para construir la lista de prefijos
// Utilizado por kmp
vector<int> prefija(string patron) {

    vector<int> lista(patron.size(), 0); // Para almacenar valores de prefijo, todo inicia en 0
    int len = 0; // Contador de caracteres iguales

    for (int i = 0; i < patron.size(); i++) {

        if (i == 0) lista[i] = 0; // El primer elemento siempre es 0
        else {
            // Mientras no coincidan los caracteres, retroceder en la lista
            while (len > 0 && patron[i] != patron[len]) {
                len = lista[len - 1];
            }
            // Si son iguales, incrementar el contador
            if (patron[i] == patron[len]) {
                len++;
            }
            lista[i] = len;
        }
    }
    return lista;
}

/*
Algoritmo KMP para buscar un patrón en un texto
Entrada:
- texto: el texto donde se buscará el patrón
- patron: el patrón a buscar
Salida:
- vector de pares (inicio, fin) indicando las posiciones donde se encontró el/los patrones
*/
vector<pair<int, int>> kmp(string texto, string patron) {
    vector<int> lista = prefija(patron); // Primero obtenemos la lista de prefijos
    vector<pair<int, int>> indices; // Para almacenar los resultados (inicio, fin)

    // Contadores para texto, patrón
    int i = 0, j = 0;

    // Recorrer el texto
    while (i < texto.size()) {
        // Si los caracteres coinciden, avanzar en ambos
        if (texto[i] == patron[j]) {
            i++;
            j++;
        }

        // Si se ha encontrado el patrón completo
        if (j == patron.size()) {
            indices.push_back({i - patron.size(), i - 1}); // Guardar índice de inicio y fin
            j = lista[j - 1]; // Regresar j
        }

        // Si no coinciden
        if (texto[i] != patron[j]) {
            if (j == 0) i++; // Avanzar en el texto
            else j = lista[j - 1]; // Regresar j
        }
    }
    return indices;
}

int main() {
    /*
    // Ejemplo 1
    string texto = "ababcabcabababd";
    string patron = "ababd";

    // Ejemplo 2
    string texto = "xabcabxabcabcx";
    string patron = "abcabc";

    // Ejemplo 3
    string texto = "abcabcdababcdabcdabde";
    string patron = "abcdabd";
    */
    string texto = "abcabcdababcdabcdabde";
    string patron = "abcdabd";
    
    // Función prefijo y kmp
    vector<int> lista = prefija(patron);
    vector<pair<int, int>> resultados = kmp(texto, patron);

    // Imprimir función prefijo
    if (lista.size() > 0) {
        cout << "Función prefijo:" << endl;
        for (int i = 0; i < lista.size(); i++) {
            cout << lista[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No se pudieron calcular los valores de prefijo" << endl;
    }

    // Imprimir los resultados kmp
    if (resultados.size() > 0) {
        cout << "Resultados KMP:" << endl;
        for (int i = 0; i < resultados.size(); i++) {
            int ind1 = resultados[i].first;
            int ind2 = resultados[i].second;
            string p = texto.substr(ind1, ind2 - ind1 + 1);
            cout << "S[" << ind1 << ":" << ind2 << "] -> " << p << endl;
        }
    } else {
        cout << "No se encontró el patrón en el texto" << endl;
    }

    return 0;
}