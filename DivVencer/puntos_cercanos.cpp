#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

struct Punto {
    int x, y;
    int id;
};

struct Resultado {
    double distancia;
    Punto p1, p2;
};

double distancia(Punto a, Punto b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Resultado fuerzaBruta(vector<Punto>& puntos) {
    Resultado mejor;
    mejor.distancia = numeric_limits<double>::infinity();

    for (int i = 0; i < (int)puntos.size(); i++) {
        for (int j = i + 1; j < (int)puntos.size(); j++) {
            double d = distancia(puntos[i], puntos[j]);

            if (d < mejor.distancia) {
                mejor = {d, puntos[i], puntos[j]};
            }
        }
    }
    return mejor;
}

Resultado puntosCercanos(vector<Punto>& X, vector<Punto>& Y) {
    int n = X.size();

    if (n <= 3) {
        return fuerzaBruta(X);
    }

    int mitad = n / 2;
    int xMedio = X[mitad].x;

    vector<Punto> izqX(X.begin(), X.begin() + mitad);
    vector<Punto> derX(X.begin() + mitad, X.end());

    vector<Punto> izqY, derY;

    for (Punto p : Y) {
        if (p.id < 0) continue;
        bool izquierda = false;
        for (Punto q : izqX) {
            if (p.id == q.id) {
                izquierda = true;
                break;
            }
        }

        if (izquierda)
            izqY.push_back(p);
        else
            derY.push_back(p);
    }

    Resultado a = puntosCercanos(izqX, izqY);
    Resultado b = puntosCercanos(derX, derY);

    Resultado mejor = (a.distancia < b.distancia) ? a : b;
    double delta = mejor.distancia;

    vector<Punto> franja;

    for (Punto p : Y) {
        if (abs(p.x - xMedio) < delta) {
            franja.push_back(p);
        }
    }
    
    for (int i = 0; i < (int)franja.size(); i++) {
        for (int j = i + 1;
             j < (int)franja.size() && j <= i + 7;
             j++) {

            double d = distancia(franja[i], franja[j]);

            if (d < mejor.distancia) {
                mejor = {d, franja[i], franja[j]};
            }
        }
    }

    return mejor;
}

int main() {
    vector<Punto> puntos = {
        {1, 12, 1}, {3, 7, 2}, {7, 1, 3},
        {8, 9, 4}, {9, 3, 5}, {10, 5, 6},
        {12, 8, 7}, {13, 4, 8}, {18, 6, 9},
        {19, 0, 10}
    };

    vector<Punto> X = puntos;
    vector<Punto> Y = puntos;

    sort(X.begin(), X.end(), [](Punto a, Punto b) {
        return a.x < b.x;
    });

    sort(Y.begin(), Y.end(), [](Punto a, Punto b) {
        return a.y < b.y;
    });

    Resultado r = puntosCercanos(X, Y);

    cout << "Puntos mas cercanos:" << endl;
    cout << "P" << r.p1.id << " ("
         << r.p1.x << ", " << r.p1.y << ")" << endl;
    cout << "P" << r.p2.id << " ("
         << r.p2.x << ", " << r.p2.y << ")" << endl;
    cout << "Distancia minima: " << r.distancia << endl;

    return 0;
}
