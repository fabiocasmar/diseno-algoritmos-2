#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>     
#include <stdlib.h>
#include <vector>
#include <algorithm> 
using namespace std;

// Variables globales
int n,m,temp_a,temp_b,num,cant_aleatorios;
double dist_temp = -1.0;
double dist_anterior = -1.0;
double costos[3000][3000];
vector<int > solucion_temp;
vector<int > vecindad;
vector<int > dist_vecindad;
std::vector<char> v;
double distancia_solucion_temp;

int aleatorio(){
    srand(time(NULL));
    return 1 + rand() % (n - 1);
}

void calculo_vecindad(){
  vecindad.clear();
  dist_vecindad.clear();
  int temp;
  while(vecindad.size()==cant_aleatorios){
    temp = aleatorio();
    if((find(solucion_temp.begin(), solucion_temp.end(), temp)!=solucion_temp.end())&&
        (find(vecindad.begin(), vecindad.end(), temp)!=vecindad.end())){
          vecindad.push_back(temp);
    }
  }
}

void calculo_cant_aleatorios(){
  cant_aleatorios = 5;
}

int main () {
    // Lectura
    cin >> n >> m;
    calculo_cant_aleatorios();
    while(!cin.eof()){
      cin >> temp_a >> temp_a >> dist_temp;
      costos[temp_a][temp_b]=dist_temp;
    }
    for(int i; i < m; i++){
      solucion_temp.push_back(aleatorio());
    }
    while(dist_temp!=dist_anterior){
      dist_anterior = dist_temp;
      calculo_vecindad();
  //     for(int i; i < solucion_temp.size()){
  //      for(){
  //      }
  //    }
    }
  }