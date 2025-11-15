#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void sufix(string s) {

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

    cout << "Sufijos del string: " << endl;
    for(int j = 0; j < sufijos.size() ; j++) {
        cout << "[" << sufijos[j].second << "]" << sufijos[j].first << endl;
    }

    cout << "Sufijos ordenados : " << endl;
    for(int j = 0; j < ord.size() ; j++) {
        cout << "[" << ord[j].second << "]" << ord[j].first << endl;
    }
}

int main(){
    string s = "ababcabcabababd$";
    sufix(s);
    return 0;
}