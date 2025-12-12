#include "cifras_set.h"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


//Funciones de generar números
vector<int> generarConjunto(){
    vector<int> v;
    for(int i=0; i<6; i++){
        int numero = rand() % (13 + 1);
        v.push_back(C[numero]);
    }

    return v;
}

//Parte extra, 6 numero aleatorios fuera del conjunto
vector<int> generar(){
    vector<int> v;
    for(int i=0; i<6; i++){
        int numero = 1 + rand() % (100 - 1 + 1);
        v.push_back(numero);
    }

    return v;
}


int generarNumero(){
    int min=100;
    int max=999;
    int numero = min + rand() % (max - min + 1);

    return numero;
}

//TDA de cifras
    Cifras::Cifras() {
        mejor_resultado_encontrado = 0; 
        operaciones.clear();
    };

    void Cifras::imprimirOperaciones(){
        reverse(operaciones.begin(), operaciones.end());

        for (const auto& op : operaciones) {
            cout << op << endl;
        }
    };

    int Cifras::get_mejor_resultado_encontrado(){
        return mejor_resultado_encontrado;
    };

    bool Cifras::resolver_juego(const vector<int>& numeros_iniciales, int target){
        operaciones.clear(); 
        mejor_resultado_encontrado = 0; 
        objetivo = target;

        return buscar_solucion(numeros_iniciales, target); 
    };

    bool Cifras::buscar_solucion(vector<int> restantes, int objetivo){
        for(int i = 0; i<restantes.size(); i++){
            for(int j = i+1; j<restantes.size(); j++){
                int a = restantes[i];
                int b = restantes[j];
                
                // División a/b
                if(b != 0 && a%b==0){
                    int r=a/b;
                    if(abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    if(r==objetivo){
                        operaciones.push_back(to_string(a) + " / " + to_string(b));
                        return true;
                    }else{
                        vector<int> nueva_lista = restantes;
                        nueva_lista.erase(nueva_lista.begin()+j);
                        nueva_lista.erase(nueva_lista.begin()+i);
                        nueva_lista.push_back(r);
                        if (buscar_solucion(nueva_lista, objetivo)) {
                            operaciones.push_back(to_string(a) + " / " + to_string(b));
                            return true;
                        }
                    }
                }
                
                // Resta a-b
                if(a-b>=0){
                    int r=a-b;
                    if(abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    if(r==objetivo){
                        operaciones.push_back(to_string(a) + " - " + to_string(b));
                        return true;
                    }else{
                        vector<int> nueva_lista = restantes;
                        nueva_lista.erase(nueva_lista.begin()+j);
                        nueva_lista.erase(nueva_lista.begin()+i);
                        nueva_lista.push_back(r);
                        if (buscar_solucion(nueva_lista, objetivo)) {
                            operaciones.push_back(to_string(a) + " - " + to_string(b));
                            return true;
                        }
                    }
                }
                
                // División b/a
                if(a != 0 && b%a==0){
                    int r=b/a;
                    if(abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    if(r==objetivo){
                        operaciones.push_back(to_string(b) + " / " + to_string(a));
                        return true;
                    }else{
                        vector<int> nueva_lista = restantes;
                        nueva_lista.erase(nueva_lista.begin()+j);
                        nueva_lista.erase(nueva_lista.begin()+i);
                        nueva_lista.push_back(r);
                        if (buscar_solucion(nueva_lista, objetivo)) {
                            operaciones.push_back(to_string(b) + " / " + to_string(a));
                            return true;
                        }
                    }
                }
                
                // Resta b-a
                if(b-a>=0){
                    int r=b-a;
                    if(abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    if(r==objetivo){
                        operaciones.push_back(to_string(b) + " - " + to_string(a));
                        return true;
                    }else{
                        vector<int> nueva_lista = restantes;
                        nueva_lista.erase(nueva_lista.begin()+j);
                        nueva_lista.erase(nueva_lista.begin()+i);
                        nueva_lista.push_back(r);
                        if (buscar_solucion(nueva_lista, objetivo)) {
                            operaciones.push_back(to_string(b) + " - " + to_string(a));
                            return true;
                        }
                    }
                }
                
                // Suma a+b
                if(a+b==objetivo){
                    operaciones.push_back(to_string(a) + " + " + to_string(b));
                    return true;
                }else{
                    int r=a+b;
                    if(abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    vector<int> nueva_lista = restantes;
                    nueva_lista.erase(nueva_lista.begin()+j);
                    nueva_lista.erase(nueva_lista.begin()+i);
                    nueva_lista.push_back(r);
                    if (buscar_solucion(nueva_lista, objetivo)) {
                        operaciones.push_back(to_string(a) + " + " + to_string(b));
                        return true;
                    }
                }
                
                // Multiplicación a*b
                if(a*b==objetivo){
                    operaciones.push_back(to_string(a) + " * " + to_string(b));
                    return true;
                }else{
                    int r=a*b;
                    if(abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    vector<int> nueva_lista = restantes;
                    nueva_lista.erase(nueva_lista.begin()+j);
                    nueva_lista.erase(nueva_lista.begin()+i);
                    nueva_lista.push_back(r);
                    if (buscar_solucion(nueva_lista, objetivo)) {
                        operaciones.push_back(to_string(a) + " * " + to_string(b));
                        return true;
                    }
                }
            }
        }
        return false;
    };

//Función extra para permitir jugar al usuario
void operar(int a, int b, char oper, vector<int> &conjunto){
    if(find(conjunto.begin(), conjunto.end(), a) == conjunto.end() || find(conjunto.begin(), conjunto.end(), b) == conjunto.end()){
        cout<<"El numero no está en el conjunto"<<endl;
        return;
    }
    int result;
    switch (oper)
    {
    case '+':
        result = a+b;
        break;
    case '-':
        if(a-b<0){
            cout<<"No se pueden obtener numeros negativos"<<endl;
            return;
        }else{
            result=a-b;
        }
        break;
    case '*':
        result=a*b;
        break;
    case '/':
        if(a%b==0){
            result=a/b;
        }else{
            cout<<"La división debe ser exacta"<<endl;
            return;
        }
        break;
    default:
        cout<<"Operador no válido"<<endl;
        break;
    }

    auto it = find(conjunto.begin(), conjunto.end(), a);
    if (it != conjunto.end()){
        conjunto.erase(it);
    } 

    it = std::find(conjunto.begin(), conjunto.end(), b);
    if (it != conjunto.end()){
        conjunto.erase(it);
    }

    conjunto.push_back(result);
    cout<<result<<endl;
}

void imprimirConjunto(vector<int> conjunto){
    cout << "Números: ";
    for (int n : conjunto) {
        cout << n << " ";
    }
    cout <<endl;
}

int main(){
    srand(time(0));

    int opc;
    cout<<"¿Quieres jugar con:"<<endl;
    cout<<"1) Combinación mágica (siempre hay solución)"<<endl;
    cout<<"2) Números aleatorios (más difícil)"<<endl;
    cin>>opc;
    vector<int> conjunto;
    if (opc == 2){
        conjunto = generar();
    } else{
        conjunto = generarConjunto();
    }
    vector<int> numeros = conjunto;
    int objetivo = generarNumero();

    cout << "Objetivo: " << objetivo <<endl;
    imprimirConjunto(conjunto);

    char respuesta;
    cout<<"Quieres jugar? (y/n)"<<endl;
    cin>>respuesta;
    if(respuesta == 'y'){
        bool victoria=false;
        bool rendirse=false;
        while(!victoria && !rendirse){
            int a, b;
            char oper;
            cin>>a>>oper>>b;
            if(a==-1){
                rendirse=true;
                continue;
            }
            operar(a, b, oper, conjunto);
            imprimirConjunto(conjunto);
            if(conjunto.back() == objetivo){
                victoria = true;
            }
            if(conjunto.size() == 1){
                break;
            }
            cout<<"-1 para rendirte"<<endl;
        }
        
        if(victoria){
            cout<<"¡Felicidades, lo conseguiste!"<<endl;
        }else if(rendirse){
            cout<<"Te rendiste. Aquí está la solución correcta:"<<endl;
        }else{
            cout<<"Te quedaste sin movimientos. Aquí está la solución correcta:"<<endl;
        }
    }
    
    Cifras juego;
    if(juego.resolver_juego(numeros, objetivo)){
        juego.imprimirOperaciones();
    }else{
        cout <<"El mejor resultado encontrado es "<<juego.get_mejor_resultado_encontrado()<<endl;
    }
}