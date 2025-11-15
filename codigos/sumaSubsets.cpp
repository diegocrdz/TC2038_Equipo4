#include <iostream>
#include <vector>

using namespace std;

void encontrarSubset(vector<int>& arr, int ind, int suma, int obj, vector<int>& pila, vector<vector<int>>& res) {

    // Si la suma es igual al objetivo, agregamos el subconjunto actual al resultado
    if (suma == obj) {
        res.push_back(pila);
        return;
    }

    // Si se alcanza el final del array, no se encontró nada
    if (ind == arr.size() || suma > obj) return;

    // Si incluimos el elemento actual
    pila.push_back(arr[ind]);
    encontrarSubset(arr, ind + 1, suma + arr[ind], obj, pila, res);
    pila.pop_back();

    // Si no incluimos el elemento actual
    encontrarSubset(arr, ind + 1, suma, obj, pila, res);
}

vector<vector<int>> sumaSubsets(vector<int> arr, int obj) {
    vector<int> pila; // Pila para ir almacenando el subconjunto actual
    vector<vector<int>> res; // Resultado final
    encontrarSubset(arr, 0, 0, obj, pila, res);
    return res;
}

int main() {
    vector<int> arr = {2, 3, 7, 9};
    vector<vector<int>> res = sumaSubsets(arr, 9);

    // Resultados obtenidos
    for (int i = 0; i < res.size(); i++) {
        cout << "Subconjunto: ";
        for (int j = res[i].size() - 1; j >= 0; j--) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}