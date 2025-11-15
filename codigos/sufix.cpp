#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<string, int>> sufix(string s) {

    // Variables para los sufijos
    vector<pair<string, int>> sufijos; // par<sufijo, índice>
    vector<pair<string, int>> ord; // par<sufijo, índice>

    // Generar sufijos
    for (int i = s.size() - 1; i >= 0; i--) {
        sufijos.push_back({s.substr(i, s.size()), i});
    }

    // Ordenar sufijos por el string del sufijo
    ord = sufijos;
    sort(ord.begin(), ord.end());

    // Regresar sufijos ordenados
    return ord;
}

int main(){
    string s = "ababcabcabababd$";
    vector<pair<string, int>> res = sufix(s);

    // Imprimir sufijos ordenados
    for (int i = 0; i < res.size(); i++) {
        cout << "[" << res[i].second << "] " << res[i].first<< endl;
    }
    
    return 0;
}