#ifndef __CIFRAS_SET_H__
#define __CIFRAS_SET_H__

#include <vector>
#include <string>

using namespace std;

int C[14]={1,2,3,4,5,6,7,8,9, 10, 25, 50, 75, 100};

class Cifras{
    private:
    int valor_actual;
    vector<int> numeros_restantes;
    int objetivo;

    vector<string> operaciones;

    //Parte interesante
    int mejor_resultado_encontrado;

    public:
    Cifras();

    void imprimirOperaciones();

    int get_mejor_resultado_encontrado();

    bool resolver_juego(const vector<int>& numeros_iniciales, int target);

    private:
    bool buscar_solucion(vector<int> restantes, int objetivo);
};
// MAIN PARA EL PROGRAMA DE LAS CIFRAS

#endif
