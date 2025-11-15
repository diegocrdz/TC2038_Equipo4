#include <iostream>
#include <vector>
#include <climits> // Para INT_MAX
#include <cmath> // Para sqrt y pow
#include <algorithm> // Para sort

using namespace std;

// Función para comparar las coordenadas y encontrar la distancia mínima
// Devuelve: (x1, y1, x2, y2, distancia)
vector<tuple<int, int, int, int, double>> comparar_cord(vector<pair<int, int>> v) {
    if (v.size() < 2) {
        return vector<tuple<int, int, int, int, double>>();
    }
    
    double min = INT_MAX; 
    vector<tuple<int, int, int, int, double>> res;

    // Comparar todos los pares de puntos
    for (int i = 0; i < v.size()-1; i++) {
        for (int j = i+1; j < v.size(); j++) {

            // Distancia euclidiana entre los puntos
            double d = sqrt(pow(v[i].first - v[j].first, 2) + pow(v[i].second - v[j].second, 2));

            // Actualizar el mínimo y resultados
            if (d < min) {
                min = d;
                res.clear();
                res.push_back(make_tuple(v[i].first, v[i].second, v[j].first, v[j].second, d));
            } else if (d == min) {
                res.push_back(make_tuple(v[i].first, v[i].second, v[j].first, v[j].second, d));
            }
        }
    }
    return res;
}

vector<tuple<int, int, int, int, double>> cpp(vector<pair<int, int>> p) {
    // Ordenar los puntos por coordenada x
    sort(p.begin(), p.end());

    // Valor medio 
    int n = p.size()/2;

    // Dividir en dos mitades
    vector<pair<int, int>> left(p.begin(), p.begin() + n);
    vector<pair<int, int>> right(p.begin() + n, p.end());

    //Comparar coordenadas 
    vector<tuple<int, int, int, int, double>> left_min = comparar_cord(left);
    vector<tuple<int, int, int, int, double>> right_min = comparar_cord(right);

    // Hacer el margen de comparacion 
    int m = p.size() / 3;
    vector<pair<int, int>> mid(p.begin() + m, p.begin() + m + n);
    vector<tuple<int, int, int, int, double>> d_mid = comparar_cord(mid);

    // Encontrar el minimo entre las tres comparaciones
    double min = INT_MAX;
    
    if (!left_min.empty() && get<4>(left_min[0]) < min) {
        min = get<4>(left_min[0]);
    }
    if (!right_min.empty() && get<4>(right_min[0]) < min) {
        min = get<4>(right_min[0]);
    }
    if (!d_mid.empty() && get<4>(d_mid[0]) < min) {
        min = get<4>(d_mid[0]);
    }

    // Almacenar los resultados con la distancia minima
    vector<tuple<int, int, int, int, double>> resultado;

    for (int i = 0; i < left_min.size(); i++) {
        if (get<4>(left_min[i]) == min) {
            resultado.push_back(left_min[i]);
        }
    }
    for (int j = 0; j < right_min.size(); j++) {
        if (get<4>(right_min[j]) == min) {
            resultado.push_back(right_min[j]);
        }
    }
    for (int k = 0; k < d_mid.size(); k++) {
        if (get<4>(d_mid[k]) == min) {
            resultado.push_back(d_mid[k]);
        }
    }
    return resultado;
}

int main () {
    vector<pair<int, int>> puntos = {
        {2, 4},
        {1, 1},
        {2, 2},
        {3, 1}
    };

    // Buscamos los pares de puntos con la distancia mínima
    vector<tuple<int, int, int, int, double>> resultado = comparar_cord(puntos);

    cout << "Pares de puntos con distancia mínima:" << endl;
    for (int i = 0; i < resultado.size(); i++) {
        cout << "(" << get<0>(resultado[i]) << ", " << get<1>(resultado[i]) << ") -> (" 
             << get<2>(resultado[i]) << ", " << get<3>(resultado[i]) << ") - Distancia: " 
             << get<4>(resultado[i]) << endl;
    }
    
    return 0;
}