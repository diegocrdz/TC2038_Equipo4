#include <iostream>
#include <string>
using namespace std;

void manacher(string s){
    string sm = "$"; // Separador
    int mayor = 0; // Longitud del palindromo mayor
    int temp_i = 0; // Índice del centro del palindromo mayor

    // Agregar separadores al string
    for(int i = 0; i < s.size(); i++) {
        sm += s[i];
        sm += "$";
    }

    // Buscar el palindromo más grande
    for(int j = 1; j < sm.size() - 1; j++) {
        
        int var = 1; // Variable para expandir alrededor del centro
        int temp_n = 0; // Longitud temporal del palindromo

        // Expandir mientras los caracteres a ambos lados coincidan
        while((j - var >= 0) && (j + var < sm.size()) && (sm[j - var] == sm[j + var])) {
            temp_n++;
            var++;
        }

        // Actualizar el palindromo mayor si se encontró uno más grande
        if(temp_n > mayor) {
            mayor = temp_n;
            temp_i = j;
        }
    }

    // Calcular índices en el string original
    int indice_inicial = (temp_i / 2) - (mayor / 2);
    int indice_final = indice_inicial + (mayor-1);

    // Imprimir resultados
    cout << "Indices: S[" << indice_inicial << ":" << indice_final << "]" << endl;
    cout << "Palindromo: " << s.substr(indice_inicial, mayor) << endl;
    cout << "Longitud: " << mayor << endl;
}

int main(){
    manacher("dawxcabbadwad");
    manacher("abcbabcbabcba");
    return 0;
}