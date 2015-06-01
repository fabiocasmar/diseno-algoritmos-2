#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>     
#include <stdlib.h>
#include <vector>
#include <algorithm> 
using namespace std;

// Si no se declara en este punto, da error de tamaño de pila
int  n = 0,m = 0;
double costos[4000][4000];


vector<int > ls(vector< int > solucion_temp){

    // Variables
    int aleatorio_vecindad = 0, numero_seleccionado = 0, 
        cant_it = 10, intentos = 0, temp = 0, max_it = 0;
    double dist_ant = 0.0, dist_temp = 0.0, dist_sol = 0.0;
    bool cambio = false, valido = false;
 
    sort(solucion_temp.begin(), solucion_temp.end());

    // Calculo de la sumatoria de la solucion Inicial
    dist_sol = 0.0;
    for(int i=0; i < solucion_temp.size()-1; i++){
        for(int j = i+1; j < solucion_temp.size();j++){
            dist_sol =  dist_sol + costos[solucion_temp[i]][solucion_temp[j]];
        }
    }
    // Imprimo solucion Inicial
    while(cant_it < max_it){
    // Ciclo del LS
        dist_ant = -1.0;
        while((dist_sol!=dist_ant)&&(cant_it < max_it)){
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
                    dist_ant = dist_sol;
                    dist_sol = dist_temp;
                    numero_seleccionado = k;
                    cambio = true;
                }
                solucion_temp[k] = temp;
            }
            if(cambio){
                solucion_temp[numero_seleccionado]=aleatorio_vecindad;
                sort(solucion_temp.begin(), solucion_temp.end());
                intentos = -1;
                cant_it = -1;
                //cout << dist_sol << endl;
            }
            cant_it = cant_it+1;
        }

    }
    return solucion_temp;
  }

int main(){
    vector< int > solucion_inicial, solucion_perturbada, ls_solucion_perturbada;
    int temp = 0, temp_a = 0, temp_b = 0, iter = 0, max_it = 10;
    double dist_solucion_inicial = 0.0, dist_ls_solucion_perturbada = 0.0, dist_temp = 0.0;
    bool valido = false;
    cout.precision(15);
    // Obtengo un valor del Reloj del Sistema, convierto los segundos
        // en un entero sin signo e inicializo la semilla
    
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);

    // Lectura de la cantidad de elementos del cojunto,
        //  y de elementos del subconjunto
    cin >> n >> m;

    max_it = 100;
    // Lectura de la distancia entre cada punto
    while(!cin.eof()){
        cin >> temp_a >> temp_b >> dist_temp;
        costos[temp_a][temp_b]=dist_temp;
        costos[temp_b][temp_a]=dist_temp;
    }

    // Generacion de la solucion inicial aleatoria
    while(solucion_inicial.size()<m){
        int temp = rand() % (n);
        valido = true;
        for(int j = 0; j < solucion_inicial.size(); j++){
            if(temp == solucion_inicial[j]){
                valido = false;
                break;
            }
        }
        if(valido){
            solucion_inicial.push_back(temp);
        }
    }
    for(int i=0; i < solucion_inicial.size()-1; i++){
        for(int j = i+1; j < solucion_inicial.size();j++){
            dist_solucion_inicial += 
                costos[solucion_inicial[i]][solucion_inicial[j]];
        }
    }
    cout << dist_solucion_inicial << endl;
    solucion_inicial = ls(solucion_inicial);
    while(iter < max_it){
        solucion_perturbada = solucion_inicial;
        for(int l = 0;l<=int(1+m*0.1);l++){
            solucion_perturbada[rand()%(m)]=rand()%(n);
        }
        ls_solucion_perturbada=ls(solucion_perturbada);

        dist_ls_solucion_perturbada = 0.0;
        for(int i=0; i < ls_solucion_perturbada.size()-1; i++){
            for(int j = i+1; j < ls_solucion_perturbada.size();j++){
                dist_ls_solucion_perturbada += 
                    costos[ls_solucion_perturbada[i]][ls_solucion_perturbada[j]];
            }
        }
        dist_solucion_inicial = 0.0;
        for(int i=0; i < solucion_inicial.size()-1; i++){
            for(int j = i+1; j < solucion_inicial.size();j++){
                dist_solucion_inicial += 
                    costos[solucion_inicial[i]][solucion_inicial[j]];
            }
        }
        if(dist_ls_solucion_perturbada > dist_solucion_inicial){
            solucion_inicial = ls_solucion_perturbada;         
        }
        iter=iter+1;
    }
    dist_solucion_inicial = 0.0;
    for(int i=0; i < solucion_inicial.size()-1; i++){
        for(int j = i+1; j < solucion_inicial.size();j++){
            dist_solucion_inicial += 
                costos[solucion_inicial[i]][solucion_inicial[j]];
        }
    }
    cout << dist_solucion_inicial << endl;
}