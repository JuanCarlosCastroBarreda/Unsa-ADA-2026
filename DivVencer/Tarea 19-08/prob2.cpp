#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;

string quitarCeros(string s) {
    int i = 0;
    int n = (int)s.size();
    while (i < n - 1 && s[i] == '0') {
        i++;
    }
    return s.substr(i);
}

string sumar(string a, string b) {
    string resultado = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int acarreo = 0;

    while (i >= 0 || j >= 0 || acarreo > 0) {
        int x = 0;
        int y = 0;
        if (i >= 0) x = a[i] - '0';
        if (j >= 0) y = b[j] - '0';

        int suma = x + y + acarreo;
        resultado = char(suma % 10 + '0') + resultado;
        acarreo = suma / 10;

        i--;
        j--;
    }

    return quitarCeros(resultado);
}

string restar(string a, string b) {
    string resultado = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int prestamo = 0;

    while (i >= 0) {
        int x = a[i] - '0' - prestamo;
        int y = 0;
        if (j >= 0) y = b[j] - '0';

        if (x < y) {
            x = x + 10;
            prestamo = 1;
        } else {
            prestamo = 0;
        }

        resultado = char(x - y + '0') + resultado;
        i--;
        j--;
    }

    return quitarCeros(resultado);
}

string multiplicarEscolar(string a, string b) {
    int n = (int)a.size();
    int m = (int)b.size();
    vector<int> r(n + m, 0);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mult = (a[i] - '0') * (b[j] - '0');
            int pos = i + j + 1;

            int suma = mult + r[pos];
            r[pos] = suma % 10;
            r[pos - 1] = r[pos - 1] + suma / 10;
        }
    }

    string resultado = "";
    for (int k = 0; k < (int)r.size(); k++) {
        resultado = resultado + char(r[k] + '0');
    }

    return quitarCeros(resultado);
}

string agregarCeros(string a, int n) {
    if (a == "0") return "0";
    for (int i = 0; i < n; i++) {
        a = a + "0";
    }
    return a;
}

string karatsuba(string a, string b) {
    a = quitarCeros(a);
    b = quitarCeros(b);

    if (a == "0" || b == "0") return "0";

    if ((int)a.size() <= 32 && (int)b.size() <= 32) {
        return multiplicarEscolar(a, b);
    }

    int n = max((int)a.size(), (int)b.size());
    int m = n / 2;

    string a0, a1, b0, b1;

    if ((int)a.size() > m) {
        a1 = a.substr(0, a.size() - m);
        a0 = a.substr(a.size() - m);
    } else {
        a1 = "0";
        a0 = a;
    }

    if ((int)b.size() > m) {
        b1 = b.substr(0, b.size() - m);
        b0 = b.substr(b.size() - m);
    } else {
        b1 = "0";
        b0 = b;
    }

    string z0 = karatsuba(a0, b0);
    string z2 = karatsuba(a1, b1);
    string z1 = karatsuba(sumar(a0, a1), sumar(b0, b1));

    z1 = restar(z1, z2);
    z1 = restar(z1, z0);

    string parte1 = agregarCeros(z2, 2 * m);
    string parte2 = agregarCeros(z1, m);
    string resultado = sumar(sumar(parte1, parte2), z0);

    return quitarCeros(resultado);
}

int main() {
    string a, b;
    cin >> a >> b;

    auto ini1 = high_resolution_clock::now();
    string r1 = multiplicarEscolar(a, b);
    auto fin1 = high_resolution_clock::now();

    auto ini2 = high_resolution_clock::now();
    string r2 = karatsuba(a, b);
    auto fin2 = high_resolution_clock::now();

    cout << r2 << endl;

    double t1 = duration<double, milli>(fin1 - ini1).count();
    double t2 = duration<double, milli>(fin2 - ini2).count();

    cerr << "Escolar:   " << t1 << " ms" << endl;
    cerr << "Karatsuba: " << t2 << " ms" << endl;
    cerr << "Coinciden: " << (r1 == r2 ? "si" : "NO") << endl;

    return 0;
}