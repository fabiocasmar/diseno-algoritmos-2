#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>     
#include <stdlib.h>
#include <vector>
#include <algorithm> 
using namespace std;


int aleatorio(int n){
    srand(time(NULL));
    return 1 + rand() % (n - 1);
}

int main () {

    // Variables
    int n,m,temp_a,temp_b,num,cant_aleatorios,aleatorio_vecindad,numero_seleccionado;
    double dist_temp = -1.0;
    double dist_anterior;
    double costos[3000][3000];
    vector< int > solucion_temp;
    std::vector<char> v;
    double distancia_solucion_temp;

    // Lectura
    cin >> n >> m;
    while(!cin.eof()){
      cin >> temp_a >> temp_a >> dist_temp;
      costos[temp_a][temp_b]=dist_temp;
    }
    for(int i = 0; i < m; i++){
      solucion_temp.push_back(aleatorio(n));
    }
    distancia_solucion_temp = 0;
    for(int i = 0; i < m; i++){
      distancia_solucion_temp += costos[solucion_temp[i]][solucion_temp[i+1]];
    }
    distancia_solucion_temp += costos[solucion_temp[m-1]][solucion_temp[0]];
    while(dist_temp!=dist_anterior){
      dist_anterior = dist_temp;
      aleatorio_vecindad = aleatorio(n);
      // Recorrido de la solucion temporal
      for(int j = 0; j < solucion_temp.size();j++){
        // Calculo de la nueva distancia
        for(int i =0; i < solucion_temp.size(); i++){
          if(i-1!=j){
            distancia_solucion_temp += costos[solucion_temp[i % solucion_temp.size()]][solucion_temp[(i+1) % solucion_temp.size()]];
          }else{
            distancia_solucion_temp += costos[solucion_temp[(i-1) % solucion_temp.size()]][aleatorio_vecindad] +
                                        costos[aleatorio_vecindad][solucion_temp[(i+1) % solucion_temp.size()]];
            i=i+1;
          }
        }
        if(distancia_solucion_temp > dist_temp){
          dist_temp = distancia_solucion_temp;
          numero_seleccionado = j;
        }
      }
      solucion_temp[numero_seleccionado]=aleatorio_vecindad;
    }
    cout << dist_temp;
  }