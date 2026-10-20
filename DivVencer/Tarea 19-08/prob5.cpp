
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int quickselect(vector<int>& a, int inicio, int fin, int k) {
    int pivote = a[inicio + rand() % (fin - inicio + 1)];

    int i = inicio;
    int j = fin;

    while (i <= j) {
        while (a[i] > pivote)
            i++;

        while (a[j] < pivote)
            j--;

        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (k <= j)
        return quickselect(a, inicio, j, k);

    if (k >= i)
        return quickselect(a, i, fin, k);

    return a[j + 1];
}

int main() {
    srand(time(0));

    int n, k;
    cin >> n >> k;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << quickselect(a, 0, n - 1, k - 1) << endl;

    return 0;
}
