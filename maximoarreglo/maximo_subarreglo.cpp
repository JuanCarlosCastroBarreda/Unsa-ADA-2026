#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
using namespace std;

int* L;
int n;
int n_cubico(){
    int max=L[0];
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            int parcial=0;
            for(int k=i; k<=j; k++){
                parcial+=L[k];
            }
            if(parcial>max){
                max=parcial;
            }
        }
    }
    return max;
}

int n_cuadratico(){
    int max=L[0];
    for(int i=0; i<n; i++){
        int parcial=0;
        for(int j=i; j<n; j++){
            parcial+=L[j];
            if(parcial>max){
                max=parcial;
            }
        }
    }
    return max;
}

int n_lineal(){
    int aqui=L[0];
    int global=L[0];
    for(int i=1; i<n; i++){
        aqui=max(L[i],aqui+L[i]);
        global=max(global,aqui);
    }
    return global;
}

double medir_tiempo(int (*func)()) {
    auto inicio = chrono::high_resolution_clock::now();
    func();
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo = fin - inicio;
    return tiempo.count();
}

int main(){

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distribucion(-5000, 5000);

    int tam[] = {1000, 2000, 4000, 8000};

    cout<<"Tabla de resultados:"<<endl;
    cout << "n\t\tO(n^3)\t\tO(n^2)\t\tO(n)" << endl;
    for(int i=0; i<4; i++){
        n = tam[i];
        L = new int[n];
        for (int j = 0; j < n; j++) {
            L[j] = distribucion(gen);
        }
        double tiempo_n_cubico = medir_tiempo(n_cubico);
        double tiempo_n_cuadratico = medir_tiempo(n_cuadratico);
        double tiempo_n_lineal = medir_tiempo(n_lineal);

        cout<<n<<"\t\t"<< tiempo_n_cubico << " ms\t"<<tiempo_n_cuadratico <<" ms\t"<<tiempo_n_lineal<<" ms"<< endl;
    }
    return 0;
}