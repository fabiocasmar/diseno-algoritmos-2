#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>     
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define SEED  67219
#define MSIZE 4000

// Si no se declara en este punto, da error de tamaño de pila
// double costos[4000][4000];

void printVector(vector<int> *v)
{
    cout << "[";
    for(vector<int>::iterator it = v->begin(); it != v->end(); ++it) {
        cout << *it << ", ";
    }
    cout << "]\n";
}

int randomElem(vector<int> *v, int n)
{
    int t = 0;
    while (true)
    {
        t = rand() % n;
        if (std::find(v->begin(), v->end(), t) == v->end())
            break;
    }
    return t;
}

void randomSol(vector<int> *v, int n, int m)
{
    // Generacion de la solucion inicial aleatoria
    while(v->size() < m)
    {
        v->push_back(randomElem(v, n));
    }
}

int distance(vector<int> *v, double (*cost)[MSIZE][MSIZE])
{
    int sz = v->size(),
        ds = 0;

    for(int i=0; i < sz-1; i++)
    {
        for(int j = i+1; j < sz; j++)
        {
            ds += (*cost)[v->at(i)][v->at(j)];
        }
    }

    return ds;
}

int main () {
    // Variables
    int n = 0, m = 0, temp = 0, temp_a = 0, temp_b = 0, 
        aleatorio_vecindad = 0, numero_seleccionado = 0;
    int intentos = 0;
    double dist_ant = 0.0, dist_temp = 0.0, dist_sol = 0.0;
    bool cambio = false, valido = false;
    vector<int> solucion_temp;

    static double costos[MSIZE][MSIZE];
    
    // Inicio de la semilla para el aleatorio
    //srand(time(NULL));
    srand(SEED);
    
    // Lectura de la cantidad de elementos del cojunto,
    // y de elementos del subconjunto
    cin >> n >> m;

    // Lectura de la distancia entre cada punto
    while(!cin.eof()){
        cin >> temp_a >> temp_b >> dist_temp;
        costos[temp_a][temp_b]=dist_temp;
        costos[temp_b][temp_a]=dist_temp;
    }

    // Generacion de la solucion inicial aleatoria
    randomSol(&solucion_temp, n, m);
    
    //printVector(&solucion_temp);

    // Calculo de la sumatoria de la solucion Inicial
    dist_sol = distance(&solucion_temp, &costos);

    // Imprimo solucion Inicial
    cout << dist_sol << endl;

    // Ciclo del LS
    while(dist_sol!=dist_ant){
        // Calculo del aleatorio para la vencindad
        aleatorio_vecindad = randomElem(&solucion_temp, n);
        dist_ant = dist_sol;

        // Ciclo que recorre cada posicion de la solucion temporal
        // y coloca en cada posicion el punto aleatorio obtenido
        // Luego agarra el mejor de ellos
        for(int k = 0; k < solucion_temp.size();k++){
            temp = solucion_temp[k];
            solucion_temp[k] = aleatorio_vecindad; 
            
            // Calculo de la nueva distancia
            dist_temp = distance(&solucion_temp, &costos);

            if(dist_temp > dist_sol){
                dist_sol = dist_temp;
                break;
            }
            solucion_temp[k] = temp;
        }
    }
    // Imprimo la solucion obtenida
    cout << dist_sol << endl;
}