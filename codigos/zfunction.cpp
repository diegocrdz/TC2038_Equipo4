#include <iostream>
#include <string>
#include <vector>
using namespace std;

void zfunction(string s, string p) {
    string s_temp = p + "$" + s;
    int i = 0;
    int j = 1;
    int j_temp = 1;
    int encontrados = 0;
    vector<int> indices;
    vector<int> z_values(s_temp.size(), 0);
    int repeticiones = 0;

    // Mientras j sea menor al tamaño de s_temp
    while (j < s_temp.size()) {
        // Inicializa valores
        i = 0;
        j = j_temp;
        repeticiones = 0;

        // 
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
    cout << "Z-values: ";
    for (int k = 0; k < z_values.size(); k++) {
        // Imprime z_values
        cout << z_values[k] << " ";

        // Si se encontró el patrón, guarda el índice real
        if (z_values[k] == p.size()) {
            encontrados++;
            indices.push_back(k - (p.size() + 1));
        }
    }
    cout << endl;

    // Imprime resultados
    cout << "Patrón encontrado " << encontrados << " veces" << endl;
    cout << "Indices de inicio de patrón: ";
    for (int k = 0; k < indices.size(); k++) {
        cout << indices[k] << " ";
    }
    cout << endl;
}

int main() {
    //zfunction("XABCABXABCABCX", "ABCABC");
    zfunction("XABCABXABCABCXABCABC", "ABCABC");
    //zfunction("ABABCABCABABABD", "ABABD");
    return 0;
}
