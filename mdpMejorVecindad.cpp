#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>     
#include <stdlib.h>
#include <vector>
#include <algorithm> 
using namespace std;

// Si no se declara en este punto, da error de tamaño de pila
double costos[4000][4000];

int main () {

    // Variables
    int n = 0,m = 0,  temp = 0, temp_a = 0, temp_b = 0, 
        aleatorio_vecindad = 0, numero_seleccionado = 0;
    int intentos = 0;
    double dist_ant = 0.0, dist_temp = 0.0, dist_sol = 0.0;
    bool cambio = false, valido = false;
    vector< int > solucion_temp;

    // Inicio de la semilla para el aleatorio
    srand(time(NULL));

    // Lectura de la cantidad de elementos del cojunto,
        //  y de elementos del subconjunto
    cin >> n >> m;

    // Lectura de la distancia entre cada punto
    while(!cin.eof()){
        cin >> temp_a >> temp_b >> dist_temp;
        costos[temp_a][temp_b]=dist_temp;
        costos[temp_b][temp_a]=dist_temp;
    }

    // Generacion de la solucion inicial aleatoria
    while(solucion_temp.size()<m){
        int temp = rand() % (n);
        valido = true;
        for(int j = 0; j < solucion_temp.size(); j++){
            if(temp == solucion_temp[j]){
                valido = false;
                break;
            }
        }
        if(valido){
            solucion_temp.push_back(temp);
        }
    }

    // Calculo de la sumatoria de la solucion Inicial
    dist_sol = 0.0;
    for(int i=0; i < solucion_temp.size()-1; i++){
        for(int j = i+1; j < solucion_temp.size();j++){
            dist_sol =  dist_sol + costos[solucion_temp[i]][solucion_temp[j]];
        }
    }
    // Imprimo solucion Inicial
    cout << dist_sol << endl;

    // Ciclo del LS
    while(dist_sol!=dist_ant){
        // Calculo del aleatorio para la vencindad
        while(true){
            int temp = rand() % (n);
            int valido = true;
            for(int j = 0; j < solucion_temp.size(); j++){
                if(temp == solucion_temp[j]){
                    valido = false;
                    break;
                }
            }
            if(valido){
                aleatorio_vecindad = temp;
                break;
            }
        }
        dist_ant = dist_sol;
        cambio = false;

        // Ciclo que recorre cada posicion de la solucion temporal
            // y coloca en cada posicion el punto aleatorio obtenido
                // Luego agarra el mejor de ellos
        for(int k = 0; k < solucion_temp.size();k++){
            temp = solucion_temp[k];
            solucion_temp[k] = aleatorio_vecindad; 
            // Calculo de la nueva distancia
            dist_temp= 0.0;
            for(int i=0; i < solucion_temp.size()-1; i++){
                for(int j = i+1; j < solucion_temp.size();j++){
                    dist_temp += costos[solucion_temp[i]][solucion_temp[j]];
                }
            }
            if(dist_temp > dist_sol){
                dist_sol = dist_temp;
                numero_seleccionado = k;
                cambio = true;
            }
            solucion_temp[k] = temp;
        }
        if(cambio){
            solucion_temp[numero_seleccionado]=aleatorio_vecindad;
            intentos = -1;
        }
    }

    // Imprimo la solucion obtenida
    cout << dist_sol << endl;
  }