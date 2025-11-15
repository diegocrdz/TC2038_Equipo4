#include <iostream>
#include <string>
using namespace std;

void manacher(string s){
    string sm = "$";
    int mayor = 0, temp_i = 0;

    for(int i = 0; i < s.size(); i++) {
        sm += s[i];
        sm += "$";
    }

    for(int j = 1; j < sm.size() - 1; j++) {
        int var = 1, temp_n = 0;

        while((j - var >= 0) && (j + var < sm.size()) && (sm[j - var] == sm[j + var])) {
            temp_n++;
            var++;
        }

        if(temp_n > mayor) {
            mayor = temp_n;
            temp_i = j;
        }
    }

    int indice_inicial = (temp_i / 2) - (mayor / 2);
    int indice_final = indice_inicial + (mayor-1);
    cout << "Indices: S[" << indice_inicial << ":" << indice_final << "]" << endl;
    cout << "Palindromo: " << s.substr(indice_inicial, mayor) << endl;
    cout << "Longitud: " << mayor << endl;
}

int main(){
    manacher("dawxcabbadwad");
    manacher("abcbabcbabcba");
    return 0;
}