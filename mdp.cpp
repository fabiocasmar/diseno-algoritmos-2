#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>     
#include <stdlib.h>
#include <vector>
#include <algorithm> 
using namespace std;

int main () {

    // Variables
    int n,m,temp_a,temp_b,aleatorio_vecindad,numero_seleccionado, temp;
    int intentos = 0;
    int max_intento = 100000;
    double dist_temp = 0.0;
    double dist_ant= -1.0;
    bool cambio = false;
    bool valido = false;
    double costos[3000][3000];
    double distancia_solucion_temp;
    vector< int > solucion_temp;

    // Lectura
    cin >> n >> m;
    while(!cin.eof()){
      cin >> temp_a >> temp_b >> dist_temp;
      costos[temp_a][temp_b]=dist_temp;
    }

    srand(time(NULL));
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


    for(int i=0; i < solucion_temp.size()-1; i++){
      for(int j = i+1; j < solucion_temp.size();j++){
          dist_temp += costos[solucion_temp[i]][solucion_temp[j]];
      }
    }
    cout << dist_temp << endl;

    while(intentos<max_intento){
      dist_ant = -1.0;
      while(dist_temp!=dist_ant){
        aleatorio_vecindad = rand() % (n);
        dist_ant = dist_temp;
        cambio = false;
        // Recorrido de la solucion temporal
        for(int k = 0; k < solucion_temp.size();k++){
          temp = solucion_temp[k];
          solucion_temp[k] = aleatorio_vecindad; 
          // Calculo de la nueva distancia
          distancia_solucion_temp= 0.0;
          
          for(int i=0; i < solucion_temp.size()-1; i++){
            for(int j = i+1; j < solucion_temp.size();j++){
                distancia_solucion_temp += costos[solucion_temp[i]][solucion_temp[j]];
            }
          }
          if(distancia_solucion_temp > dist_temp){
            dist_temp = distancia_solucion_temp;
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
      intentos = intentos + 1;
    }
    cout << dist_temp << endl;
  }