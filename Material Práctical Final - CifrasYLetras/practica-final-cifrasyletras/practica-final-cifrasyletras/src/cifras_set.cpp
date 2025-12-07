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

int generarNumero(){
    int min=100;
    int max=999;
    int numero = min + rand() % (max - min + 1);

    return numero;
}

//TDA de cifras

class cifras{
    private:
    int valor_actual;
    vector<int> numeros_restantes;
    int objetivo;

    std::vector<string> operaciones;

    //Parte interesante
    int mejor_resultado_encontrado;

    public:
    cifras() {
        mejor_resultado_encontrado = 0; 
        operaciones.clear();
    }

    void imprimirOperaciones(){
        reverse(operaciones.begin(), operaciones.end());

        for (const auto& op : operaciones) {
            cout << op << endl;
        }
    }

    int get_mejor_resultado_encontrado(){
        return mejor_resultado_encontrado;
    }

    bool resolver_juego(const vector<int>& numeros_iniciales, int target){
        operaciones.clear(); 
        mejor_resultado_encontrado = 0; 
        objetivo = target;

        return buscar_solucion(numeros_iniciales, target); 
    }
    private:
    bool buscar_solucion(vector<int> restantes, int objetivo){
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
    }

    
};

int main(){
    srand(time(0));

    vector<int> conjunto = generarConjunto();
    int objetivo = generarNumero();

    cout << "Objetivo: " << objetivo <<endl;
    cout << "Números: ";
    for (int n : conjunto) {
        cout << n << " ";
    }
    cout <<endl;

    cifras juego;
    if(juego.resolver_juego(conjunto, objetivo)){
        juego.imprimirOperaciones();
    }else{
        cout <<"El mejor resultado encontrado es "<<juego.get_mejor_resultado_encontrado()<<endl;
    }
}