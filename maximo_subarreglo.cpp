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
    n = 6;
    L = new int[n];
    int Lista[] = {10, 0, -8, 5, 19, -1};
    for(int i=0;i<n;i++){
        L[i]=Lista[i];
    }
    cout<<"Lista: ";
    for(int i=0;i<n;i++){
        cout<<L[i];
        if(i+1<n) cout<<" ";
    }
    cout<<endl;
    cout<<"Resultado del subarreglo maximo en n cúbico: "<<n_cubico()<<"  Tiempo: "<<medir_tiempo(n_cubico)<<" ms"<<endl;
    cout<<"Resultado del subarreglo maximo en n cuadrático: "<<n_cuadratico()<<"  Tiempo: "<<medir_tiempo(n_cuadratico)<<" ms"<<endl;
    cout<<"Resultado del subarreglo maximo en n lineal: "<<n_lineal()<<"  Tiempo: "<<medir_tiempo(n_lineal)<<" ms"<<endl;
    return 0;
}