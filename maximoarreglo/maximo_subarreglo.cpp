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

double medir_tiempo(int (*func)(), int &(resultado)) {
    auto inicio = chrono::high_resolution_clock::now();
    resultado = func();
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo = fin - inicio;
    return tiempo.count();
}

int main(){

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distribucion(-5000, 5000);

    int tam[] = {1000, 2000, 4000, 8000};
    int resultado_cubico, resultado_cuadratico, resultado_lineal;

    double anterior_cubico = 0;
    double anterior_cuadratico = 0;
    double anterior_lineal = 0;

    cout<<"Tabla de resultados:"<<endl;
    cout << "n\t\tSuma O(n^3)\tTiempo O(n^3)\tRazon"<<"\t\tSuma O(n^2)\tTiempo O(n^2)\tRazon"<<"\t\tSuma O(n)\tTiempo O(n)\tRazon" << endl;
    for(int i=0; i<4; i++){
        n = tam[i];
        L = new int[n];
        for (int j = 0; j < n; j++) {
            L[j] = distribucion(gen);
        }
        double tiempo_n_cubico = medir_tiempo(n_cubico, resultado_cubico);
        double tiempo_n_cuadratico = medir_tiempo(n_cuadratico, resultado_cuadratico);
        double tiempo_n_lineal = medir_tiempo(n_lineal, resultado_lineal);

        double razon_cubico = 0;
        double razon_cuadratico = 0;
        double razon_lineal = 0;

        if(i > 0){
            razon_cubico = tiempo_n_cubico / anterior_cubico;
            razon_cuadratico = tiempo_n_cuadratico / anterior_cuadratico;
            razon_lineal = tiempo_n_lineal / anterior_lineal;
        }

        cout<<n<<"\t\t"<< resultado_cubico <<"\t\t"<< tiempo_n_cubico <<" ms\t"<<razon_cubico<<"\t\t"
        << resultado_cuadratico <<"\t\t"<< tiempo_n_cuadratico <<" ms\t"<<razon_cuadratico<<"\t\t"
        << resultado_lineal <<"\t\t"<< tiempo_n_lineal<<" ms\t"<<razon_lineal<<endl;

        anterior_cubico = tiempo_n_cubico;
        anterior_cuadratico = tiempo_n_cuadratico;
        anterior_lineal = tiempo_n_lineal;

        delete[] L;

    }
    return 0;
}