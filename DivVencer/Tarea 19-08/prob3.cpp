#include <iostream>
#include <vector>
using namespace std;

long long contadorInversiones;
void mezclar(vector<int>& v, vector<int>& aux, int ini, int mid, int fin) {
    int i = ini;
    int j = mid + 1;
    int k = ini;

    while (i <= mid && j <= fin) {
        if (v[i] <= v[j]) {
            aux[k] = v[i];
            i++;
        } else {
            aux[k] = v[j];
            contadorInversiones = contadorInversiones + (mid - i + 1);
            j++;
        }
        k++;
    }

    while (i <= mid) {
        aux[k] = v[i];
        i++;
        k++;
    }
    while (j <= fin) {
        aux[k] = v[j];
        j++;
        k++;
    }
    for (int p = ini; p <= fin; p++) {
        v[p] = aux[p];
    }
}

void mergeSort(vector<int>& v, vector<int>& aux, int ini, int fin) {
    if (ini >= fin) return;

    int mid = (ini + fin) / 2;
    mergeSort(v, aux, ini, mid);
    mergeSort(v, aux, mid + 1, fin);
    mezclar(v, aux, ini, mid, fin);
}

int main() {
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        vector<int> aux(n);
        contadorInversiones = 0;

        mergeSort(v, aux, 0, n - 1);

        cout <<"Son " << contadorInversiones <<" intercambios como minimo" <<endl;
    }

    return 0;
}