#include <iostream>
using namespace std;

long long fibonacci_secu(int n) {
    long long a = 0, b = 1;

    for (int i = 0; i < n; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }

    return a;
}

pair<long long, long long> fibonacci_log(int n) {
    if (n == 0)
        return {0, 1};

    auto p = fibonacci_log(n / 2);

    long long a = p.first;
    long long b = p.second;

    long long c = a * (2 * b - a);
    long long d = a * a + b * b;

    if (n % 2 == 0)
        return {c, d};
    else
        return {d, c + d};
}

int main() {
    cout << "Fibonacci Secuencial:" << endl;
    for (int n = 0; n <= 20; n++) {
        cout << n << ": "
             << fibonacci_secu(n) << endl;
    }
    cout << "Fibonacci Logarítmico:" << endl;
    for (int n = 0; n <= 20; n++) {
        cout << n << ": "
             << fibonacci_log(n).first << endl;
    }

    return 0;
}