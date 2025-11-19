/*
Concurso de programación intento 2
A - 8 Queens Chess Problem

Equipo:
- Diego Córdova Rodríguez
- Aquiba Yudah Benarroch Bittán
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void reinas(int n, int col, int xInicial, int yInicial, vector<int>& posiciones, int& soluciones, vector<vector<int>>& res) {
    // Caso base
    // Si ya se colocaron todas las reinas
    if (col == n) {
        soluciones++;
        res.push_back(posiciones);
        return;
    }

    // Colocar la reina en la posicion inicial
    if (col == yInicial) {
        posiciones[col] = xInicial;
        reinas(n, col + 1, xInicial, yInicial, posiciones, soluciones, res);
        return;
    }

    // Recorrer las demas filas
    for (int fila = 0; fila < n; fila++) {
        bool esValido = true;

        // Revisar si la posicion es valida
        for (int i = 0; i < col; i++) {
            
            // Si la reina no se ha asignado a ninguna fila
            if (posiciones[i] != -1 && (posiciones[i] == fila || // Si hay otra reina en la misma fila
                posiciones[i] - i == fila - col ||  // Si hay otra reina en la misma diagonal
                posiciones[i] + i == fila + col)) { // Si hay otra reina en la otra diagonal
                esValido = false;
                break; // Si no es valido, salir del ciclo
            }
        }

        // Si es valido, colocar la reina y avanzar a la siguiente fila
        if (esValido) {
            posiciones[col] = fila;
            reinas(n, col + 1, xInicial, yInicial, posiciones, soluciones, res);
        }
    }
}

int main() {
    int numDatasets;
    cin >> numDatasets;

    if (numDatasets < 0) {
        return 0;
    }

    for (int i = 0; i < numDatasets ; i++) {
        int fila, columna;
        cin >> fila >> columna;

        if (fila < 1 || fila > 8 || columna < 1 || columna > 8) {
            return 0;
        }

        fila = fila - 1;
        columna = columna - 1;

        vector<int> posiciones(8, -1);
        int soluciones = 0;
        vector<vector<int>> res;
        reinas(8, 0, fila, columna, posiciones, soluciones, res);

        // El problema pide ordenar las soluciones lexicográficamente
        sort(res.begin(), res.end());

        cout << "SOLN         COLUMN" << endl;
        cout << " #        1 2 3 4 5 6 7 8" << endl;
        cout << endl;

        for(int i = 0; i < res.size(); i++) {
            cout << " " << i + 1 << "        ";
            for(int j = 0; j < res[i].size(); j++) {
                cout << res[i][j] + 1 << " ";
            }
            cout << endl;
        }
    }

    return 0;
}