#include <vector>
#include <iostream>

using namespace std;

// Clase para representar objetos que irán dentro de la mochila
// cada objeto tiene un valor (costo) y peso
class Objeto {
    private:
        int valor, peso;

    public:
        // Constructor default
        Objeto() {
            valor = 0;
            peso = 0;
        }

        // Constructor
        Objeto(int valor, int peso) {
            this->valor = valor;
            this->peso = peso;
        }

        // Getters
        int getValor() { return valor; }
        int getPeso() { return peso; }

        // Imprimir info
        void imprimirObjeto() {
            cout << "Valor: $" << valor << " Peso: " << peso << endl;
        }
};

/*
Función knapsack
Entrada:
- vector de objetos
- peso máximo (w)
Salida:
- Valor máximo
*/

int knapsack(vector<Objeto> objetos, int w) {

    // Obtener número objetos
    int n = objetos.size();

    // Matriz para almacenar los valores máximos
    vector<vector<int>> A(n+1, vector<int>(w+1, 0));

    for (int i=1; i<=n; i++) {

        // Peso del objeto actual
        int wi = objetos[i-1].getPeso();
        int vi = objetos[i-1].getValor();

        for (int x=0; x<=w; x++) {
            
            int n1 = A[i-1][x];
            int n2;

            if (x >= wi) {
                n2 = A[i-1][x-wi] + vi;
            } else {
                n2 = n1;
            }

            // Seleccionar el máximo
            if (n1 < n2) {
                A[i][x] = n2;
            } else {
                A[i][x] = n1;
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int x = 0; x <= w; x++) {
            cout << A[i][x] << " ";
        }
        cout << endl;
    }
    
    // Regresar valor máximo
    return A[n][w];
}

int main() {
    vector<Objeto> objetos;
    /*
    objetos.push_back(Objeto(3, 4));
    objetos.push_back(Objeto(2, 3));
    objetos.push_back(Objeto(4, 2));
    objetos.push_back(Objeto(4, 3));
    */

    /*
    objetos.push_back(Objeto(30, 6));
    objetos.push_back(Objeto(14, 3));
    objetos.push_back(Objeto(16, 4));
    objetos.push_back(Objeto(9, 2));
    */

    objetos.push_back(Objeto(2, 1));
    objetos.push_back(Objeto(4, 3));
    objetos.push_back(Objeto(7, 5));
    objetos.push_back(Objeto(10, 7));

    // Obtener valor máximo
    //int max = knapsack(objetos, 6);
    //int max = knapsack(objetos, 10);
    int max = knapsack(objetos, 8);

    // Imprimir resultado
    cout << "Valor máximo: " << max << endl;

    return 0;
}