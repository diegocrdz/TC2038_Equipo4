#include <iostream>
#include <vector>

using namespace std;

// Método recursivo
int fibonacci(int n) {
    if (n<=1) return n;
    else return fibonacci(n-1) + fibonacci(n-2);
}

// Programación dinámica

// Memoización recursiva
int fibonacciMemo(int n) {
    // Vector para almacenar resultados ya calculados
    vector <int> memo = {0,1};

    // Si ya se calculó, regresar el valor
    if (n < memo.size()) {
        return memo[n];
        
    } else {
        // Si no se ha calculado, calcularlo y guardarlo en el vector
        int f = fibonacciMemo(n-1) + fibonacciMemo(n-2);
        memo.push_back(f);

        // Regresar el valor calculado
        return f;
    }
}

int fibonacciMemo2(int n) {
    if (n<=1) return n; // Caso base
    else {
        // Calcula n1 y n2
        int n1 = fibonacciMemo2(n-1);
        int n2 = fibonacciMemo2(n-2);
        // Obtiene la suma de n-1 + n-2
        int f;
        f = n1 + n2;
        n1 = n2; // Intercambia valores
        n2 = f;
        return f;
    }
}

// Otra forma de hacerlo
int fibonacciMemo3(int n, int a, int b) {
    if (n<=1) return n; // Caso base
    return fibonacciMemo3(n-1, b, a+b);
}

// Tabulación iterativa

int fibonacciIterativo(int n) {
    vector <int> f(n);
    f[0] = 0;
    f[1] = 1;

    for(int i=2; i<=n; i++) {
        f[i] = f[i-1] + f[i-2];
    }
    return f[n];
}

int fibonacciIterativo2(int n) {
    if (n<=1) return n;
    else {
        int n1=0, n2=1, f;

        for(int i=2; i<=n; i++) {
            f = n1 + n2;
            n1 = n2;
            n2 = f;
        }
        return f;
    }
}

int main() {
    //cout << "Número correspondiente a la posición n: " << fibonacci(6) << endl;
    //cout << "Número correspondiente a la posición n: " << fibonacciMemo(6) << endl;
    //cout << "Número correspondiente a la posición n: " << fibonacciMemo2(6) << endl;
    //cout << "Número correspondiente a la posición n: " << fibonacciIterativo(6) << endl;
    cout << "Número correspondiente a la posición n: " << fibonacciIterativo2(6) << endl;
}