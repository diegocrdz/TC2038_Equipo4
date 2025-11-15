#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> floyd(vector<vector<vector<int>>> conexiones ){
    int n = conexiones.size();
    vector<vector<int>> A(n, vector<int>(n, 0));
    vector<vector<int>> A_ant(n, vector<int>(n, 0));

    // Inicialización de la matriz de adyacencia
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j){
                A[i][j] = 0;
            } else {
                if(conexiones[i][j].size() != 0){
                    A[i][j] = conexiones[i][j][1];
                } else {
                    A[i][j] = 999;                    
                }
            }
        }
    }
    A_ant = A;

    // Siguiente A
    for(int x = 1; x < n; x++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                A[i][j] = min(A_ant[i][j], A_ant[i][x] + A_ant[x][j]);
            }
        }
        A_ant = A;
    }
    return A;
}

int main() {

    vector<vector<vector<int>>> conexiones = {
        { {0, 0}, {1, 5}, {2, 8} , {3, 7}, {4, 10}  },
        { {0, 5}, {1, 0}, {2, 1}, {}, {}},
        { {0, 8}, {1, 1}, {2, 0}, {3, 9}, {}},
        { {0, 7}, {}, {2, 9}, {3, 0}, {4, 2}},
        { {0, 10}, {}, {}, {3, 2}, {4, 0}}
    };

    vector<vector<vector<int>>> conexiones1 = {
        { {0, 0}, {1, 3}, {}, {3, 8}, {4, 7} },
        { {0, 3}, {1, 0}, {2, 1}, {3, 4}, {} },
        { {}, {1, 1}, {2, 0}, {3, 2}, {} },
        { {0, 8}, {1, 4}, {2, 2}, {3, 0}, {4, 3} },
        { {0, 7}, {}, {}, {3, 3}, {4, 0} }
    };

    vector<vector<vector<int>>> conexiones2 = {
        { {0, 0}, {1, 2}, {2, 6}, {}, {}, {}, {} },
        { {0, 2}, {1, 0}, {}, {3, 5}, {}, {}, {} },
        { {0, 6}, {}, {2, 0}, {3, 8}, {}, {}, {} },
        { {}, {1, 5}, {2, 8}, {3, 0}, {4, 10}, {5, 15}, {} },
        { {}, {}, {}, {3, 10}, {4, 0}, {}, {6, 2} },
        { {}, {}, {}, {3, 15}, {}, {5, 0}, {6, 6} },
        { {}, {}, {}, {}, {4, 2}, {5, 6}, {6, 0} }
    };

    vector<vector<vector<int>>> conexiones3 = {
        { {0, 0}, {1, 4}, {2, 4}, {3, 6}, {4, 6} },
        { {0, 4}, {1, 0}, {2, 2}, {}, {} },
        { {0, 4}, {1, 2}, {2, 0}, {3, 8}, {} },
        { {0, 6}, {}, {2, 8}, {3, 0}, {4, 9} },
        { {0, 6}, {}, {}, {3, 9}, {4, 0} }
    };

    vector<vector<int>> A = floyd(conexiones1);

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
