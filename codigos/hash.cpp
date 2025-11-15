#include <map>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

long long hashF(string s, bool mod=true) {

    // Mapa de valores para el abecedario
    map <string, int> abc;
    abc = {{"a",1}, {"b",2}, {"c",3}, {"d",4}, {"e",5}, {"f",6}, {"g",7}, {"h",8}, {"i",9}, {"j",10},
           {"k",11}, {"l",12}, {"m",13}, {"n",14}, {"ñ",15}, {"o",16}, {"p",17}, {"q",18}, {"r",19},
           {"s",20}, {"t",21}, {"u",22}, {"v",23}, {"w",24}, {"x",25}, {"y",26}, {"z",27}};

    // Parámetros de hash
    int p = 31;
    long long ac = 0; 
    int m = pow(10,9) + 9;

    // Calcular hash
    for (int i = 0; i < s.size(); i++) {
        // Si no se usa mod, sumar directamente
        if (!mod) ac += abc[string(1, s[i])] * ((long long)pow(p, i));
        // Si se usa mod, sumar y aplicar mod
        else ac = (ac + abc[string(1, s[i])] * ((long long)pow(p, i))) % m;
    }
    return ac;
}

int main() {
    string s = "ababcabcabababd";
    //string s = "cacbcac";
    //string s = "xcbcc";
    
    // Calcular y mostrar hash
    cout << "Hash con mod: " << hashF(s, false) << endl;
    cout << "Hash sin mod: " << hashF(s, true) << endl;
    
    return 0;
}