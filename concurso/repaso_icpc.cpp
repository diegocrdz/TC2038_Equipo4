#include <iostream>
#include <string>
#include <vector>
#include <fstream> // Leer archivos
using namespace std;

int zfunction(string s, string p) {
    string s_temp = p + "$" + s;
    int i = 0, j = 1;
    int j_temp = 1;
    int encontrados = 0;
    int repeticiones = 0;
    vector<int> z_values(s_temp.size(), 0);

    while (j < s_temp.size()) {
        i = 0;
        j = j_temp;
        repeticiones = 0;

        while (j < s_temp.size() && s_temp[i] == s_temp[j]) {
            i++;
            j++;
            repeticiones++;
        }

        z_values[j_temp] = repeticiones;
        j_temp++;
    }

    for (int k = 0; k < z_values.size(); k++) {
        if (z_values[k] == p.size()) {
            encontrados++;
        }
    }

    return encontrados;
}

bool caracterEspecial(char c) {
    string esp = "1234567890!#$%&/()=?¡'¿´+¨*{}[],;.:-_";
    for (int i = 0; i < esp.size(); i++) {
        if (esp[i] == c) {
            return true;
        }
    }
    return false;
}

string normalizar(string s) {
    string res;
    int len = 0;

    for (int i = 0; i < s.size(); i++) {
        if (len > 20) {
            return "#";
        }

        if (caracterEspecial(s[i])) {
            s[i] = ' ';
            res += ' ';
            len++;
        } else {
            res += s[i];
        }
    }
    return res;
}

vector<string> separar(string s) {
    
    vector<string> res;
    string acumulado = "";

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            res.push_back(acumulado);
            acumulado = "";
        } else if (i == s.size() - 1) {
            acumulado += s[i];
            res.push_back(acumulado);
            acumulado = "";
        } else {
            acumulado += s[i];
        }
    }

    return res;
}

int main() {
    int x = 1; // Contador de casos

    fstream archivo("entrada.txt");

    if (!archivo.is_open()) {
        return 0;
    }

    // Mientras no sea el final del archivo
    while (!archivo.eof()) {

        string line1;
        string line2;

        getline(archivo, line1);
        getline(archivo, line2);

        if (line1.size() > 1000 || line2.size() > 1000) {
            cout << "Linea no valida, tiene mas de 1000 caracteres" << endl;
            return 0;
        }

        if (line1 == "" || line2 == "") {
            cout << x << ". " << "Blank!" << endl;
            x++;
        } else {
            string l1 = normalizar(line1);
            string l2 = normalizar(line2);
            
            if (l1 == "#" || l2 == "#") {
                return 0;
            }

            vector<string> lineas2 = separar(l2);

            int max = 0;

            for (int i = 0; i < lineas2.size(); i++) {
                int encontradas = zfunction(l1, lineas2[i]);

                max += encontradas;
            }

            cout << x << ". " << "Length of longest match: " << max << endl;
            x++;
        }
    }
    
    return 0;
}