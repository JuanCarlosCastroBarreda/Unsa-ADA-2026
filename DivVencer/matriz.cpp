#include <iostream>
using namespace std;

struct Matriz {
    int a[2][2];
};

Matriz multiplicar(Matriz A, Matriz B) {
    Matriz C;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            C.a[i][j] = 0;

            for (int k = 0; k < 2; k++)
                C.a[i][j] += A.a[i][k] * B.a[k][j];
        }

    return C;
}

Matriz potencia(Matriz A, int n) {
    if (n == 0) {
        Matriz I = {{{1, 0}, {0, 1}}};
        return I;
    }

    Matriz mitad = potencia(A, n / 2);
    Matriz resultado = multiplicar(mitad, mitad);

    if (n % 2 != 0)
        resultado = multiplicar(resultado, A);

    return resultado;
}

int main() {
    Matriz A = {{{1, 2}, {3, 4}}};

    Matriz R = potencia(A, 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            cout << R.a[i][j] << " ";
        cout << endl;
    }

    return 0;
}