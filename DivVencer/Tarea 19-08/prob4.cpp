
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

struct Punto {
    double x, y;
};

double distancia(Punto a, Punto b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double fuerzaBruta(vector<Punto>& p, int inicio, int fin) {
    double mejor = 1e9;

    for (int i = inicio; i <= fin; i++)
        for (int j = i + 1; j <= fin; j++)
            mejor = min(mejor, distancia(p[i], p[j]));

    return mejor;
}

double cercano(vector<Punto>& p, int inicio, int fin) {
    if (fin - inicio <= 2)
        return fuerzaBruta(p, inicio, fin);

    int medio = (inicio + fin) / 2;
    double xMedio = p[medio].x;

    double izquierda = cercano(p, inicio, medio);
    double derecha = cercano(p, medio + 1, fin);
    double mejor = min(izquierda, derecha);

    vector<Punto> franja;

    for (int i = inicio; i <= fin; i++)
        if (abs(p[i].x - xMedio) < mejor)
            franja.push_back(p[i]);

    sort(franja.begin(), franja.end(),
         [](Punto a, Punto b) {
             return a.y < b.y;
         });

    for (int i = 0; i < (int)franja.size(); i++) {
        for (int j = i + 1;
             j < (int)franja.size() &&
             franja[j].y - franja[i].y < mejor;
             j++) {
            mejor = min(mejor, distancia(franja[i], franja[j]));
        }
    }

    return mejor;
}

int main() {
    int n;
    cout << "0 para terminar" << endl;
    
    while (cin >> n && n != 0) {
        vector<Punto> p(n);

        for (int i = 0; i < n; i++)
            cin >> p[i].x >> p[i].y;

        if (n == 1) {
            cout << "INFINITY\n";
            continue;
        }

        sort(p.begin(), p.end(),
             [](Punto a, Punto b) {
                 return a.x < b.x;
             });

        double resultado = cercano(p, 0, n - 1);

        if (resultado >= 10000)
            cout << "INFINITY\n";
        else
            cout << fixed << setprecision(4)
                 << resultado << '\n';
    }

    return 0;
}
