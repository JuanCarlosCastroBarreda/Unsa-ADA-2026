#include <iostream>
using namespace std;

long long potencia_secu(int a, int n) {
    long long resultado = 1;

    for (int i = 0; i < n; i++) {
        resultado *= a;
    }

    return resultado;
}

long long potencia_log(int a, int n) {
    if (n == 0)
        return 1;

    long long mitad = potencia_log(a, n / 2);

    if (n % 2 == 0)
        return mitad * mitad;
    else
        return a * mitad * mitad;
}

int main() {
    cout << "Potencia Secuencial:" << endl;
    cout << potencia_secu(2, 5) << endl;
    cout << potencia_secu(3, 2) << endl;

    cout << "Potencia Logarítmica:" << endl;
    cout << potencia_log(4, 3) << endl;
    cout << potencia_log(2, 4) << endl;
     return 0;
}