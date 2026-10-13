#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

map<string, vector<int>> memoria;
vector<int> diVen(string d){
    if(memoria.count(d)){
        return memoria[d];
    }
    vector<int> resultado;

    for(size_t i=0;i<d.size();i++){
        if(d[i]=='+' || d[i]=='-' || d[i]=='*'){
            vector<int> izq=diVen(d.substr(0,i));
            vector<int> der=diVen(d.substr(i+1));
            for (int a:izq){
                for(int b:der){
                    if(d[i]=='+')
                        resultado.push_back(a+b);
                    else if(d[i]=='-')
                        resultado.push_back(a-b);
                    else
                        resultado.push_back(a*b);
                }
            }
        }
    }
    if(resultado.empty()){
        resultado.push_back(stoi(d));
    }
    memoria[d]=resultado;

    return resultado;
}

int main(){
    string entrada;
    cout<<"Ingrese una expresion(+ , -, *):"<<endl;
    cin>>entrada;
    vector<int> resultado=diVen(entrada);
    sort(resultado.begin(), resultado.end());
    for(size_t i=0;i<resultado.size();i++){
        if(i>0){
            cout<<" ";
        }
        cout<<resultado[i];
    }
    cout<<"\n";

    return 0;
}